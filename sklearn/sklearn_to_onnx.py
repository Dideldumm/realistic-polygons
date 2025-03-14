# Train a model.
import sys

from skl2onnx import to_onnx

import train_on_polygons


def main(realistic_data: str, unrealistic_data: str, output_name: str):
    shuffled_features, shuffled_labels, unrealistic_features, unrealistic_labels = train_on_polygons.prepare_training_data(
        realistic_data,
        unrealistic_data)
    model = train_on_polygons.train_and_test_new_model(shuffled_features, shuffled_labels)
    onnx = to_onnx(model, shuffled_features[:1])
    with open(output_name, "wb") as file:
        file.write(onnx.SerializeToString())


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
