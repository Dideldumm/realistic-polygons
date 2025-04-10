import tensorflow as tf
import tf_keras as keras


def main():
    print("TensorFlow version: ", tf.__version__)

    # load example dataset
    mnist = keras.datasets.mnist
    (x_train, y_train), (x_test, y_test) = mnist.load_data()
    x_train, x_test = x_train / 255.0, x_test / 255.0

    # build a machine learning model
    model = keras.models.Sequential([
        keras.layers.Input(shape=(28, 28)),
        keras.layers.Flatten(),
        keras.layers.Dense(128, activation='relu'),
        keras.layers.Dropout(0.2),
        keras.layers.Dense(10)
    ])

    predictions = model(x_train[:1]).numpy()
    print(predictions)

    # apply softmax to get normalized probabilities
    print(tf.nn.softmax(predictions).numpy())

    # loss function
    loss_fn = keras.losses.SparseCategoricalCrossentropy(from_logits=True)
    print(loss_fn(y_train[:1], predictions).numpy())

    # configure settings for the model (set optimizer, loss function and metrics)
    model.compile(optimizer='adam',
                  loss=loss_fn,
                  metrics=['accuracy'])

    # train the model
    model.fit(x_train, y_train, epochs=5)

    # evaluate performance using the test set
    print(model.evaluate(x_test, y_test, verbose=2))




if __name__ == '__main__':
    main()
