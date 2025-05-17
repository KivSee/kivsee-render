"""Platform constraint definitions for kivsee-render."""

CONSTRAINTS = {
    "linux_x86_64": [
        "@platforms//os:linux",
        "@platforms//cpu:x86_64",
    ],
    "linux_aarch64": [
        "@platforms//os:linux",
        "@platforms//cpu:aarch64",
    ],
    "linux_armv7": [
        "@platforms//os:linux",
        "@platforms//cpu:armv7",
    ],
    "macos_x86_64": [
        "@platforms//os:macos",
        "@platforms//cpu:x86_64",
    ],
    "macos_arm64": [
        "@platforms//os:macos",
        "@platforms//cpu:aarch64",
    ],
    "windows_x86_64": [
        "@platforms//os:windows",
        "@platforms//cpu:x86_64",
    ],
} 