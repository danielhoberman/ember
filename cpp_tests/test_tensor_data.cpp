#include <iostream>
#include <cassert>
#include "ember/tensor/tensor_data.h"

int main() {
    ember::tensor::TensorData td({1.0, 2.0, 3.0, 4.0}, {2, 2});

    // Check shape
    assert(td.shape()[0] == 2);
    assert(td.shape()[1] == 2);

    // Check get/set
    td.set({0, 1}, 10.0);
    assert(td.get({0, 1}) == 10.0);

    std::cout << "TensorData test passed!\n";
    return 0;
}
