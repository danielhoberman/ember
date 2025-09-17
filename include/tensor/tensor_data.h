#pragma once
#include <vector>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <string>
#include <random>

class IndexingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class TensorData {
public:
    using Storage = std::vector<float>;
    using Shape = std::vector<int>;
    using Strides = std::vector<int>;

private:
    Storage storage_;
    Shape shape_;
    Strides strides_;
    int dims_;
    int size_;

public:
    // Constructor
    TensorData(const Storage &storage, const Shape &shape, const Strides &strides = {});

    // -------------------------------
    // Element access
    // -------------------------------
    float get(const std::vector<int>& index) const;
    void set(const std::vector<int>& index, float value);

    // -------------------------------
    // Index conversions
    // -------------------------------
    int index_to_position(const std::vector<int>& index) const;
    std::vector<int> to_index(int ordinal) const;

    // -------------------------------
    // Utilities
    // -------------------------------
    bool is_contiguous() const;                          // check memory layout
    TensorData permute(const std::vector<int>& order) const;
    std::string to_string() const;                       // pretty-print

    // -------------------------------
    // Index helpers
    // -------------------------------
    int index(const std::vector<int>& index) const;      // validate + convert to position
    std::vector<std::vector<int>> indices() const;       // iterate all indices
    std::vector<int> sample() const;                     // random index

    // -------------------------------
    // Properties
    // -------------------------------
    const Shape& shape() const { return shape_; }
    const Strides& strides() const { return strides_; }
    const Storage& storage() const { return storage_; }
    int size() const { return size_; }

    std::tuple<Storage, Shape, Strides> tuple() const;   // return storage, shape, strides

    // -------------------------------
    // Static utilities
    // -------------------------------
    static Strides strides_from_shape(const Shape& shape);
    static Shape shape_broadcast(const Shape& shape1, const Shape& shape2);
};
