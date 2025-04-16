#include "KivseeUnityPlugin.h"
#include <stdio.h>
#include "interfaces/IUnityLog.h"
#include <stdexcept>

#ifdef _WIN32
#include <Windows.h>
#endif

// Include the kivsee-render library headers
#include <hsv.h>
#include <segments/segments_map.h>
#include <effect.h>
#include <effects.pb.h>
#include <animation.h>
#include <vector>
#include <list>
#include <memory>
#include <string>

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
// Flag to track if effects are currently owned by animation
static bool s_effectsOwnedByAnimation = false;

void Log(const char* message) {
    if (s_unityLog != nullptr) {
        s_unityLog->Log(kUnityLogTypeLog, message, __FILE__, __LINE__);
    }
}

// Utility function to log errors safely
void LogError(const char* message) {
    if (s_unityLog != nullptr) {
        s_unityLog->Log(kUnityLogTypeError, message, __FILE__, __LINE__);
    }
}

void LogException(const std::exception& e) {
    if (s_unityLog != nullptr) {
        s_unityLog->Log(kUnityLogTypeException, e.what(), __FILE__, __LINE__);
    }
}

// Unity plugin load callback
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    s_unityInterfaces = unityInterfaces;
     //function will get called by unity when it loads the plugin automatically
   
    //Get the unity log pointer once the Unity plugin gets loaded
    // Follow the same pattern for any other Unity interfaces you need
    s_unityLog = s_unityInterfaces->Get<IUnityLog>();


    Log("KivseeRender: Plugin loaded\n");
}

// Unity plugin unload callback
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
    // Clean up any resources
    s_segmentsMap.reset();
    s_ledsBuffer.clear();
    
    // Clear effects and animation
    if (!s_effectsOwnedByAnimation) {
        for (auto effect : s_effects) {
            delete effect;
        }
    }
    s_effects.clear();
    s_animation.reset();
    s_effectsOwnedByAnimation = false;

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

// Helper function that causes an exception indirectly
static void ThrowTestException()
{
    // Create a volatile variable to prevent compiler optimization
    volatile int* ptr = nullptr;
    // Dereference null pointer will cause an access violation exception at runtime
    // but won't be detected by static analysis as an explicit throw
    *ptr = 42;
}

