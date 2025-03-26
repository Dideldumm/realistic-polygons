import sys

import onnxruntime as onnx
import onnx as onx
import numpy as np


def main(model_file: str, data_file: str):
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
    pred = session.run([output_name], {input_name: features})
    for data in pred:
        for i in range(len(data)):
            data_point = data[i]
            probability = data_point[1]
            print(f"Index: {i}, Probability: {probability}")
        print()


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
