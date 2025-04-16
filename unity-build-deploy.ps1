#!/usr/bin/env pwsh
param ([string]$UnityDeployDir = $env:UNITY_PLUGIN_DIR)

# Always build
Write-Host "Building kivsee-render-unity..."
bazel build //:kivsee-render-unity
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: Build failed" -ForegroundColor Red
    exit 1
}

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
        
        try {
            # Try to copy the DLL directly
            Copy-Item -Path $dllPath -Destination $targetFile -Force -ErrorAction Stop
            Write-Host "Deployment successful"
        } catch {
            Write-Host "Error: Couldn't replace the DLL file. It might be locked by Unity." -ForegroundColor Red
            Write-Host "Error: Close Unity and run this script again to update the DLL."
        }
    } else {
        Write-Host "Error: Could not find kivsee-render-unity.dll in bazel-bin directory" -ForegroundColor Red
        exit 1
    }
} 