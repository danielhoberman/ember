#include "scalar.h"

Scalar::Scalar(float val, bool req_grad) 
    : value(val), grad(0.0f), requires_grad(req_grad) {}

Scalar Scalar::operator+(const Scalar& other) {
    return Scalar(value + other.value, requires_grad || other.requires_grad);
}

void Scalar::backward() {
    if (requires_grad) grad = 1.0f;  // very simple example
}
