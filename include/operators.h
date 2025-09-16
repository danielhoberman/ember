#pragma once
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace fwd {

// Basic math
inline float mul(float a, float b) { return a * b; }
inline float add(float a, float b) { return a + b; }
inline float neg(float a) { return -a; }
inline float id(float a) { return a; }
inline float max(float a, float b) { return std::max(a, b); }

// Comparisons (numeric style: return 0.0f / 1.0f)
inline float lt(float a, float b) { return (a < b) ? 1.0f : 0.0f; }
inline float eq(float a, float b) { return (a == b) ? 1.0f : 0.0f; }
inline float is_close(float a, float b, float tol = 2e-1f) {
    return (std::fabs(a - b) < tol) ? 1.0f : 0.0f;
}

// Activations
inline float relu(float a) { return (a > 0.0f) ? a : 0.0f; }

// Exponentials and logs
inline float exp(float a) { return std::exp(a); }

inline float log(float a) {
    if (a <= 0.0f) throw std::domain_error("log: input must be > 0");
    return std::log(a);
}

inline float inv(float a) {
    if (a == 0.0f) throw std::domain_error("inv: division by zero");
    return 1.0f / a;
}

// Numerically stable sigmoid
inline float sigmoid(float a) {
    if (a >= 0.0f) {
        float z = std::exp(-a);
        return 1.0f / (1.0f + z);
    } else {
        float z = std::exp(a);
        return z / (1.0f + z);
    }
}

} // namespace fwd


namespace bwd {

// Backward ops
inline float log(float a, float grad) { return grad / a; }
inline float inv(float a, float grad) { return -grad / (a * a); }

inline float relu(float a, float grad) {
    return (a > 0.0f) ? grad : 0.0f;
}


inline float sigmoid(float a, float grad) {
    float s = fwd::sigmoid(a);
    return grad * s * (1.0f - s);
}

inline float exp(float a, float grad) { return grad * fwd::exp(a); }

} // namespace bwd
