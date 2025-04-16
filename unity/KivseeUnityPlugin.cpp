#include "KivseeUnityPlugin.h"
#include <stdio.h>
#include "interfaces/IUnityLog.h"

// Include the kivsee-render library headers
#include <hsv.h>
#include <segments/segments_map.h>
#include <effect.h>
#include <animation.h>
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <stdexcept>

// The Unity interface pointers
static IUnityInterfaces* s_unityInterfaces = nullptr;
static IUnityLog* s_unityLog = nullptr;

// Sample data for the GetArray function
static const int s_TestArray[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
static const int s_TestArraySize = sizeof(s_TestArray) / sizeof(s_TestArray[0]);

// Our LED data
static std::unique_ptr<kivsee_render::segments::SegmentsMap> s_segmentsMap = nullptr;
static std::vector<kivsee_render::HSV> s_ledsBuffer;
static std::list<kivsee_render::Effect*> s_effects;
static std::unique_ptr<kivsee_render::Animation> s_animation = nullptr;

// Utility function to log errors safely
void LogError(const char* message) {
    if (s_unityLog != nullptr) {
        s_unityLog->Log(kUnityLogTypeError, message, __FILE__, __LINE__);
    }
    printf("KivseeRender ERROR: %s\n", message);
}

void LogException(const std::exception& e) {
    if (s_unityLog != nullptr) {
        s_unityLog->Log(kUnityLogTypeException, e.what(), __FILE__, __LINE__);
    }
    printf("KivseeRender ERROR: %s\n", e.what());
}

// Unity plugin load callback
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    s_unityInterfaces = unityInterfaces;
     //function will get called by unity when it loads the plugin automatically
   
    //Get the unity log pointer once the Unity plugin gets loaded
    // Follow the same pattern for any other Unity interfaces you need
    s_unityLog = s_unityInterfaces->Get<IUnityLog>();


    printf("KivseeRender: Plugin loaded\n");
}

// Unity plugin unload callback
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
    // Clean up any resources
    s_segmentsMap.reset();
    s_ledsBuffer.clear();
    
    // Clear effects and animation
    for (auto effect : s_effects) {
        delete effect;
    }
    s_effects.clear();
    s_animation.reset();

    s_unityInterfaces = nullptr;
    s_unityLog = nullptr;
    printf("KivseeRender: Plugin unloaded\n");
}

// Simple function to add an int and a float
float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestAdd(int x, float y)
{
    return static_cast<float>(x) + y;
}

// Log a message from Unity
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestLog(const char* message)
{
    if (message)
    {
        s_unityLog->Log(kUnityLogTypeLog, message, __FILE__, __LINE__);
    }
}

// Get the size of the array that can be retrieved
int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestGetArraySize()
{
    return s_TestArraySize;
}

// Fill the provided array with test data
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestGetArray(int* outArray, int size)
{
    if (outArray && size > 0)
    {
        int copySize = (size < s_TestArraySize) ? size : s_TestArraySize;
        for (int i = 0; i < copySize; ++i)
        {
            outArray[i] = s_TestArray[i];
        }
    }
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestCppExceptionCaught()
{
    try {
        throw std::runtime_error("Test C++ exception caught");
    }
    catch (const std::exception& e) {
        LogException(e);
    }
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestCppExceptionUncaught()
{
    throw std::runtime_error("Test C++ exception - uncaught!");
}


// Simple example effect for testing
class SimpleColorEffect : public kivsee_render::Effect 
{
private:
    kivsee_render::HSV m_color;

protected:
    void Render(float rel_time, int cycle_index) override {
        // Apply the color to all pixels in the segment
        for (auto& pixel : *segment_pixels) {
            *(pixel.pixel) = m_color;
        }
    }

public:
    SimpleColorEffect(const kivsee_render::HSV& color) : m_color(color) {}
};

// Create a simple test segment map with hardcoded values
bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API CreateTestSegmentsMap()
{
    // Create a very simple test setup with one segment
    s_segmentsMap = std::make_unique<kivsee_render::segments::SegmentsMap>();
    s_segmentsMap->guid = 1;
    
    // Hardcoded LED count for testing
    const int ledCount = 30;
    s_segmentsMap->number_of_pixels = ledCount;
    
    // Resize the LED buffer
    s_ledsBuffer.resize(ledCount);
    
    // Create a test segment
    kivsee_render::segments::Segment segment;
    strcpy(segment.first, "test");  // Segment name
    
    // Add pixels to the segment
    for (int i = 0; i < ledCount; i++) {
        kivsee_render::segments::SegmentPixel pixel;
        pixel.pixel = &s_ledsBuffer[i];
        pixel.relativePositionInSegment = static_cast<float>(i) / ledCount;
        segment.second.push_back(pixel);
    }
    
    s_segmentsMap->segments.push_back(segment);
    
    return true;
}

// Get the total number of LEDs
int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetTotalLedCount()
{
    if (s_segmentsMap) {
        return s_segmentsMap->number_of_pixels;
    }
    return 0;
}

// Get the HSV values for all LEDs
bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetLedColors(float* hsvArray, int arraySize)
{
    if (!hsvArray || arraySize <= 0 || !s_segmentsMap) {
        return false;
    }
    
    int ledCount = s_segmentsMap->number_of_pixels;
    int valuesToCopy = std::min(arraySize / 3, static_cast<int>(s_ledsBuffer.size()));
    
    // Copy HSV values to the provided array (hue, sat, val, hue, sat, val, ...)
    for (int i = 0; i < valuesToCopy; i++) {
        hsvArray[i * 3] = s_ledsBuffer[i].hue;
        hsvArray[i * 3 + 1] = s_ledsBuffer[i].sat;
        hsvArray[i * 3 + 2] = s_ledsBuffer[i].val;
    }
    
    return true;
}

// Create a simple animation for testing
bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetSimpleAnimation(const char* segmentName, float hue, float duration, int numRepeats)
{
    if (!s_segmentsMap || !segmentName) {
        return false;
    }
    
    // Find the segment
    auto* segmentPixels = s_segmentsMap->getPixelsForSegment(segmentName);
    if (!segmentPixels) {
        return false;
    }
    
    // Clean up previous effects/animations
    for (auto effect : s_effects) {
        delete effect;
    }
    s_effects.clear();
    s_animation.reset();
    
    // Create a simple color effect
    auto* effect = new SimpleColorEffect(kivsee_render::HSV(hue, 1.0f, 1.0f));
    
    // Initialize the effect with our segment
    void* config = nullptr; // We don't need a config for our simple effect
    effect->Init(segmentPixels, config);
    
    // Add the effect to our list
    s_effects.push_back(effect);
    
    // Create an animation with this effect
    s_animation = std::make_unique<kivsee_render::Animation>(
        s_effects.begin(),
        s_effects.end(),
        static_cast<uint32_t>(duration * 1000), // Convert to milliseconds
        numRepeats
    );
    
    return true;
}

// Render a frame at the specified time
bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API RenderFrame(unsigned long timeMs)
{
    if (!s_animation) {
        return false;
    }
    
    // Render the animation frame
    auto stats = s_animation->Render(timeMs);
    
    return stats.is_rendering;
} 