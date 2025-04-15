#include "KivseeUnityPlugin.h"
#include <stdio.h>

// The Unity interface pointers
static IUnityInterfaces* s_UnityInterfaces = nullptr;

// Sample data for the GetArray function
static const int s_TestArray[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
static const int s_TestArraySize = sizeof(s_TestArray) / sizeof(s_TestArray[0]);

// Unity plugin load callback
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    s_UnityInterfaces = unityInterfaces;
    printf("KivseeRender: Plugin loaded\n");
}

// Unity plugin unload callback
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
    s_UnityInterfaces = nullptr;
    printf("KivseeRender: Plugin unloaded\n");
}

// Simple function to add an int and a float
float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API Add(int x, float y)
{
    return static_cast<float>(x) + y;
}

// Log a message from Unity
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API Log(const char* message)
{
    if (message)
    {
        printf("Unity message: %s\n", message);
    }
}

// Get the size of the array that can be retrieved
int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetArraySize()
{
    return s_TestArraySize;
}

// Fill the provided array with test data
void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetArray(int* outArray, int size)
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