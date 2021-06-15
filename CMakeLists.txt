cmake_minimum_required(VERSION 3.10)

project(kiv)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_TESTS "Build unit tests" OFF)
option(WITH_DEBUG_PRINTS "enable debug print macros" OFF)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("default build type: Release")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(GCC_FLAGS_EXTRA "-Wall -Wno-deprecated-declarations -Wno-stringop-truncation")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_FLAGS_EXTRA}")


set(KIV_LIBS protobuf-nanopb)

set(KIV_SOURCES "")

set(KIV_SOURCES ${KIV_SOURCES} ./src/functions/float_functions/float_function.cpp) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/color/const_color.cpp) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/color/rainbow.cpp) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/animation.cpp) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/effect.cpp) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/effect/brightness.cpp) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/effect/hue.cpp) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/effect/saturation.cpp) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/functions.pb.c) 
set(KIV_SOURCES ${KIV_SOURCES} ./src/effects.pb.c) 



# Enable debug prints
if (WITH_DEBUG_PRINTS)
  add_compile_options(-DDEBUG_HELPERS)
endif()

# 3rd party
#set(KIV_SOURCES ${KIV_SOURCES} libs/jsoncpp/jsoncpp.cc)

# main executable
add_executable(simulation ${KIV_SOURCES} src/simulation.cpp)
target_include_directories(simulation PUBLIC include)
target_link_libraries(simulation PUBLIC ${KIV_LIBS})


# Unit Tests
if (BUILD_TESTS)
  add_executable(test1 test/test1.cpp)
  target_include_directories(test1 PUBLIC include)

  enable_testing()
  add_test(NAME test1 COMMAND test1)
endif()

