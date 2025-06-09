cmake_minimum_required(VERSION 3.10)
project(kivsee-render LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Add kivsee-proto dependency
FetchContent_Declare(
    kivsee-proto
    GIT_REPOSITORY https://github.com/KivSee/kivsee-proto.git
    GIT_TAG main
)
FetchContent_MakeAvailable(kivsee-proto)

# Add source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Create the main library target
add_library(kivsee-render STATIC ${SOURCES})
target_include_directories(kivsee-render PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(kivsee-render PUBLIC
    kivsee_proto_nanopb
)
