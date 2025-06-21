# Unity Support
Files and Config related to  use in the Unity Visualizer.

## Resources
https://docs.unity3d.com/6000.0/Documentation/Manual/plug-ins-native.html

### Unity's Native Plugin Example Repo
https://github.com/Unity-Technologies/NativeRenderingPlugin/tree/master

#### Calling Unity from C++
The library (this project) can call unity functions using the Plugin API.
You can find it in the example repo, but the best way is to grab one from your Unity Editor installation:

`<UNITY_EDITOR_FOLDER>/Data/PluginAPI`

#### C++ function declaration examples
https://github.com/Unity-Technologies/NativeRenderingPlugin/blob/master/PluginSource/source/RenderingPlugin.cpp


#### Usage Within Unity
https://github.com/Unity-Technologies/NativeRenderingPlugin/blob/master/UnityProject/Assets/UseRenderingPlugin.cs