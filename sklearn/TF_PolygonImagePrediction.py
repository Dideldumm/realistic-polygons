import sys

import tensorflow as tf
import tf_keras as keras

scale = 224


def predict_single_image(model: keras.Model, image_file: str):
    image = keras.utils.load_img(
        image_file,
        color_mode="grayscale",
        target_size=(scale, scale),
    )
    image_array = keras.utils.img_to_array(image)
    image_array = tf.expand_dims(image_array, 0)
    image_array = image_array / 255.0

    prediction = model.predict(image_array)[0][0]
    print("Prediction: " + prediction)


def main(model_directory: str, data_directory: str):
    print("TensorFlow version: ", tf.__version__)

    model: keras.Model = keras.models.load_model(model_directory)

    # if "." in data_directory.:
    #     predict_single_image(model, data_directory)
    #     return

    dataset = keras.preprocessing.image_dataset_from_directory(
        data_directory,
        labels=None,
        color_mode="grayscale",
        image_size=(scale, scale),
        batch_size=32,
        shuffle=False,
    )

    predictions = model.predict(dataset)
    for (i, prediction) in enumerate(predictions, start=0):
        print(i, prediction)


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
