# KivSee Render

A C++ rendering library for KivSee, with Unity integration.

## Building

To build the library:

```bash
bazel build //kivsee-render:kivsee-render
```

To build the Unity plugin DLL:

```bash
bazel build //:kivsee-render-unity
```

## Deploying to Unity

The library needs to be deployed to your Unity project's Plugins directory. Use the provided scripts:

**Windows PowerShell:**
```powershell
# Build, optionally deploy
./unity-build-deploy.ps1 [-UnityDeployDir "C:\path\to\UnityProject\Assets\Plugins\KivSee"]
```

**Bash:**
```bash
# Build, optionally deploy
./unity-build-deploy.sh [-UnityDeployDir /path/to/UnityProject/Assets/Plugins/KivSee]
```

**Note about Unity DLL locking:** If Unity is running when you deploy, it might lock the DLL file, preventing direct replacement. The scripts handle this by placing a `.new` file alongside the original, which will be used when Unity restarts.

### Manual Build

If you prefer to build without scripts:

```bash
# Just build the Unity plugin
bazel build //:kivsee-render-unity

# Then manually copy from bazel-bin to your Unity Plugins directory
```

## Testing

Run the tests:

```