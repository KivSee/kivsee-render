#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <string>
#include <algorithm>
#include <signal.h>
#include <atomic>
#include <thread>
#include "led_controller.h"
#include "base64.h"

// Define M_PI if not defined (Windows specific)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using json = nlohmann::json;

// Global variables for signal handling
httplib::Server* g_server = nullptr;
std::atomic<bool> g_running(true);

void signal_handler(int signal) {
    if ((signal == SIGTERM || signal == SIGINT) && g_server) {
        std::cout << "Received signal " << signal << ", shutting down gracefully..." << std::endl;
        g_running = false;
        g_server->stop();
    }
}

struct SequenceStats
{
    double mean;
    double std_dev;
    double min;
    double max;
    double correlation;
};

struct HSVStats {
    std::vector<int> hue_histogram;
    std::vector<int> saturation_histogram;
    std::vector<int> value_histogram;
    double mean_hue;
    double std_dev_hue;
    double mean_saturation;
    double std_dev_saturation;
    double mean_value;
    double std_dev_value;
    double prominent_hue;
    double prominent_saturation;
    double prominent_value;
};

struct SequenceData
{
    std::string thingName;
    std::vector<double> sequence;
    std::vector<double> objects;
};

SequenceStats calculateStats(const std::vector<double> &sequence, const std::vector<double> &objects)
{
    SequenceStats stats;

    // Calculate mean
    stats.mean = std::accumulate(sequence.begin(), sequence.end(), 0.0) / sequence.size();

    // Calculate standard deviation
    double sq_sum = std::inner_product(sequence.begin(), sequence.end(), sequence.begin(), 0.0);
    stats.std_dev = std::sqrt(sq_sum / sequence.size() - stats.mean * stats.mean);

    // Calculate min and max
    stats.min = *std::min_element(sequence.begin(), sequence.end());
    stats.max = *std::max_element(sequence.begin(), sequence.end());

    // Calculate correlation between sequences
    double sum1 = std::accumulate(sequence.begin(), sequence.end(), 0.0);
    double sum2 = std::accumulate(objects.begin(), objects.end(), 0.0);
    double mean1 = sum1 / sequence.size();
    double mean2 = sum2 / objects.size();

    double numerator = 0.0;
    double denom1 = 0.0;
    double denom2 = 0.0;

    for (size_t i = 0; i < sequence.size(); ++i)
    {
        numerator += (sequence[i] - mean1) * (objects[i] - mean2);
        denom1 += (sequence[i] - mean1) * (sequence[i] - mean1);
        denom2 += (objects[i] - mean2) * (objects[i] - mean2);
    }

    stats.correlation = numerator / std::sqrt(denom1 * denom2);

    return stats;
}

// Helper function to calculate mean of cyclic values (like hue)
double cyclicMean(const std::vector<double>& values) {
    double sum_sin = 0.0;
    double sum_cos = 0.0;

    for (double value : values) {
        double angle = value * 2 * M_PI;  // Convert to radians
        sum_sin += std::sin(angle);
        sum_cos += std::cos(angle);
    }

    double mean_angle = std::atan2(sum_sin, sum_cos);
    if (mean_angle < 0) mean_angle += 2 * M_PI;
    return mean_angle / (2 * M_PI);  // Convert back to [0,1] range
}

// Helper function to calculate standard deviation of cyclic values
double cyclicStdDev(const std::vector<double>& values, double mean) {
    double sum_squared_diff = 0.0;
    for (double value : values) {
        double diff = value - mean;
        // Handle the cyclic nature by taking the shortest distance
        if (diff > 0.5) diff -= 1.0;
        else if (diff < -0.5) diff += 1.0;
        sum_squared_diff += diff * diff;
    }
    return std::sqrt(sum_squared_diff / values.size());
}

