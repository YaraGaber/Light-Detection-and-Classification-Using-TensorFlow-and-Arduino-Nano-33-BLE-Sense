#include "model.h"  // Include the generated model header file
#include <Arduino_APDS9960.h>  // APDS-9960 library
#include <Chirale_TensorFlowLite.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

// TensorFlow Lite Globals
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

constexpr int kTensorArenaSize = 4000;  // Adjust size according to model requirements
alignas(16) uint8_t tensor_arena[kTensorArenaSize];

// APDS-9960 variables
int r, g, b;
int lightLevel = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial Monitor to be ready
  Serial.println("Initializing TensorFlow Lite Model...");

  // Initialize APDS-9960 sensor
  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS-9960 sensor!");
    while (1);  // Halt if sensor initialization fails
  }

  // Load TensorFlow Lite Model
  model = tflite::GetModel(g_model);  // g_model is the array containing the model data
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);  // Halt if schema version mismatch
  }

  // Initialize TensorFlow Lite Interpreter
  static tflite::AllOpsResolver resolver;
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  // Allocate tensors for the model
  if (interpreter->AllocateTensors() != kTfLiteOk) {
    Serial.println("Failed to allocate tensors!");
    while (1);  // Halt if tensor allocation fails
  }

  // Get input and output tensors
  input = interpreter->input(0);
  output = interpreter->output(0);

  Serial.println("Model loaded successfully!");
}

void loop() {
  // Read light data from APDS-9960
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);
    lightLevel = r + g + b;  // Sum of RGB as light intensity (simple approach)

    // Debug: Print raw RGB values to check sensor readings
    Serial.print("Raw RGB: ");
    Serial.print(r);
    Serial.print(", ");
    Serial.print(g);
    Serial.print(", ");
    Serial.println(b);
  }

  // Normalize light value (0-1 range)
  float normalizedLight = (float)lightLevel / 765.0;  // 765 = Max RGB (255*3)
  Serial.print("Normalized Light: ");
  Serial.println(normalizedLight);  // Debug: Check the normalized light value

  // Set input tensor data
  input->data.f[0] = normalizedLight;

  // Run inference
  if (interpreter->Invoke() != kTfLiteOk) {
    Serial.println("Inference failed!");
    return;
  }

  // Get the predicted class (output from the model)
  int predictedClass = 0;
  uint8_t maxOutputValue = output->data.uint8[0];

  // Find the class with the highest value in the output tensor
  for (int i = 1; i < output->bytes; i++) {
    if (output->data.uint8[i] > maxOutputValue) {
      maxOutputValue = output->data.uint8[i];
      predictedClass = i;  // Set the class index with the highest value
    }
  }

  // Debug: Print the output tensor
  Serial.print("Output Raw: ");
  for (int i = 0; i < output->bytes; i++) {
    Serial.print(output->data.uint8[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Map the predicted class to a string label
  String lightLevelLabel;
  switch (predictedClass) {
    case 0:
      lightLevelLabel = "Dark";
      break;
    case 1:
      lightLevelLabel = "Dim";
      break;
    case 2:
      lightLevelLabel = "Bright";
      break;
    default:
      lightLevelLabel = "Unknown Light Level";
      break;
  }

  // Print the result
  Serial.print("Predicted Light Level: ");
  Serial.println(lightLevelLabel);

  delay(500);  // Delay for readability and to avoid spamming the Serial Monitor
}
