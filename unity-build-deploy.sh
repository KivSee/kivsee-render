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
        backupFile="$UnityDeployDir/$libName.new"
        
        # First copy to a temporary file
        echo "Copying $libPath to $backupFile"
        cp "$libPath" "$backupFile"
        
        # Try to replace the original file
        {
            if [ -f "$targetFile" ]; then
                echo "Replacing existing library..."
                rm "$targetFile" && mv "$backupFile" "$targetFile"
                echo "Deployment successful (replaced existing library)"
            else
                # First-time deployment
                mv "$backupFile" "$targetFile"
                echo "Deployment successful (new installation)"
            fi
        } || {
            echo "Warning: Couldn't replace the library file. It might be locked by Unity."
            echo "A new version has been placed at $backupFile"
            echo "  1. The new library will be used after Unity restarts."
            echo "  2. Alternatively, you can close Unity and run this script again."
            echo "  3. Or manually rename the .new file to replace the original when Unity is closed."
        }
    else
        echo "Error: Could not find $libName in bazel-bin directory"
        exit 1
    fi
fi 