#include <gtest/gtest.h>
#include "ember/tensor/tensor_data.h"

// -------------------------------
// Free function tests
// -------------------------------

TEST(HelperFunctionsTest, IndexToPosition) {
    std::vector<int> strides = {3, 1};     // 2D tensor flattened
    std::vector<int> index   = {1, 2};     // row=1, col=2
    EXPECT_EQ(index_to_position(index, strides), 5);

    // Edge case: zero index
    index = {0, 0};
    EXPECT_EQ(index_to_position(index, strides), 0);
}

TEST(HelperFunctionsTest, ShapeBroadcast) {
    std::vector<int> a = {1, 3};
    std::vector<int> b = {2, 3};
    auto result = shape_broadcast(a, b);
    EXPECT_EQ(result, (std::vector<int>{2, 3}));

    // Edge case: same shape
    a = {2, 3};
    b = {2, 3};
    EXPECT_EQ(shape_broadcast(a, b), (std::vector<int>{2, 3}));

    // Broadcasting scalar
    a = {1};
    b = {2, 3};
    EXPECT_EQ(shape_broadcast(a, b), (std::vector<int>{2, 3}));
}

TEST(HelperFunctionsTest, BroadcastIndex) {
    std::vector<int> big_index = {1, 2};
    std::vector<int> big_shape = {2, 3};
    std::vector<int> shape     = {2, 3};
    std::vector<int> out_index;

    broadcast_index(big_index, big_shape, shape, out_index);

    // Now check that out_index matches the expected result
    std::vector<int> expected = {1, 2};
    EXPECT_EQ(out_index, expected);
}


// -------------------------------
// TensorData tests
// -------------------------------

TEST(TensorDataTest, ConstructionAndAccess) {
    TensorData::Storage storage = {1, 2, 3, 4};
    TensorData::Shape shape = {2, 2};
    TensorData td(storage, shape);

    EXPECT_EQ(td.size(), 4);
    EXPECT_EQ(td.get({0,0}), 1);
    EXPECT_EQ(td.get({1,1}), 4);
}

TEST(TensorDataTest, SetAndGet) {
    TensorData::Storage storage = {0, 0, 0, 0};
    TensorData::Shape shape = {2, 2};
    TensorData td(storage, shape);

    td.set({0, 1}, 5);
    td.set({1, 0}, 7);

    EXPECT_EQ(td.get({0,1}), 5);
    EXPECT_EQ(td.get({1,0}), 7);
}

TEST(TensorDataTest, IsContiguousTrue) {
    TensorData::Storage storage = {1, 2, 3, 4};
    TensorData::Shape shape = {2, 2};
    TensorData td(storage, shape);

    EXPECT_TRUE(td.is_contiguous());
}

// TEST(TensorDataTest, IsContiguousFalse) {
//     TensorData::Storage storage = {1, 2, 3, 4, 5, 6};
//     TensorData::Shape shape = {2, 3};
//     TensorData td(storage, shape);

//     // Simulate a non-contiguous tensor (e.g., strides manually changed)
//     td.set_strides({1, 2}); // hypothetical API to force non-contiguity
//     EXPECT_FALSE(td.is_contiguous());
// }

TEST(TensorDataTest, OutOfBoundsAccess) {
    TensorData::Storage storage = {1, 2, 3, 4};
    TensorData::Shape shape = {2, 2};
    TensorData td(storage, shape);

    EXPECT_THROW(td.get({2,0}), std::out_of_range);
    EXPECT_THROW(td.get({0,2}), std::out_of_range);
    EXPECT_THROW(td.set({2,1}, 10), std::out_of_range);
}

TEST(TensorDataTest, MultiDimensional) {
    TensorData::Storage storage = {0,1,2,3,4,5,6,7};
    TensorData::Shape shape = {2,2,2};
    TensorData td(storage, shape);

    EXPECT_EQ(td.get({1,0,1}), 5);
    td.set({0,1,1}, 99);
    EXPECT_EQ(td.get({0,1,1}), 99);
}

TEST(TensorDataTest, ShapeBroadcastingIntegration) {
    TensorData::Storage a_storage = {1, 2};
    TensorData::Shape a_shape = {2,1};
    TensorData td_a(a_storage, a_shape);

    TensorData::Storage b_storage = {10, 20, 30};
    TensorData::Shape b_shape = {1,3};
    TensorData td_b(b_storage, b_shape);

    auto result_shape = shape_broadcast(a_shape, b_shape);
    EXPECT_EQ(result_shape, (std::vector<int>{2,3}));
}

