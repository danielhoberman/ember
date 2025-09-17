#include "ember/tensor/tensor_data.h"
#include <iostream>

int main() {
    using TD = TensorData;

    TD::Storage data = {1,2,3,4,5,6};
    TD::Shape shape = {2,3};
    TD tensor(data, shape);

    std::cout << "Size: " << tensor.size() << "\n";

    // Access elements
    for (const auto& idx : tensor.indices()) {
        std::cout << "(";
        for (int i : idx) std::cout << i << " ";
        std::cout << "): " << tensor.get(idx) << "\n";
    }

    // Sample
    auto s = tensor.sample();
    std::cout << "Sampled index: ";
    for (int i : s) std::cout << i << " ";
    std::cout << "\n";

    // Permute
    TD permuted = tensor.permute({1,0});
    std::cout << "Permuted shape: ";
    for (int dim : permuted.shape()) std::cout << dim << " ";
    std::cout << "\n";

    // Contiguous
    std::cout << "Is contiguous: " << tensor.is_contiguous() << "\n";

    return 0;
}
