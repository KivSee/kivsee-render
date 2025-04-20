#include "interfaces/IUnityInterface.h"
#include "interfaces/IUnityLog.h"
#include "NewUnityPlugin.h"
#include "segments.pb.h"
#include "segments/segments_map.h"
#include "hsv.h"
#include <pb_decode.h>
#include <memory>
#include <animation.h>

// TODO: Set this according to segments
#define LED_COUNT_HACK 144

// TODO: Tidy up old logic (KivSeeUnityPlugin.cpp)
// TODO: refactor into class
static kivsee_render::Animation *animation;
static kivsee_render::segments::SegmentsMap *segments_map;


// The Unity interface pointers
static IUnityInterfaces* s_unityInterfaces = nullptr;
static IUnityLog* s_unityLog = nullptr;

static kivsee_render::HSV leds[LED_COUNT_HACK];

// Unity Logging
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


    Log("KivSeeRender: Plugin loaded\n");
}

// Unity plugin unload callback
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
    Log("KivSeeRender: PluginUnloading...");
    // Clean up any resources
    segments_map = nullptr;
    
    delete animation;
    animation = nullptr;

    delete segments_map;
    segments_map = nullptr;

    s_unityInterfaces = nullptr;
    s_unityLog = nullptr;
    Log("KivSeeRender: PluginUnloaded");
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetAnimationFromPB(const unsigned char* buffer, int bufferSize)
{
    Log("SetAnimationFromPB");
    
    pb_istream_t animation_stream = pb_istream_from_buffer(buffer, bufferSize);
    void *arg_animation = &animation;
    ::kivsee_render::DecodeAnimationFromPbStream(&animation_stream, nullptr, &arg_animation);
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetSegmentsFromPB(const unsigned char* buffer, int bufferSize)
{
    Log("SetSegmentsFromPB");

    pb_istream_t segments_map_stream = pb_istream_from_buffer(buffer, bufferSize);
    ::kivsee_render::segments::SegmentsMapDecodeArgs segments_map_decode_args;
    segments_map_decode_args.out_segments_map = &segments_map;
    segments_map_decode_args.leds_array = leds;
    void *arg = &segments_map_decode_args;
    ::kivsee_render::segments::DecodeSegmentsMapFromPbStream(&segments_map_stream, nullptr, &arg);
    char print_buf[100];
    sprintf(print_buf, "guid: %d", segments_map->guid);
    Log(print_buf);


    Log("Segments Initialized");
}

// Get the total number of LEDs
int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetTotalLedCount()
{
    if (segments_map) {
        return segments_map->number_of_pixels;
    }
    return 0;
}

// Get the HSV values for all LEDs
bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetLedColors(float* hsvArray, int arraySize)
{
    try {
        if (!hsvArray || arraySize <= 0 || !segments_map) {
            return false;
        }
        
        int valuesToCopy = std::min(arraySize / 3, LED_COUNT_HACK);
        
        // Copy HSV values to the provided array (hue, sat, val, hue, sat, val, ...)
        for (int i = 0; i < valuesToCopy; i++) {
            hsvArray[i * 3] = leds[i].hue;
            hsvArray[i * 3 + 1] = leds[i].sat;
            hsvArray[i * 3 + 2] = leds[i].val;
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