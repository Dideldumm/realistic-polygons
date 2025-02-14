import sys
from typing import Tuple
from typing import List

import numpy as np
import pandas as pd

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

random_state = 42


def load_metadata(filename: str) -> Tuple[int, int]:
    try:
        with open(filename, "r") as file:
            max_features, number_of_polygons = map(int, file.readlines())
            return max_features, number_of_polygons
    except FileNotFoundError:
        raise FileNotFoundError(f"File {filename} not found.")
    except ValueError as e:
        raise ValueError(f"Failed to parse numbers: {e}.")


def build_header(number_of_features: int) -> List[str]:
    return [f"x{i / 2}" if i % 2 == 0 else f"y{i / 2}" for i in range(number_of_features)]


def main(realistic_data: str, unrealistic_data: str) -> None:
    max_features, number_of_polygons = load_metadata(realistic_data + ".metadata")
    header = build_header(number_of_polygons)

    realistic_features = pd.read_csv(realistic_data, header=None, names=header).values
    realistic_labels = np.ones(number_of_polygons)

    unrealistic_features = pd.read_csv(unrealistic_data, header=None, names=header).values
    unrealistic_labels = np.zeros(number_of_polygons)

    features = np.vstack([realistic_features, unrealistic_features])
    labels = np.vstack([realistic_labels, unrealistic_labels])

    random_indices = np.random.permutation(number_of_polygons)
    features = features[random_indices]
    labels = labels[random_indices]

    train_features, test_features, train_labels, test_labels = train_test_split(features, labels,
                                                                                test_size=0.2,
                                                                                random_state=random_state)

    model = LogisticRegression(solver="saga", max_iter=1000)
    model.fit(train_features, train_labels)

    prediction = model.predict(test_features)

    accuracy = accuracy_score(test_labels, prediction)

    print(f"Accuracy: {accuracy}")


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
