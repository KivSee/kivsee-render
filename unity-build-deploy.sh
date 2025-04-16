#!/bin/bash
set -e

# Take Unity deploy dir from args (using same format as PowerShell version)
UnityDeployDir=""
if [ "$1" == "-UnityDeployDir" ] && [ -n "$2" ]; then
    UnityDeployDir="$2"
else
    # If not explicitly set, use environment variable
    UnityDeployDir="$UNITY_PLUGIN_DIR"
fi

# Always build
echo "Building kivsee-render-unity..."
bazel build //:kivsee-render-unity
if [ $? -ne 0 ]; then
    echo "Error: Build failed" >&2
    exit 1
fi

# Only deploy if Unity plugin directory is specified
if [ -z "$UnityDeployDir" ]; then
    echo "No Unity deploy directory specified. Skipping deployment step."
    echo "To deploy, use: ./unity-build-deploy.sh -UnityDeployDir /path/to/Assets/Plugins"
else
    echo "Deploying to Unity directory: $UnityDeployDir"
    
    # Create destination directory if it doesn't exist
    mkdir -p "$UnityDeployDir"
    
    # Find the library in bazel-bin
    if [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS
        libName="libkivsee-render-unity.dylib"
    elif [[ "$OSTYPE" == "linux"* ]]; then
        # Linux
        libName="libkivsee-render-unity.so"
    else
        # Assume Windows
        libName="kivsee-render-unity.dll"
    fi
    
    # Use find to locate the library file in bazel-bin
    libPath=$(find bazel-bin -name "$libName" -type f | head -n 1)
    
    if [ -n "$libPath" ]; then
        targetFile="$UnityDeployDir/$libName"
        
        # Try to copy the library file directly
        if cp "$libPath" "$targetFile" 2>/dev/null; then
            echo "Deployment successful"
        else
            echo "Error: Couldn't replace the library file. It might be locked by Unity." >&2
            echo "Error: Close Unity and run this script again to update the library." >&2
        fi
    else
        echo "Error: Could not find $libName in bazel-bin directory"
        exit 1
    fi
fi 