cmake_minimum_required(VERSION 3.5)
project(simulation-service VERSION 0.1.10 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Set default installation prefix to a local directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "Installation Directory" FORCE)
endif()

# Add kivsee-render as a subdirectory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/kivsee-render)

# Add httplib
include(FetchContent)
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.14.1
)
FetchContent_MakeAvailable(httplib)

# Add nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Add cpp-base64
FetchContent_Declare(
    cpp-base64
    GIT_REPOSITORY https://github.com/ReneNyffenegger/cpp-base64.git
    GIT_TAG V2.rc.08
)
FetchContent_MakeAvailable(cpp-base64)

# Create cpp-base64 library
add_library(cpp-base64-lib STATIC
    ${cpp-base64_SOURCE_DIR}/base64.cpp
)
target_include_directories(cpp-base64-lib PUBLIC ${cpp-base64_SOURCE_DIR})

# Create led_controller library
add_library(led_controller
    include/led_controller.h
    src/led_controller.cpp
)
target_include_directories(led_controller PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(led_controller
    kivsee-render
)

# Create simulation_service executable
add_executable(simulation_service
    src/main.cpp
)
target_link_libraries(simulation_service
    led_controller
    kivsee-render
    httplib
    nlohmann_json::nlohmann_json
    cpp-base64-lib
)
if(WIN32)
    target_compile_definitions(simulation_service PRIVATE _WIN32_WINNT=0x0601)
else()
    target_link_libraries(simulation_service pthread)
endif()

# Install rules
install(TARGETS simulation_service
    RUNTIME DESTINATION bin
)