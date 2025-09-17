# Create test executable
add_executable(test_tensor
    test_tensor_data.cpp
)

# Link with the main library
target_link_libraries(test_tensor PRIVATE ember)

# Register tests with CTest
add_test(NAME TensorTests COMMAND test_tensor)
