#ifndef __KIVSEE_UNITY_PLUGIN_H__
#define __KIVSEE_UNITY_PLUGIN_H__

// Unity plugin interface
#include "IUnityInterface.h"

// C99 compatibility
#ifdef __cplusplus
extern "C" {
#endif

// Required Unity plugin interface functions
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces);
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload();

// Test functions
UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API Add(int x, float y);
UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API Log(const char* message);
UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API GetArraySize();
UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API GetArray(int* outArray, int size);

#ifdef __cplusplus
}
#endif

#endif // __KIVSEE_UNITY_PLUGIN_H__ 