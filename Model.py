import pandas as pd
import tensorflow as tf
from sklearn.model_selection import train_test_split

# Load dataset
data = pd.read_csv(r"C:\Users\yarag\OneDrive\Documents\doucments arduino\codes\adv2\light.csv")
X = data['Light_Intensity'].values.reshape(-1, 1)
y = pd.get_dummies(data['Label']).values

# Split data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

# Build model
model = tf.keras.Sequential([
    tf.keras.layers.Dense(8, activation='relu', input_shape=(1,)),
    tf.keras.layers.Dense(3, activation='softmax') # 3 classes: Bright, Dim, Dark
])

model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
model.summary()

# Train model
history = model.fit(X_train, y_train, epochs=50, validation_data=(X_test, y_test))

# Save as TFLite model
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

with open('light_model.tflite', 'wb') as f:
    f.write(tflite_model)
