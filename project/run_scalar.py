import ember


class Network(ember.nn.Module):
    def __init__(self, hidden_layers):
        super().__init__()
        input_size = 2
        self.layer1 = ember.nn.Linear(input_size, hidden_layers)
        self.layer2 = ember.nn.Linear(hidden_layers, hidden_layers)
        self.layer3 = ember.nn.Linear(hidden_layers, 1)  # final output

    def forward(self, x):
        middle = [h.relu() for h in self.layer1.forward(x)]
        end = [h.relu() for h in self.layer2.forward(middle)]
        return self.layer3.forward(end)[0].sigmoid()


def default_log_fn(epoch, total_loss, correct, losses):
    print("Epoch ", epoch, " loss ", total_loss, "correct", correct)


class ScalarTrain:
    def __init__(self, hidden_layers):
        self.hidden_layers = hidden_layers
        self.model = Network(self.hidden_layers)

    def run_one(self, x):
        # Wrap inputs in ember.Scalar and forward through the network
        return self.model.forward(
            (ember.Scalar(x[0], name="x_1"), ember.Scalar(x[1], name="x_2"))
        )

    def train(self, data, learning_rate, max_epochs=500, log_fn=default_log_fn):
        self.learning_rate = learning_rate
        self.max_epochs = max_epochs
        self.model = Network(self.hidden_layers)
        optim = ember.optim.SGD(self.model.parameters(), learning_rate)

        losses = []
        for epoch in range(1, self.max_epochs + 1):
            total_loss = 0.0
            correct = 0
            optim.zero_grad()

            for i in range(data.N):
                x_1, x_2 = data.X[i]
                y = data.y[i]
                x_1 = ember.Scalar(x_1)
                x_2 = ember.Scalar(x_2)
                out = self.model.forward((x_1, x_2))

                if y == 1:
                    prob = out
                    correct += 1 if out.data > 0.5 else 0
                else:
                    prob = -out + 1.0
                    correct += 1 if out.data < 0.5 else 0
                loss = -prob.log()
                (loss / data.N).backward()
                total_loss += loss.data

            losses.append(total_loss)
            optim.step()

            if epoch % 10 == 0 or epoch == max_epochs:
                log_fn(epoch, total_loss, correct, losses)

        return losses

    def predict(self, X):
        """
        Predict output probabilities for a list of inputs.

        Args:
            X: List of tuples [(x1, x2), ...]

        Returns:
            List of floats (predicted probabilities)
        """
        preds = []
        for x in X:
            out = self.run_one(x)
            preds.append(out.data)
        return preds


if __name__ == "__main__":
    PTS = 50
    HIDDEN = 10
    RATE = 0.5

    # Load XOR dataset
    data = ember.datasets["Xor"](PTS)
    trainer = ScalarTrain(HIDDEN)
    trainer.train(data, RATE)

    # Testing / Predictions
    test_points = [(0, 0), (0, 1), (1, 0), (1, 1)]
    test_labels = [0, 1, 1, 0]  # XOR ground truth

    predictions = trainer.predict(test_points)

    print("\nPredictions vs Actual:")
    for pt, pred, label in zip(test_points, predictions, test_labels):
        pred_label = round(pred)
        correct = "✅" if pred_label == label else "❌"
        print(
            f"Input: {pt}, Predicted probability: {pred:.4f}, "
            f"Predicted: {pred_label}, Actual: {label} {correct}"
        )
