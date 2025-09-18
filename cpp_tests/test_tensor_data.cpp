#include <gtest/gtest.h>
#include "ember/tensor/tensor_data.h"

// -------------------------------
// Free function tests
// -------------------------------
TEST(HelperFunctionsTest, IndexToPosition) {
    std::vector<int> strides = {3, 1};     // 2D tensor flattened
    std::vector<int> index   = {1, 2};     // row=1, col=2
    EXPECT_EQ(index_to_position(index, strides), 5);
}

TEST(HelperFunctionsTest, ShapeBroadcast) {
    std::vector<int> a = {1, 3};
    std::vector<int> b = {2, 3};
    auto result = shape_broadcast(a, b);
    EXPECT_EQ(result, (std::vector<int>{2, 3}));
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

TEST(TensorDataTest, IsContiguousTrue) {
    TensorData::Storage storage = {1, 2, 3, 4};
    TensorData::Shape shape = {2, 2};
    TensorData td(storage, shape);

    EXPECT_TRUE(td.is_contiguous());
}
