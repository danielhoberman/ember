#pragma once
#include <vector>
#include <stdexcept>
#include <numeric>   // for std::accumulate
#include <algorithm> // for std::max

// Custom exception for invalid tensor indexing
class IndexingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Tensor metadata + storage container
class TensorData {
public:
    using Storage = std::vector<float>;   // float32 storage (could be replaced with custom allocator)
    using Shape   = std::vector<int>;     // list of dimension sizes
    using Strides = std::vector<int>;     // how to move in memory along each dimension

private:
    Storage storage_;
    Shape shape_;
    Strides strides_;
    int dims_;   // number of dimensions (rank)
    int size_;   // total number of elements

public:
    // Constructor
    TensorData(const Storage &storage, const Shape &shape, const Strides &strides = {});

    // --- Accessors ---
    float get(const std::vector<int>& index) const;         // TODO: convert index → flat position, return storage value
    void set(const std::vector<int>& index, float value);   // TODO: convert index → flat position, assign value

    // --- Utilities ---
    bool is_contiguous() const;                   // TODO: check if strides match row-major layout
    TensorData permute(const std::vector<int>& order) const; // TODO: return a new TensorData with permuted dims/strides             // TODO: compute row-major strides

    // Properties
    const Shape& shape() const { return shape_; }
    const Strides& strides() const { return strides_; }
};
