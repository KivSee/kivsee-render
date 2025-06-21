#include "interfaces/IUnityInterface.h"
#include "interfaces/IUnityLog.h"
#include "KivseeUnityPlugin.h"
#include "kivsee/proto/render/v1/segments.pb.h"
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

// Get the total number of LEDs
int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetTotalLedCount()
{
    if (segments_map) {
        return segments_map->number_of_pixels;
    }
    return 0;
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetSegmentsFromPB(const unsigned char* buffer, int bufferSize)
{
    Log("SetSegmentsFromPB");

    pb_istream_t segments_map_stream = pb_istream_from_buffer(buffer, bufferSize);
    ::kivsee_render::segments::SegmentsMapDecodeArgs segments_map_decode_args;
    segments_map_decode_args.out_segments_map = &segments_map;
    segments_map_decode_args.leds_array = leds;
    void *arg = &segments_map_decode_args;
    bool success = ::kivsee_render::segments::DecodeSegmentsMapFromPbStream(&segments_map_stream, nullptr, &arg);
    
    if (success && segments_map != nullptr) {
        char print_buf[100];
        sprintf(print_buf, "guid: %u", segments_map->guid);
        Log(print_buf);
        Log("Segments Initialized");

        sprintf(print_buf, "number of pixels: %u", segments_map->number_of_pixels);
        Log(print_buf);
    } else {
        LogError("Failed to decode segments map or segments_map is null");
        LogError(segments_map_stream.errmsg);
    }
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetAnimationFromPB(const unsigned char* buffer, int bufferSize)
{
    Log("SetAnimationFromPB");

    kivsee_render::DecodeAnimationArgs args = { segments_map };
    void *decodeArgs = &args;
    
    pb_istream_t animation_stream = pb_istream_from_buffer(buffer, bufferSize);
    bool success = ::kivsee_render::DecodeAnimationFromPbStream(&animation_stream, nullptr, &decodeArgs);

    // Turns decodeArgs into animation SOMEHOW
    animation = (::kivsee_render::Animation *)decodeArgs;
    
    if (!success || animation == nullptr) {
        LogError("Failed to decode animation or animation is null");
        LogError(animation_stream.errmsg);
        return;
    }

    if (animation->duration_ms == 0) {
        LogError("Invalid animation: duration is 0!");
        return;
    }

    char print_buf[100];
    sprintf(print_buf, "Animation decoded successfully. duration: %u", animation->duration_ms);
    Log(print_buf);
}

UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API RenderFrame(unsigned long timeMs)
{
    animation->Render(timeMs);
    return true;
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