HSVStats calculateHSVStats(const std::vector<kivsee_render::HSV>& frames) {
    HSVStats stats;
    const int num_buckets = 10;
    stats.hue_histogram.resize(num_buckets, 0);
    stats.saturation_histogram.resize(num_buckets, 0);
    stats.value_histogram.resize(num_buckets, 0);

    std::vector<double> hues;
    std::vector<double> saturations;
    std::vector<double> values;

    // Collect all values and build histograms
    for (const auto& frame : frames) {
        hues.push_back(frame.hue);
        saturations.push_back(frame.sat);
        values.push_back(frame.val);

        // Update histograms
        stats.hue_histogram[static_cast<int>(frame.hue * num_buckets)]++;
        stats.saturation_histogram[static_cast<int>(frame.sat * num_buckets)]++;
        stats.value_histogram[static_cast<int>(frame.val * num_buckets)]++;
    }

    // Calculate means
    stats.mean_hue = cyclicMean(hues);
    stats.mean_saturation = std::accumulate(saturations.begin(), saturations.end(), 0.0) / saturations.size();
    stats.mean_value = std::accumulate(values.begin(), values.end(), 0.0) / values.size();

    // Calculate standard deviations
    stats.std_dev_hue = cyclicStdDev(hues, stats.mean_hue);
    stats.std_dev_saturation = std::sqrt(std::accumulate(saturations.begin(), saturations.end(), 0.0,
        [&](double sum, double val) { return sum + (val - stats.mean_saturation) * (val - stats.mean_saturation); }) / saturations.size());
    stats.std_dev_value = std::sqrt(std::accumulate(values.begin(), values.end(), 0.0,
        [&](double sum, double val) { return sum + (val - stats.mean_value) * (val - stats.mean_value); }) / values.size());

    // Find prominent values (most frequent bucket)
    auto max_hue_it = std::max_element(stats.hue_histogram.begin(), stats.hue_histogram.end());
    auto max_sat_it = std::max_element(stats.saturation_histogram.begin(), stats.saturation_histogram.end());
    auto max_val_it = std::max_element(stats.value_histogram.begin(), stats.value_histogram.end());

    stats.prominent_hue = (std::distance(stats.hue_histogram.begin(), max_hue_it) + 0.5) / num_buckets;
    stats.prominent_saturation = (std::distance(stats.saturation_histogram.begin(), max_sat_it) + 0.5) / num_buckets;
    stats.prominent_value = (std::distance(stats.value_histogram.begin(), max_val_it) + 0.5) / num_buckets;

    return stats;
}