// DOESNT WORK - This crashes Unity anyway...
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestCppExceptionCaught()
{
    try {
        ThrowTestException();
    }
    catch (const std::exception& e) {
        LogException(e);
    }
    catch (...) {
        LogError("Unknown error in TestCppExceptionCaught");
    }
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestCppExceptionUncaught()
{
    // Simply call the function that will cause an exception
    // No need for pragmas as we're not explicitly throwing
    ThrowTestException();
}

// Simple example effect for testing
class SimpleColorEffect : public kivsee_render::Effect 
{
private:
    kivsee_render::HSV m_color;

protected:
    void Render(float rel_time, int cycle_index) override {
        // Apply the color to all pixels in the segment
        if (segment_pixels == nullptr) {
            return;
        }
        
        for (auto& pixel : *segment_pixels) {
            if (pixel.pixel != nullptr) {
                *(pixel.pixel) = m_color;
            }
        }
    }

public:
    SimpleColorEffect(const kivsee_render::HSV& color) : m_color(color) {}
};

// Create a simple test segment map with the specified LED count
bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API CreateTestSegmentsMap(int ledCount)
{
    try {
        // Validate input
        if (ledCount <= 0) {
            ledCount = 30; // Default to 30 if an invalid count is provided
            LogError("Invalid LED count provided, using default (30)");
        }
        
        // Create a very simple test setup with one segment
        s_segmentsMap = std::make_unique<kivsee_render::segments::SegmentsMap>();
        s_segmentsMap->guid = 1;
        
        // Set the LED count
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
    catch (const std::exception& e) {
        LogException(e);
        return false;
    }
    catch (...) {
        LogError("Unknown error in CreateTestSegmentsMap");
        return false;
    }
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
    try {
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
    catch (const std::exception& e) {
        LogException(e);
        return false;
    }
    catch (...) {
        LogError("Unknown error in GetLedColors");
        return false;
    }
}

// Create a simple animation for testing - CRASH PROTECTION VERSION
bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetSimpleAnimation(const char* segmentName, float hue, float duration, int numRepeats)
{
    try {
        // Put a guard at the function beginning - print to stdout since we might not have Unity logging yet
        char logMsg[256];
        snprintf(logMsg, sizeof(logMsg), "SetSimpleAnimation: Starting with params: segmentName=%s, hue=%f, duration=%f, repeats=%d", 
            segmentName ? segmentName : "NULL", hue, duration, numRepeats);
        Log(logMsg);

        // Extra crash protection - check parameters before try block
        if (!segmentName) {
            Log("SetSimpleAnimation: NULL segment name");
            return false;
        }

        // Log entry to debug our call path
        snprintf(logMsg, sizeof(logMsg), "SetSimpleAnimation: segmentName=%s, hue=%f, duration=%f, repeats=%d", 
              segmentName, hue, duration, numRepeats);
        Log(logMsg);
        
        // Validate parameters
        if (!s_segmentsMap) {
            LogError("SetSimpleAnimation: No segments map created. Call CreateTestSegmentsMap first.");
            return false;
        }
        
        if (strlen(segmentName) == 0) {
            LogError("SetSimpleAnimation: Empty segment name");
            return false;
        }
        
        // Convert string parameter to local copy to avoid marshaling issues
        char localSegmentName[32];
        strncpy(localSegmentName, segmentName, sizeof(localSegmentName)-1);
        localSegmentName[sizeof(localSegmentName)-1] = '\0';
        
        // Find the segment
        auto* segmentPixels = s_segmentsMap->getPixelsForSegment(localSegmentName);
        if (!segmentPixels) {
            char errorMsg[256];
            snprintf(errorMsg, sizeof(errorMsg), "SetSimpleAnimation: Segment '%s' not found", localSegmentName);
            LogError(errorMsg);
            return false;
        }
        
        // Validate segment
        if (segmentPixels->empty()) {
            LogError("SetSimpleAnimation: Segment has no pixels");
            return false;
        }

        /// START -----------------------

        // Clean up previous effects/animations
        Log("SetSimpleAnimation: Cleaning up previous effects");
        
        // Reset the animation first which may hold references to effects
        s_animation.reset();
        
        // Only delete effects if they aren't owned by a now-destroyed animation
        if (!s_effectsOwnedByAnimation) {
            for (auto effect : s_effects) {
                delete effect;
            }
        }
        s_effects.clear();
        s_effectsOwnedByAnimation = false;
        
        // Create a simple color effect
        Log("SetSimpleAnimation: Creating new effect");
        
        auto* effect = new SimpleColorEffect(kivsee_render::HSV(hue, 1.0f, 1.0f));
        if (!effect) {
            LogError("SetSimpleAnimation: Failed to create effect");
            return false;
        }
        
        // Initialize the effect with our segment
        Log("SetSimpleAnimation: Initializing effect");
        
        // Create effect config with basic parameters
        EffectConfig effectConfig;
        effectConfig.start_time = 0;
        effectConfig.end_time = duration * 1000; // Convert to milliseconds
        effectConfig.repeat_num = numRepeats;
        effectConfig.repeat_start = 0.0f;
        effectConfig.repeat_end = 1.0f;
        void* config = &effectConfig;
        effect->Init(segmentPixels, config);
        
        // Add the effect to our list
        Log("SetSimpleAnimation: Adding effect to list");
        
        s_effects.push_back(effect);
        
        // Validate duration and repeats
        if (duration <= 0) {
            LogError("SetSimpleAnimation: Invalid duration");
            return false;
        }
        
        if (numRepeats < 0) {
            LogError("SetSimpleAnimation: Invalid repeat count");
            return false;
        }
        
        // Create an animation with this effect
        Log("SetSimpleAnimation: Creating animation");
        
        /// END --------------------------
        
        try {
            // Extra safety with nested try/catch
            s_animation = std::make_unique<kivsee_render::Animation>(
                s_effects.begin(),
                s_effects.end(),
                static_cast<uint32_t>(duration * 1000), // Convert to milliseconds
                numRepeats
            );
            
            // Mark effects as owned by animation now
            s_effectsOwnedByAnimation = true;
        }
        catch (const std::exception& e) {
            LogException(e);
            LogError("SetSimpleAnimation: Exception creating animation object");
            return false;
        }
        catch (...) {
            LogError("SetSimpleAnimation: Unknown exception creating animation object");
            return false;
        }
        
        if (!s_animation) {
            LogError("SetSimpleAnimation: Failed to create animation");
            return false;
        }
        
        printf("SetSimpleAnimation: Completed successfully\n");
        fflush(stdout);
        return true;
    }
    catch (const std::exception& e) {
        LogException(e);
        printf("SetSimpleAnimation: Exception: %s\n", e.what());
        fflush(stdout);
        return false;
    }
    catch (...) {
        LogError("SetSimpleAnimation: Unknown error");
        printf("SetSimpleAnimation: Unknown exception\n");
        fflush(stdout);
        return false;
    }
}

// Render a frame at the specified time
bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API RenderFrame(unsigned long timeMs)
{
    try {
        if (!s_animation) {
            return false;
        }
        
        // Render the animation frame
        auto stats = s_animation->Render(timeMs);
        
        return stats.is_rendering;
    }
    catch (const std::exception& e) {
        LogException(e);
        return false;
    }
    catch (...) {
        LogError("Unknown error in RenderFrame");
        return false;
    }
} 