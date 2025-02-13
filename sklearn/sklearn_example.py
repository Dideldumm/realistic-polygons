import numpy as np
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# Step 1: Generate a sample dataset
features, classes = make_classification(n_samples=1000, n_features=20, n_informative=15,
                                        n_redundant=5, n_classes=2, random_state=42)

# Step 2: Split into training and testing sets
training_features, test_features, training_classes, test_classes = train_test_split(features, classes, test_size=0.2,
                                                                                    random_state=42)

# Step 3: Initialize and train a logistic regression model
model = LogisticRegression(max_iter=1000)
model.fit(training_features, training_classes)

# Step 4: Make predictions and evaluate the model using the test data
test_prediction = model.predict(test_features)

# Evaluate performance
accuracy = accuracy_score(test_classes, test_prediction)
conf_matrix = confusion_matrix(test_classes, test_prediction)
class_report = classification_report(test_classes, test_prediction)

# Print evaluation metrics
print(f"Accuracy: {accuracy:.2f}")
print("Confusion Matrix:")
print(conf_matrix)
print("Classification Report:")
print(class_report)

# Optional: Predict on new data
new_data = np.random.rand(5, 20)  # 5 samples, 20 features
y_new = model.predict(new_data)
print("Predictions for new samples:", y_new)
