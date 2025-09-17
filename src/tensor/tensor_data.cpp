#include "ember/tensor/tensor_data.h"
#include <stdexcept>
#include <numeric>
#include <algorithm>

int index_to_position(const std::vector<int>& index, const std::vector<int>& strides) {
    /*
    Converts a multidimensional tensor `index` into a single-dimensional position in
    storage based on strides.
    */
    if (index.size() != strides.size()) {
        throw IndexingError("Strides size must match index");
    }

    int pos = 0;
    for (size_t i = 0; i < index.size(); i++) {
        pos += index[i] * strides[i];
    }
    return pos;
}

void to_index(int ordinal, const std::vector<int>& shape, std::vector<int>& out_index) {
    /*
    Convert an `ordinal` to an index in the `shape`.
    */
    for (int i = static_cast<int>(shape.size()) - 1; i >= 0; --i) {
        out_index[i] = ordinal % shape[i];
        ordinal /= shape[i];
    }
}

void broadcast_index(const std::vector<int>& big_index,
                     const std::vector<int>& big_shape,
                     const std::vector<int>& shape,
                     std::vector<int>& out_index) {
    /*
    Convert a `big_index` with `big_shape` to a smaller `out_index`
    with `shape` following broadcasting rules.
    */
    int offset = static_cast<int>(big_shape.size()) - static_cast<int>(shape.size());

    for (size_t i = 0; i < shape.size(); i++) {
        if (shape[i] == 1) {
            out_index[i] = 0; // broadcasted dimension
        } else {
            out_index[i] = big_index[i + offset];
        }
    }
}

std::vector<int> shape_broadcast(const std::vector<int>& shape1, const std::vector<int>& shape2) {
    /*
    Broadcast two shapes to create a new union shape.

    Args:
        shape1 : first shape
        shape2 : second shape

    Returns:
        broadcasted shape

    Raises:
        IndexingError : if cannot broadcast
    */
    std::vector<int> result;

    auto it1 = shape1.rbegin();
    auto it2 = shape2.rbegin();

    while (it1 != shape1.rend() || it2 != shape2.rend()) {
        int dim1 = (it1 != shape1.rend()) ? *it1 : 1;
        int dim2 = (it2 != shape2.rend()) ? *it2 : 1;

        if (dim1 == dim2 || dim1 == 1) {
            result.push_back(dim2);
        } else if (dim2 == 1) {
            result.push_back(dim1);
        } else {
            throw IndexingError("Cannot broadcast shapes.");
        }

        if (it1 != shape1.rend()) ++it1;
        if (it2 != shape2.rend()) ++it2;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<int> strides_from_shape(const std::vector<int>& shape) {
    std::vector<int> strides(shape.size());
    int offset = 1;

    for (int i = static_cast<int>(shape.size()) - 1; i >= 0; --i) {
        strides[i] = offset;
        offset *= shape[i];
    }
    return strides;
}



// Constructor
TensorData::TensorData(const Storage &storage,
                       const Shape &shape,
                       const Strides &strides)
    : storage_(storage),
      shape_(shape),
      dims_(static_cast<int>(shape.size())) {
    // 1. If strides are not provided, compute them using strides_from_shape
    if (strides.empty()) {
        strides_ = strides_from_shape(shape);
    } else {
        strides_ = strides;
    }

    // 2. Validate that strides.size() == shape.size()
    if (strides_.size() != shape.size()) {
        throw IndexingError("Strides size must match shape");
    }

    // 3. Compute size_ as the product of shape
    size_ = std::accumulate(shape.begin(), shape.end(),
                            1, std::multiplies<int>());

    // 4. Validate that storage_.size() == size_
    if (storage_.size() != static_cast<size_t>(size_)) {
        throw IndexingError("Storage size must match size");
    }
}

// -------------------------------
// Instance methods
// -------------------------------
int TensorData::index(const std::vector<int>& key) const {
    return index_to_position(key, strides_);
}

std::vector<std::vector<int>> TensorData::indices() const {
    // Generate all valid index tuples for this shape
    std::vector<std::vector<int>> all_indices;
    std::vector<int> out_index(shape_.size(), 0);

    for (int i = 0; i < size_; i++) {
        to_index(i, shape_, out_index);  // assume you have to_index(int, Shape, Index&)
        all_indices.push_back(out_index);
    }

    return all_indices;
}

std::vector<int> TensorData::sample() const {
    std::vector<int> key;
    key.reserve(shape_.size());
    for (int s : shape_) {
        key.push_back(rand() % s);  // use <random> for better RNG if needed
    }
    return key;
}

float TensorData::get(const std::vector<int>& key) const {
    return storage_[index(key)];
}

void TensorData::set(const std::vector<int>& key, float value) {
    storage_[index(key)] = value;
}

TensorData TensorData::permute(const std::vector<int>& order) const {
    // Validate permutation
    std::vector<int> sorted(order);
    std::sort(sorted.begin(), sorted.end());
    for (int i = 0; i < (int)shape_.size(); i++) {
        if (sorted[i] != i) {
            throw IndexingError("Invalid permutation order");
        }
    }

    // Apply permutation
    Shape new_shape, new_strides;
    for (int i : order) {
        new_shape.push_back(shape_[i]);
        new_strides.push_back(strides_[i]);
    }

    return TensorData(storage_, new_shape, new_strides);
}

// --- Utilities ---
bool TensorData::is_contiguous() const {
    int last = 1e9;  // large sentinel
    for (int stride : strides_) {
        if (stride > last) return false;
        last = stride;
    }
    return true;
}