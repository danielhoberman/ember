#pragma once

class Scalar {
public:
    float value;
    float grad;
    bool requires_grad;

    Scalar(float val, bool req_grad = false);

    Scalar operator+(const Scalar& other);
    void backward();
};
