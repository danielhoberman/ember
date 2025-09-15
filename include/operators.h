#pragma once
#include <cmath>

// =====================
// Header-only operators
// =====================

// Multiply two floats
inline float _mul(float a, float b) { return a * b; }

// Identity function (returns input unchanged)
inline float _id(float a) { return a; }

// Addition
inline float _add(float a, float b) { return a + b; }

// Negation (unary minus)
inline float _neg(float a) { return -a; }

// Less-than comparison: returns 1.0f if a < b, else 0.0f
inline float _lt(float a, float b) { return (a < b) ? 1.0f : 0.0f; }

// Equality comparison: returns 1.0f if a == b, else 0.0f
inline float _eq(float a, float b) { return (a == b) ? 1.0f : 0.0f; }

// Maximum of two floats
inline float _max(float a, float b) { return (a > b) ? a : b; }

// Check if two floats are close within a tolerance: returns 1.0f if close, else 0.0f
inline float _is_close(float a, float b, float tol = 1e-2f) {
    return (std::fabs(a - b) < tol);
}

// Compute the sigmoid function in a numerically stable way
inline float _sigmoid(float a) {
    return 1.0f / (1.0f + std::exp(-a));
}

// Compute the ReLU function: max(0, a)
inline float _relu(float a) {
    return (a > 0) ? a : 0.0f;
}

// Compute the natural logarithm of a
inline float _log(float a) { return std::log(a); }

// Compute the exponential of a (e^a)
inline float _exp(float a) { return std::exp(a); }

// Compute the multiplicative inverse (1/a) of a
inline float _inv(float a) { return 1.0f / a; }
