import sys

import tensorflow as tf
import tf_keras as keras


def main(data_directory: str):
    print("TensorFlow version: ", tf.__version__)

    image_scale = 224
    epochs = 10

    data_set = keras.preprocessing.image_dataset_from_directory(
        data_directory,
        labels="inferred",
        label_mode="binary",
        color_mode="grayscale",
        image_size=(image_scale, image_scale),
        batch_size=32,
    )

    training_data, test_data = keras.utils.split_dataset(data_set, left_size=0.8, shuffle=True)

    model = keras.models.Sequential([
        keras.Input(shape=(image_scale, image_scale, 1)),
        keras.layers.Rescaling(1. / 255),

        keras.layers.Conv2D(16, 5, activation='relu'),
        keras.layers.MaxPooling2D(),
        keras.layers.Conv2D(32, 3, activation='relu'),
        keras.layers.MaxPooling2D(),

        keras.layers.Flatten(),
        # keras.layers.Dropout(0.3), # when it overfits
        keras.layers.Dense(64, activation='relu'),
        keras.layers.Dense(1, activation='sigmoid'),
    ])

    model.compile(
        optimizer='adam',
        loss=keras.losses.BinaryCrossentropy(),
        metrics=['accuracy'],
    )

    history = model.fit(training_data, epochs=epochs, validation_data=test_data)
    print(history.history)

    model.save("polygon_image_classifier")


if __name__ == '__main__':
    main(sys.argv[1])
