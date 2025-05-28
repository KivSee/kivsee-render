cmake_minimum_required(VERSION 3.5)
project(kivsee-render VERSION 0.1.10 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add nanopb
set(nanopb_BUILD_GENERATOR OFF CACHE BOOL "Don't build nanopb generator")
include(FetchContent)
FetchContent_Declare(
    nanopb
    GIT_REPOSITORY https://github.com/nanopb/nanopb.git
    GIT_TAG nanopb-0.4.9
)
FetchContent_MakeAvailable(nanopb)

# Create nanopb library
add_library(protobuf-nanopb STATIC
    ${nanopb_SOURCE_DIR}/pb_common.c
    ${nanopb_SOURCE_DIR}/pb_decode.c
    ${nanopb_SOURCE_DIR}/pb_encode.c
)
target_include_directories(protobuf-nanopb
    PUBLIC
        $<BUILD_INTERFACE:${nanopb_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# Add source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.pb.c"
)

# Add header files
file(GLOB_RECURSE HEADERS
    "include/*.h"
)

# Create the main library target
add_library(kivsee-render STATIC ${SOURCES} ${HEADERS})
target_include_directories(kivsee-render PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${nanopb_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Link dependencies
target_link_libraries(kivsee-render PUBLIC
    protobuf-nanopb
)

# Install rules
install(TARGETS kivsee-render protobuf-nanopb
    EXPORT kivsee-render-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Export targets
install(EXPORT kivsee-render-targets
    FILE kivsee-render-targets.cmake
    NAMESPACE kivsee-render::
    DESTINATION lib/cmake/kivsee-render
)

# Create and install package configuration files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/kivsee-render-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/kivsee-render-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/kivsee-render-config.cmake"
    INSTALL_DESTINATION lib/cmake/kivsee-render
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/kivsee-render-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/kivsee-render-config-version.cmake"
    DESTINATION lib/cmake/kivsee-render
)