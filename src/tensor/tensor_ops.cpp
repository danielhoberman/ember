#include "ember/tensor/tensor_ops.h"
#include <iostream>
#include <algorithm>

// -------------------------------
// TensorOps
// -------------------------------
std::function<void(TensorData&, const TensorData&)> TensorOps::map(UnaryFn fn) {
    // TODO:
    // Implement tensor_map logic.
    // Apply `fn` to each element of input TensorData and write to output TensorData.
    return [](TensorData& out, const TensorData& in) {
        // Example:
        // for each element i in in.storage():
        //   out.storage()[i] = fn(in.storage()[i])
    };
}

std::function<void(TensorData&, const TensorData&, const TensorData&)> TensorOps::zip(BinaryFn fn) {
    // TODO:
    // Implement tensor_zip logic.
    // Apply fn(a[i], b[i]) and write to out[i], handling broadcasting.
    return [](TensorData& out, const TensorData& a, const TensorData& b) {
        // Example:
        // 1. Compute broadcasted shape
        // 2. Iterate over all output indices
        // 3. Map each index to a and b using broadcasting rules
        // 4. Apply fn and store in out
    };
}

std::function<void(TensorData&, const TensorData&, int)> TensorOps::reduce(BinaryFn fn, float start) {
    // TODO:
    // Implement tensor_reduce logic along dimension `dim`
    return [start, fn](TensorData& out, const TensorData& in, int dim) {
        // Example:
        // 1. Determine output shape (reduce dim -> 1)
        // 2. Iterate along dim and apply fn cumulatively
        // 3. Store result in out
    };
}

TensorData TensorOps::matrix_multiply(const TensorData& a, const TensorData& b) {
    throw std::runtime_error("matrix_multiply not implemented");
}

// -------------------------------
// TensorBackend
// -------------------------------
TensorBackend::TensorBackend(TensorOps* ops) {
    // TODO: Assign operations from TensorOps
    // Example:
    // neg_map = ops->map([](float x){ return -x; });
    cuda = ops->cuda;
}

// -------------------------------
// SimpleOps
// -------------------------------
std::function<void(TensorData&, const TensorData&)> SimpleOps::map(UnaryFn fn) {
    // TODO: implement tensor_map logic for SimpleOps
    return TensorOps::map(fn);
}

std::function<void(TensorData&, const TensorData&, const TensorData&)> SimpleOps::zip(BinaryFn fn) {
    // TODO: implement tensor_zip logic for SimpleOps
    return TensorOps::zip(fn);
}

std::function<void(TensorData&, const TensorData&, int)> SimpleOps::reduce(BinaryFn fn, float start) {
    // TODO: implement tensor_reduce logic for SimpleOps
    return TensorOps::reduce(fn, start);
}

TensorData SimpleOps::matrix_multiply(const TensorData& a, const TensorData& b) {
    throw std::runtime_error("matrix_multiply not implemented");
}
