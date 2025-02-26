
# Light Detection and Classification Using TensorFlow and Arduino Nano 33 BLE Sense

This project demonstrates how to implement **light detection and classification** using an **Arduino Nano 33 BLE Sense** and **TensorFlow Lite**. The system captures light data from the onboard light sensor, processes it using a pre-trained TensorFlow Lite model, and classifies the type of light in real-time. This is a great example of running machine learning on microcontrollers!



## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Hardware Requirements](#hardware-requirements)
4. [Software Requirements](#software-requirements)
5. [Installation](#installation)
6. [Usage](#usage)
7. [Training the Model](#training-the-model)
8. [Deploying the Model to Arduino](#deploying-the-model-to-arduino)
9. [Project Structure](#project-structure)
10. [Troubleshooting](#troubleshooting)
11. [Contributing](#contributing)
12. [License](#license)
13. [Acknowledgments](#acknowledgments)

---

## Introduction
This project leverages the **Arduino Nano 33 BLE Sense**'s onboard light sensor and **TensorFlow Lite for Microcontrollers** to classify different types of light (e.g., natural light, artificial light, etc.). The system captures light intensity data, processes it using a TensorFlow Lite model, and outputs the classification results in real-time.

This project is ideal for:
- Learning how to deploy machine learning models on microcontrollers.
- Building light-sensitive applications.
- Exploring TinyML (Tiny Machine Learning).

---

## Features
- Real-time light detection and classification using Arduino Nano 33 BLE Sense.
- Lightweight TensorFlow Lite model for microcontrollers.
- Easy-to-use Python scripts for data collection and model training.
- Utilizes the onboard light sensor of the Arduino Nano 33 BLE Sense.
- Open-source and customizable.

---

## Hardware Requirements
To build this project, you will need the following components:
- **Arduino Nano 33 BLE Sense** (with onboard light sensor)
- USB cable for Arduino Nano 33 BLE Sense

---

## Software Requirements
- **Arduino IDE** (download from [here](https://www.arduino.cc/en/software))
- **TensorFlow Lite for Microcontrollers**
- **Python 3.x** (for data collection and model training)
- **TensorFlow** (for training the model)
- **Arduino Libraries**:
  - `TensorFlowLite`
  - `Arduino_LSM9DS1` (for onboard sensors)

---

## Installation
Follow these steps to set up the project:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/YaraGaber/Light-Detection-and-Classification-Using-TensorFlow-and-Arduino-Nano-33-BLE-Sense.git
   cd Light-Detection-and-Classification-Using-TensorFlow-and-Arduino-Nano-33-BLE-Sense
   ```

2. **Install Arduino IDE:**
   - Download and install the Arduino IDE from the [official website](https://www.arduino.cc/en/software).

3. **Install Required Arduino Libraries:**
   - Open the Arduino IDE.
   - Go to `Sketch` -> `Include Library` -> `Manage Libraries`.
   - Search for and install the following libraries:
     - `TensorFlowLite`
     - `Arduino_LSM9DS1`

4. **Install Python Dependencies:**
   If you plan to train your own model, install the required Python packages:
   ```bash
   pip install tensorflow numpy pandas
   ```

---

## Usage
### Step 1: Upload the Sketch to Arduino Nano 33 BLE Sense
- Open the `Light_Detection_Classification.ino` file in the Arduino IDE.
- Connect your Arduino Nano 33 BLE Sense to your computer.
- Select the correct board and port from the `Tools` menu.
- Click the `Upload` button to upload the sketch to the Arduino Nano 33 BLE Sense.

![Arduino IDE](https://github.com/YaraGaber/Light-Detection-and-Classification-Using-TensorFlow-and-Arduino-Nano-33-BLE-Sense/blob/main/assets/Arduino%20Nano%2033%20BLE%20Rev2.jpg)  
*Figure 2: Uploading the sketch to Arduino Nano 33 BLE Sense.*

### Step 2: Collect Data
- Use the provided Python script (`collect_data.py`) to collect light intensity data from the onboard sensor.
- Save the collected data in a CSV file for training.

### Step 3: Run Light Detection and Classification
- Once the sketch is uploaded, the Arduino Nano 33 BLE Sense will start capturing light data.
- The TensorFlow Lite model will classify the light type in real-time and output the results to the Serial Monitor.

---

## Training the Model
1. **Prepare the Dataset:**
   - Use the collected data to train a TensorFlow model.
   - The dataset should include light intensity data for each type of light you want to classify.

2. **Train the Model:**
   - Use the provided Python script (`train_model.py`) to train the model.
   - The script will save the trained model in TensorFlow Lite format.

3. **Convert the Model:**
   - Convert the trained model to a TensorFlow Lite model using the TensorFlow Lite Converter.
   - Save the model as a `.tflite` file.

---

## Deploying the Model to Arduino
1. **Include the Model in the Sketch:**
   - Convert the `.tflite` model to a C array using the `xxd` command or a similar tool.
   - Include the model array in the Arduino sketch.

2. **Upload the Sketch:**
   - Upload the updated sketch to the Arduino Nano 33 BLE Sense.
   - The Arduino will now use the new model for light detection and classification.

---

## Project Structure
```
Light-Detection-and-Classification-Using-TensorFlow-and-Arduino-Nano-33-BLE-Sense/
├── Arduino/                  # Arduino sketch and model files
│   ├── Light_Detection_Classification.ino
│   └── model.h
├── Python/                   # Python scripts for data collection and training
│   ├── collect_data.py
│   ├── train_model.py
│   └── requirements.txt
├── images/                   # Images for the README
│   ├── demo.gif
│   ├── arduino_ide.png
├── README.md                 # Project documentation
└── LICENSE                   # License file
```

---

## Troubleshooting
- **Serial Monitor Not Showing Output:**
  - Ensure the Arduino Nano 33 BLE Sense is connected correctly.
  - Check the baud rate in the Serial Monitor (set to 9600).

- **Light Sensor Not Detected:**
  - Verify the sketch is correctly configured to use the onboard light sensor.

- **Model Not Working:**
  - Double-check the model conversion process.
  - Ensure the model is correctly included in the Arduino sketch.

---

## Contributing
Contributions are welcome! If you have any suggestions, improvements, or bug fixes, feel free to:
1. Fork the repository.
2. Create a new branch.
3. Submit a Pull Request.

Please ensure your code follows the project's coding standards.

---



