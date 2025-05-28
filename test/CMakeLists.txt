# Add test executable
add_executable(kivsee-render-tests
    test_main.cpp
    # Add your test source files here
)

# Link test executable with dependencies
target_link_libraries(kivsee-render-tests
    PRIVATE
    kivsee-render
    GTest::gtest_main
    GTest::gmock_main
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(kivsee-render-tests)