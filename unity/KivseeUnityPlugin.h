#ifndef __KIVSEE_UNITY_PLUGIN_H__
#define __KIVSEE_UNITY_PLUGIN_H__

// Unity plugin interface
#include "interfaces/IUnityInterface.h"

// C99 compatibility
#ifdef __cplusplus
extern "C" {
#endif

// Required Unity plugin interface functions
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces);
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload();

// Test functions
UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API TestAdd(int x, float y);
UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API TestLog(const char* message);
UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API TestGetArraySize();
UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API TestGetArray(int* outArray, int size);
UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API TestCppExceptionCaught();
UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API TestCppExceptionUncaught();

// LED Rendering API functions
UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API CreateTestSegmentsMap(int ledCount);
UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API GetTotalLedCount();
UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API GetLedColors(float* hsvArray, int arraySize);
UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API SetSimpleAnimation(const char* segmentName, float hue, float duration, int numRepeats);
UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API RenderFrame(unsigned long timeMs);

#ifdef __cplusplus
}
#endif

#endif // __KIVSEE_UNITY_PLUGIN_H__ 