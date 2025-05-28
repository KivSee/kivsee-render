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

            // Extract time range
            uint32_t time1 = json_data["startTimeMs"].get<uint32_t>();
            uint32_t time2 = json_data["endTimeMs"].get<uint32_t>();

            // Parse things array
            std::vector<kivsee_simulation::LedController*> things;
            for (const auto& seq_data : json_data["things"]) {
                kivsee_simulation::LedController *led_controller = new kivsee_simulation::LedController(144); // Hard coded :()

                std::string sequenceProto = base64_decode(seq_data["sequenceProto"].get<std::string>());
                std::string objectProto = base64_decode(seq_data["objectProto"].get<std::string>());

                bool success = led_controller->InitFromProtoBuffers((const uint8_t*)sequenceProto.c_str(), sequenceProto.length(), (const uint8_t*)objectProto.c_str(), objectProto.length());
                if (!success) {
                    std::cout << "Failed to initialize LED controller" << std::endl;
                    continue;
                }

                things.push_back(led_controller);
            }

            // Calculate brightness over time
            double total_brightness = 0.0;
            int total_leds = 0;
            for (uint32_t current_time = time1; current_time <= time2; current_time += 20) {
                for (auto& controller : things) {
                    const kivsee_render::HSV* frame = controller->Render(current_time);
                    const int numberOfLeds = controller->GetNumLeds();
                    for (int i = 0; i < numberOfLeds; i++) {
                        const double current_pixel_brightness = frame[i].val;
                        total_brightness += current_pixel_brightness;
                        total_leds++;
                    }
                }
            }

            double average_brightness = 0.0;
            if (total_leds > 0) {
                average_brightness = total_brightness / total_leds;
            }

            // Add time difference to the response
            json final_response = {
                {"time_difference", time2 - time1},
                {"average_brightness", average_brightness}
            };

            res.set_content(final_response.dump(), "application/json");

            for (auto& controller : things) {
                delete controller;
            }
            things.clear();

        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(json({{"error", e.what()}}).dump(), "application/json");
        } });

    std::cout << "Server starting on port 8084..." << std::endl;
    
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