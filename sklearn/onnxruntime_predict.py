import sys

import onnxruntime as onnx
import onnx as onx
import numpy as np
import csv


def main(model_file: str, data_file: str, output_file: str):
    model = onx.load(model_file)
    # print(onx.helper.printable_graph(model.graph), flush=True)

    # Load the ONNX model
    session = onnx.InferenceSession(model_file)
    # Load the data
    features = np.loadtxt(data_file, delimiter=",", dtype=np.float32)

    # Get input and output names
    input_name = session.get_inputs()[0].name
    output_name = session.get_outputs()[1].name
    print(f"Model expects input: {input_name}", flush=True)
    print(f"Model will output: {output_name}", flush=True)

    # Run inference
    pred = session.run([output_name], {input_name: features})[0]
    probabilities = np.array([datapoint[1] for datapoint in pred])
    result = np.column_stack((features, probabilities))
    np.savetxt(output_file, result, delimiter=",", fmt="%f")


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2], sys.argv[3])
