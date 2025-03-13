import sys
from typing import Tuple
from typing import List

import numpy as np
from scipy.sparse import vstack

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report

random_state = 42


def load_metadata(filename: str) -> Tuple[int, int]:
    try:
        with open(filename, "r") as file:
            max_points, number_of_polygons = map(int, file.readlines())
            return max_points, number_of_polygons
    except FileNotFoundError:
        raise FileNotFoundError(f"File {filename} not found.")
    except ValueError as e:
        raise ValueError(f"Failed to parse numbers: {e}.")


def build_header(number_of_features: int) -> List[str]:
    return [f"x{i // 2}" if i % 2 == 0 else f"y{i // 2}" for i in range(number_of_features)]


def main(realistic_data: str, unrealistic_data: str, generated_data: str) -> None:
    max_points, number_of_realistic_polygons = load_metadata(realistic_data + ".metadata")
    _, number_of_unrealistic_polygons = load_metadata(unrealistic_data + ".metadata")
    _, number_of_generated_polygons = load_metadata(generated_data + ".metadata")

    header = build_header(number_of_realistic_polygons)

    # realistic_features = pd.read_csv(realistic_data, header=None, names=header).values
    realistic_features = np.loadtxt(realistic_data, delimiter=",")
    realistic_labels = np.ones(number_of_realistic_polygons)

    unrealistic_features = np.loadtxt(unrealistic_data, delimiter=",")
    unrealistic_labels = np.zeros(number_of_unrealistic_polygons)


    features = np.vstack([realistic_features, unrealistic_features])
    labels = np.hstack([realistic_labels, unrealistic_labels])


    random_indices = np.random.permutation(number_of_realistic_polygons + number_of_unrealistic_polygons)
    shuffled_features = features[random_indices]
    shuffled_labels = labels[random_indices]

    train_features, test_features, train_labels, test_labels = train_test_split(shuffled_features, shuffled_labels,
                                                                                test_size=0.2,
                                                                                random_state=random_state)


    model = LogisticRegression(solver="saga", max_iter=10000)
    model.fit(train_features, train_labels)

    test_prediction = model.predict(test_features)

    print("test prediction:\n")
    print(classification_report(test_labels, test_prediction))
    print()

    generated_features = np.loadtxt(unrealistic_data, delimiter=",")
    generated_with_unrealistic = np.vstack([generated_features, unrealistic_features])
    generated_target = np.ones(number_of_generated_polygons)
    target = np.hstack([generated_target, unrealistic_labels])
    prediction = model.predict(generated_with_unrealistic)
    print("performance of generated data:\n")
    print(classification_report(target, prediction))


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
