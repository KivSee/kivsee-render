#!/usr/bin/env pwsh
param ([string]$UnityDeployDir = $env:UNITY_PLUGIN_DIR)

# Always build
Write-Host "Building kivsee-render-unity..."
bazel build //:kivsee-render-unity

# Only deploy if Unity plugin directory is specified
if ([string]::IsNullOrEmpty($UnityDeployDir)) {
    Write-Host "No Unity deploy directory specified. Skipping deployment step."
    Write-Host "To deploy, use: ./unity-build-deploy.ps1 -UnityDeployDir 'C:\path\to\Assets\Plugins'"
} else {
    Write-Host "Deploying to Unity directory: $UnityDeployDir"
    
    # Create destination directory if it doesn't exist
    if (-not (Test-Path -Path $UnityDeployDir)) {
        New-Item -ItemType Directory -Path $UnityDeployDir -Force | Out-Null
        Write-Host "Created directory: $UnityDeployDir"
    }
    
    # Find the DLL in bazel-bin
    $dllPath = Get-ChildItem -Path "bazel-bin" -Filter "kivsee-render-unity.dll" -Recurse -ErrorAction SilentlyContinue | 
                Select-Object -First 1 -ExpandProperty FullName
    
    if ($dllPath) {
        $targetFile = "$UnityDeployDir\kivsee-render-unity.dll"
        $backupFile = "$UnityDeployDir\kivsee-render-unity.dll.new"
        
        # First copy to a temporary file
        Write-Host "Copying $dllPath to $backupFile"
        Copy-Item -Path $dllPath -Destination $backupFile -Force
        
        try {
            # Try to replace the original file
            if (Test-Path -Path $targetFile) {
                Write-Host "Replacing existing DLL..."
                Remove-Item -Path $targetFile -Force -ErrorAction Stop
                Rename-Item -Path $backupFile -NewName "kivsee-render-unity.dll" -ErrorAction Stop
                Write-Host "Deployment successful (replaced existing DLL)"
            } else {
                # First-time deployment
                Rename-Item -Path $backupFile -NewName "kivsee-render-unity.dll" -ErrorAction Stop
                Write-Host "Deployment successful (new installation)"
            }
        } catch {
            Write-Host "Warning: Couldn't replace the DLL file. It might be locked by Unity." -ForegroundColor Yellow
            Write-Host "A new version has been placed at $backupFile" -ForegroundColor Yellow
            Write-Host "  1. The new DLL will be used after Unity restarts."
            Write-Host "  2. Alternatively, you can close Unity and run this script again."
            Write-Host "  3. Or manually rename the .new file to replace the original when Unity is closed."
        }
    } else {
        Write-Host "Error: Could not find kivsee-render-unity.dll in bazel-bin directory" -ForegroundColor Red
        exit 1
    }
} 