import sys

import onnxruntime as onnx
import numpy as np

def main(model_file: str):
    # Load the ONNX model
    session = onnx.InferenceSession(model_file)
    # sess = onnx.InferenceSession("rf_iris.onnx", providers=["CPUExecutionProvider"])

    # Get input and output names
    input_name = session.get_inputs()[0].name
    output_name = session.get_outputs()[0].name

    # Example new data (ensure the shape matches what the model expects)
    X_new = np.array([[5.1, 3.5, 1.4, 0.2]], dtype=np.float32)  # Modify based on your feature size

    # Run inference
    pred = session.run([output_name], {input_name: X_new})

    # Extract predicted class
    predicted_class = np.argmax(pred[0], axis=1)  # If it's a probability output
    print(predicted_class)

    # Compute the prediction with onnxruntime.
    pred_onx = sess.run([label_name], {input_name: X_test.astype(np.float32)})[0]


if __name__ == '__main__':
    main(sys.argv[1])