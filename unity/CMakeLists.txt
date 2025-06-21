cmake_minimum_required(VERSION 3.10)
project(kivsee-unity-plugin VERSION 0.1.10 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Glob all C++ source files in the unity directory
file(GLOB UNITY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Add kivsee-render as a subdirectory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/kivsee-render)

# Create the Unity plugin library
add_library(kivsee-unity-plugin MODULE ${UNITY_SOURCES})

# macOS-specific plug-in tweaks
if(APPLE)
    # Produce a .bundle, not .so/.dylib
    set_target_properties(kivsee-unity-plugin PROPERTIES
        SUFFIX ".bundle")

    # Universal binary - Intel + Apple-silicon
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)

    # OPTIONAL: remove "lib" prefix
    set_target_properties(kivsee-unity-plugin PROPERTIES PREFIX "")
endif()

# Set include directories for the Unity plugin
target_include_directories(kivsee-unity-plugin PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Link against the kivsee-render library
target_link_libraries(kivsee-unity-plugin
    kivsee-render
)
