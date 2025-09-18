add_executable(unit_tests test_tensor_data.cpp)

target_link_libraries(unit_tests
    PRIVATE
        ember
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
