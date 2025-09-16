from ember.nn.module import Module, Parameter
from ember.scalar import Scalar
import random


class Linear(Module):
    weights: list[list[Parameter]]
    bias: list[Parameter]

    def __init__(self, in_size: int, out_size: int) -> None:
        super().__init__()
        self.weights = []
        self.bias = []
        for i in range(in_size):
            self.weights.append([])
            for j in range(out_size):
                self.weights[i].append(
                    self.add_parameter(
                        f"weight_{i}_{j}", Scalar(2 * (random.random() - 0.5))
                    )
                )
        for j in range(out_size):
            self.bias.append(
                self.add_parameter(f"bias_{j}", Scalar(2 * (random.random() - 0.5)))
            )

    def forward(self, inputs: list[Scalar]) -> list[Scalar]:
        """
        Forward pass for a linear layer.

        Args:
            inputs: List of tinytorch.Scalar values of length in_size

        Returns:
            List of tinytorch.Scalar values of length out_size
        """
        y = [b.value for b in self.bias]
        for i, x in enumerate(inputs):
            for j in range(len(y)):
                y[j] = y[j] + x * self.weights[i][j].value
        return y