int main()
{
    httplib::Server svr;
    g_server = &svr;

    // Set up signal handlers
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    svr.Post("/sequence/stats", [](const httplib::Request &req, httplib::Response &res)
             {
        try {
            auto json_data = json::parse(req.body);
            std::cout << "Successfully parsed JSON" << std::endl;

            // Extract time range
            uint32_t time1 = json_data["startTimeMs"].get<uint32_t>();
            uint32_t time2 = json_data["endTimeMs"].get<uint32_t>();
            std::cout << "Time range: " << time1 << " to " << time2 << std::endl;

            // Parse things array
            std::vector<kivsee_simulation::LedController*> things;
            std::cout << "Processing " << json_data["things"].size() << " things" << std::endl;

            for (const auto& seq_data : json_data["things"]) {
                try {
                    kivsee_simulation::LedController *led_controller = new kivsee_simulation::LedController(144);

                    std::string sequenceProto = base64_decode(seq_data["sequenceProto"].get<std::string>());
                    std::string objectProto = base64_decode(seq_data["objectProto"].get<std::string>());
                    std::cout << "Decoded protos, lengths: " << sequenceProto.length() << ", " << objectProto.length() << std::endl;

                    bool success = led_controller->InitFromProtoBuffers((const uint8_t*)sequenceProto.c_str(), sequenceProto.length(), (const uint8_t*)objectProto.c_str(), objectProto.length());
                    if (!success) {
                        std::cout << "Failed to initialize LED controller" << std::endl;
                        delete led_controller;
                        continue;
                    }

                    things.push_back(led_controller);
                } catch (const std::exception& e) {
                    std::cout << "Error processing thing: " << e.what() << std::endl;
                    continue;
                }
            }

            std::cout << "Successfully initialized " << things.size() << " controllers" << std::endl;

            // Calculate brightness and collect HSV data
            double total_brightness = 0.0;
            int total_leds = 0;
            std::vector<kivsee_render::HSV> all_frames;

            try {
                for (uint32_t current_time = time1; current_time <= time2; current_time += 20) {
                    for (auto& controller : things) {
                        const kivsee_render::HSV* frame = controller->Render(current_time);
                        const int numberOfLeds = controller->GetNumLeds();
                        for (int i = 0; i < numberOfLeds; i++) {
                            const double current_pixel_brightness = frame[i].val;
                            total_brightness += current_pixel_brightness;
                            total_leds++;
                            all_frames.push_back(frame[i]);
                        }
                    }
                }
            } catch (const std::exception& e) {
                std::cout << "Error during frame rendering: " << e.what() << std::endl;
                throw;
            }

            std::cout << "Processed " << total_leds << " LEDs across " << all_frames.size() << " frames" << std::endl;

            double average_brightness = 0.0;
            if (total_leds > 0) {
                average_brightness = total_brightness / total_leds;
            }

            // Calculate HSV statistics
            HSVStats hsv_stats = calculateHSVStats(all_frames);
            std::cout << "Calculated HSV statistics" << std::endl;

            // Add time difference and all statistics to the response
            json final_response = {
                {"time_difference", time2 - time1},
                {"average_brightness", average_brightness},
                {"hsv_stats", {
                    {"hue_histogram", hsv_stats.hue_histogram},
                    {"saturation_histogram", hsv_stats.saturation_histogram},
                    {"value_histogram", hsv_stats.value_histogram},
                    {"mean_hue", hsv_stats.mean_hue},
                    {"std_dev_hue", hsv_stats.std_dev_hue},
                    {"mean_saturation", hsv_stats.mean_saturation},
                    {"std_dev_saturation", hsv_stats.std_dev_saturation},
                    {"mean_value", hsv_stats.mean_value},
                    {"std_dev_value", hsv_stats.std_dev_value},
                    {"prominent_hue", hsv_stats.prominent_hue},
                    {"prominent_saturation", hsv_stats.prominent_saturation},
                    {"prominent_value", hsv_stats.prominent_value}
                }}
            };

            std::cout << "Preparing response" << std::endl;
            res.set_content(final_response.dump(), "application/json");
            std::cout << "Response sent successfully" << std::endl;

            for (auto& controller : things) {
                delete controller;
            }
            things.clear();

        } catch (const json::parse_error& e) {
            std::cout << "JSON parse error: " << e.what() << std::endl;
            res.status = 400;
            res.set_content(json({{"error", "Invalid JSON format"}, {"details", e.what()}}).dump(), "application/json");
        } catch (const json::type_error& e) {
            std::cout << "JSON type error: " << e.what() << std::endl;
            res.status = 400;
            res.set_content(json({{"error", "Invalid JSON data type"}, {"details", e.what()}}).dump(), "application/json");
        } catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
            res.status = 500;
            res.set_content(json({{"error", "Internal server error"}, {"details", e.what()}}).dump(), "application/json");
        } catch (...) {
            std::cout << "Unknown error occurred" << std::endl;
            res.status = 500;
            res.set_content(json({{"error", "Unknown internal server error"}}).dump(), "application/json");
        } });

    std::cout << "Server starting on port 80..." << std::endl;

    // Start server in a non-blocking way
    std::thread server_thread([&svr]() {
        svr.listen("0.0.0.0", 80);
    });

    // Wait for shutdown signal
    while (g_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Wait for server thread to finish
    if (server_thread.joinable()) {
        server_thread.join();
    }

    return 0;
}