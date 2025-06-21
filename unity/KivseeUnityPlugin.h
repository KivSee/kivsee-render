#ifndef __KIVSEE_UNITY_PROTOBUF_H__
#define __KIVSEE_UNITY_PROTOBUF_H__

// Unity plugin interface
#include "interfaces/IUnityInterface.h"

// C99 compatibility
#ifdef __cplusplus
extern "C" { // No name mangling
#endif

// Required Unity plugin interface functions
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces);
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload();

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetSegmentsFromPB(const unsigned char* buffer, int bufferSize);
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetAnimationFromPB(const unsigned char* buffer, int bufferSize);

UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API GetTotalLedCount();
UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API RenderFrame(unsigned long timeMs);
UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API GetLedColors(float* hsvArray, int arraySize);

#ifdef __cplusplus
}
#endif

#endif // __KIVSEE_UNITY_PLUGIN_H__ 