from typing import Sequence

from ember.nn.module import Parameter
from ember.scalar import Scalar


class Optimizer:
    def __init__(self, parameters: Sequence[Parameter]):
        self.parameters = parameters


class SGD(Optimizer):
    def __init__(self, parameters: Sequence[Parameter], lr: float = 1.0):
        super().__init__(parameters)
        self.lr = lr

    def zero_grad(self) -> None:
        """Reset derivatives or grads of all parameters to None."""
        for p in self.parameters:
            if p.value is None:
                continue

            # reset derivative if it exists
            deriv = getattr(p.value, "derivative", None)
            if deriv is not None:
                p.value.derivative = None

            # reset grad if it exists
            grad = getattr(p.value, "grad", None)
            if grad is not None:
                p.value.grad = None

    def step(self) -> None:
        """Update parameters using SGD rule."""
        for p in self.parameters:
            if p.value is None:
                continue

            deriv = getattr(p.value, "derivative", None)
            if deriv is not None:
                new_val = Scalar(p.value.data - self.lr * deriv)
                p.update(new_val)
                continue  # skip grad if derivative exists

            grad = getattr(p.value, "grad", None)
            if grad is not None:
                p.update(p.value - self.lr * grad)
