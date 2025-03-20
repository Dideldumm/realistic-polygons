# Train a model.
import sys

import numpy as np
import skl2onnx
from onnxconverter_common import FloatTensorType

import train_on_polygons


def main(realistic_data: str, unrealistic_data: str, output_name: str):
    realistic_features = np.loadtxt(realistic_data, delimiter=",")
    unrealistic_features = np.loadtxt(unrealistic_data, delimiter=",")
    shuffled_features, shuffled_labels = train_on_polygons.prepare_training_data(realistic_features,
                                                                                 unrealistic_features)
    model = train_on_polygons.train_and_test_new_model(shuffled_features, shuffled_labels, False)
    initial_type = [('input', FloatTensorType([None, shuffled_features.shape[1]]))]
    onnx = skl2onnx.convert_sklearn(model, initial_types=initial_type)
    # onnx = to_onnx(model, shuffled_features[:1])
    with open(output_name, "wb") as file:
        file.write(onnx.SerializeToString())


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
