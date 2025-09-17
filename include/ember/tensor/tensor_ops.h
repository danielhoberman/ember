#pragma once
#include <vector>
#include <functional>
#include <tuple>
#include <stdexcept>
#include <cmath>
#include "tensor_data.h"



// -------------------------------
// Protocol / interface for map, zip, reduce
// -------------------------------
using UnaryFn = std::function<float(float)>;
using BinaryFn = std::function<float(float, float)>;

class TensorOps {
public:
    // -------------------------------
    // Higher-order functions
    // -------------------------------
    static std::function<void(TensorData&, const TensorData&)> map(UnaryFn fn);
    static std::function<void(TensorData&, const TensorData&, const TensorData&)> zip(BinaryFn fn);
    static std::function<void(TensorData&, const TensorData&, int)> reduce(BinaryFn fn, float start = 0.0f);

    static TensorData matrix_multiply(const TensorData& a, const TensorData& b);

    // Indicates if operations are CUDA-enabled
    static inline bool cuda = false;
};

// -------------------------------
// Backend wrapper
// -------------------------------
class TensorBackend {
public:
    TensorBackend(TensorOps* ops);

    // Maps
    std::function<void(TensorData&, const TensorData&)> neg_map;
    std::function<void(TensorData&, const TensorData&)> relu_map;
    std::function<void(TensorData&, const TensorData&)> sigmoid_map;
    std::function<void(TensorData&, const TensorData&)> log_map;
    std::function<void(TensorData&, const TensorData&)> id_map;

    // Zips
    std::function<void(TensorData&, const TensorData&, const TensorData&)> add_zip;
    std::function<void(TensorData&, const TensorData&, const TensorData&)> mul_zip;

    // Reduce
    std::function<void(TensorData&, const TensorData&, int)> add_reduce;

    std::function<TensorData(const TensorData&, const TensorData&)> matrix_multiply;

    bool cuda;
};

// -------------------------------
// SimpleOps implementation (skeleton)
// -------------------------------
class SimpleOps : public TensorOps {
public:
    static std::function<void(TensorData&, const TensorData&)> map(UnaryFn fn);
    static std::function<void(TensorData&, const TensorData&, const TensorData&)> zip(BinaryFn fn);
    static std::function<void(TensorData&, const TensorData&, int)> reduce(BinaryFn fn, float start = 0.0f);
    static TensorData matrix_multiply(const TensorData& a, const TensorData& b);

    static inline bool is_cuda = false;
};
