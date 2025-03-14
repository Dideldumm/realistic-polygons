import sys

import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report

random_state = 42


def main(realistic_data: str, unrealistic_data: str, generated_data: str) -> None:
    # realistic_features = pd.read_csv(realistic_data, header=None, names=header).values
    shuffled_features, shuffled_labels = prepare_training_data(realistic_data, unrealistic_data)
    model = train_and_test_new_model(shuffled_features, shuffled_labels)

    generated_with_unrealistic, target = prepare_training_data(generated_data, unrealistic_data)

    prediction = model.predict(generated_with_unrealistic)
    print("performance of generated data:\n")
    print(classification_report(target, prediction))


def prepare_training_data(realistic_data, unrealistic_data):
    realistic_features = np.loadtxt(realistic_data, delimiter=",")
    realistic_labels = np.ones(realistic_features.shape[0])
    unrealistic_features = np.loadtxt(unrealistic_data, delimiter=",")
    unrealistic_labels = np.zeros(unrealistic_features.shape[0])
    features = np.vstack([realistic_features, unrealistic_features])
    labels = np.hstack([realistic_labels, unrealistic_labels])
    shuffled_features, shuffled_labels = shuffle(features, labels, realistic_features.shape[0],
                                                 unrealistic_features)
    return shuffled_features, shuffled_labels


def shuffle(features, labels, number_of_realistic_polygons, unrealistic_features):
    random_indices = np.random.permutation(number_of_realistic_polygons + unrealistic_features.shape[0])
    shuffled_features = features[random_indices]
    shuffled_labels = labels[random_indices]
    return shuffled_features, shuffled_labels


def prepare_generated_data(generated_data, unrealistic_features, unrealistic_labels):
    generated_features = np.loadtxt(generated_data, delimiter=",")
    generated_target = np.ones(generated_features.shape[0])
    generated_with_unrealistic = np.vstack([generated_features, unrealistic_features])
    target = np.hstack([generated_target, unrealistic_labels])
    return generated_with_unrealistic, target


def train_and_test_new_model(shuffled_features, shuffled_labels):
    train_features, test_features, train_labels, test_labels = train_test_split(shuffled_features, shuffled_labels,
                                                                                test_size=0.2,
                                                                                random_state=random_state)
    model = train_new_model(train_features, train_labels)
    test_prediction = model.predict(test_features)
    print("test prediction:\n")
    print(classification_report(test_labels, test_prediction))
    return model


def train_new_model(train_features, train_labels):
    model = LogisticRegression(solver="saga", max_iter=10000)
    model.fit(train_features, train_labels)
    return model


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
