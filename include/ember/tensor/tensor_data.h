#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <tuple>
#include <random>

// -------------------------------
// Exception
// -------------------------------
class IndexingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// -------------------------------
// Helper functions (not methods)
// -------------------------------

// Converts a multidimensional index into a single storage position
int index_to_position(const std::vector<int>& index,
                      const std::vector<int>& strides);

// Converts an ordinal to an index (fills out_index in-place)
void to_index(int ordinal,
              const std::vector<int>& shape,
              std::vector<int>& out_index);

// Broadcasts a big_index down to out_index following broadcasting rules
void broadcast_index(const std::vector<int>& big_index,
                     const std::vector<int>& big_shape,
                     const std::vector<int>& shape,
                     std::vector<int>& out_index);

// Pure helper version of shape_broadcast
std::vector<int> shape_broadcast(const std::vector<int>& shape1,
                                 const std::vector<int>& shape2);

// Pure helper version of strides_from_shape
std::vector<int> strides_from_shape(const std::vector<int>& shape);


// -------------------------------
// TensorData class
// -------------------------------
class TensorData {
public:
    using Storage = std::vector<float>;
    using Shape   = std::vector<int>;
    using Strides = std::vector<int>;

private:
    Storage storage_;
    Shape shape_;
    Strides strides_;
    int dims_;
    int size_;

public:
    // Constructor
    TensorData(const Storage &storage,
               const Shape &shape,
               const Strides &strides = {});

    // -------------------------------
    // Instance methods
    // -------------------------------
    int index(const std::vector<int>& key) const;
    std::vector<std::vector<int>> indices() const;
    std::vector<int> sample() const;

    float get(const std::vector<int>& key) const;
    void set(const std::vector<int>& key, float value);

    TensorData permute(const std::vector<int>& order) const;

    bool is_contiguous() const;

    // -------------------------------
    // Properties
    // -------------------------------
    const Shape& shape() const { return shape_; }
    const Strides& strides() const { return strides_; }
    const Storage& storage() const { return storage_; }
    int size() const { return size_; }

    std::tuple<Storage, Shape, Strides> tuple() const {
        return std::make_tuple(storage_, shape_, strides_);
    }


    // -------------------------------
    // Static methods
    // -------------------------------
    static TensorData::Shape shape_broadcast(const TensorData::Shape& shape1,
                                         const TensorData::Shape& shape2) {
    return ::shape_broadcast(shape1, shape2);
    }
};
