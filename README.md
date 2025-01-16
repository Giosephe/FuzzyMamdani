<<<<<<< HEAD
# FuzzyMamdani Library

**Version:** 1.0  
**Author:** Kennet Morillo  
**License:** Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International  

The FuzzyMamdani library simplifies the implementation of a fuzzy logic control system (based on the Mamdani model) for Arduino. 
It is specifically designed for beginners and students, offering intuitive methods and detailed examples. Whether you're exploring fuzzy logic for the first time or building small projects, this library provides a solid foundation for understanding and applying fuzzy control systems.

---

## Table of Contents
1. [Features](#features)
2. [Installation](#installation)
3. [Basic Usage](#basic-usage)
4. [Advanced Usage](#advanced-usage)
5. [Provided Examples](#provided-examples)
6. [Inference Engine Details](#inference-engine-details)
7. [Educational Focus](#educational-focus)
8. [License](#license)
9. [Contact](#contact)

---

## Features

- Supports **3, 4, or 5 fuzzy sets** for input and output.
- Easy configuration of fuzzy rules and membership functions.
- Implements the **centroid method** for defuzzification.
- Compatible with Arduino IDE.
- Provides examples for quick setup:
  - Using 3, 4, or 5 fuzzy sets.

---

## Installation

1. Download the repository or clone it using:
   ```bash
   git clone https://github.com/KennetMorillo/FuzzyMamdani.git
   ```
2. Copy the `FuzzyMamdani` folder into your Arduino `libraries` folder:
   - On Windows: `Documents/Arduino/libraries/`
   - On macOS/Linux: `~/Arduino/libraries/`
3. Open the Arduino IDE and include the library in your project:
   ```cpp
   #include <FuzzyMamdani.h>
   ```

---

## Basic Usage

Here's a quick example of how to use the library:

```cpp
#include <FuzzyMamdani.h>

FuzzyMamdani fuzzy;

void setup() {
  Serial.begin(9600);

  // Configure the number of fuzzy sets
  fuzzy.setNumSets(3);

  // Define fuzzy sets for error input
  FuzzySet eLow = {{0, 10, 20}, 'T'};
  FuzzySet eMedium = {{15, 30, 45}, 'T'};
  FuzzySet eHigh = {{40, 70, 100}, 'T'};

  fuzzy.setInputSet(0, eLow);
  fuzzy.setInputSet(1, eMedium);
  fuzzy.setInputSet(2, eHigh);

  // Define fuzzy sets for control output
  FuzzySet cLow = {{0, 10, 20}, 'T'};
  FuzzySet cMedium = {{15, 40, 60}, 'T'};
  FuzzySet cHigh = {{50, 75, 100}, 'T'};

  fuzzy.setOutputSet(0, cLow);
  fuzzy.setOutputSet(1, cMedium);
  fuzzy.setOutputSet(2, cHigh);

  // Define fuzzy rules
  fuzzy.setRule(0, 0, 0);
  fuzzy.setRule(1, 1, 1);
  fuzzy.setRule(2, 2, 2);

  // Set additional parameters
  fuzzy.setSetPoint(50);
  fuzzy.setIterations(20);
}

void loop() {
  float input = 30.0; // Example input
  float output = fuzzy.computeOutput(input);

  Serial.print("Input: ");
  Serial.println(input);
  Serial.print("Output: ");
  Serial.println(output);
}
```

---

## Advanced Usage

This section demonstrates advanced features, such as allowing negative errors and retrieving the current SetPoint:

```cpp
void setup() {
  fuzzy.setNegativeErrorOff(false); // Enable negative errors
  fuzzy.setSetPoint(75.0); // Adjust the SetPoint

  float currentSetPoint = fuzzy.getSetPoint();
  Serial.print("Current SetPoint: ");
  Serial.println(currentSetPoint);
}
```

---

## Provided Examples

The FuzzyMamdani library includes several example sketches to help you get started with different configurations:

1. **FuzzyMamdani_3Sets**:
   - Demonstrates how to use the library with **3 fuzzy sets** for input and output.
   - Includes basic configurations and rules tailored for smaller control systems.

2. **FuzzyMamdani_4Sets**:
   - Shows how to configure the library with **4 fuzzy sets** for more precise control scenarios.
   - Provides a balance between simplicity and accuracy.

3. **FuzzyMamdani_5Sets**:
   - Explains the setup for **5 fuzzy sets**, ideal for highly detailed control systems.
   - Suitable for applications requiring fine-tuned control.

4. **FuzzyMamdani_InteractiveDemo**:
   - An interactive demonstration that allows you to test the library dynamically via the Serial Monitor.
   - Users can input values in real time and observe the fuzzy logic system in action.

Each example is located in its respective folder:

- `FuzzyMamdani_3Sets/FuzzyMamdani_3Sets.ino`
- `FuzzyMamdani_4Sets/FuzzyMamdani_4Sets.ino`
- `FuzzyMamdani_5Sets/FuzzyMamdani_5Sets.ino`
- `FuzzyMamdani_InteractiveDemo/FuzzyMamdani_InteractiveDemo.ino`

To explore these examples:
1. Open the `.ino` file in the respective folder.
2. Upload it to your Arduino board using the Arduino IDE.
3. Use the Serial Monitor to observe or interact with the system's behavior.

---

## Inference Engine Details

- **Membership Calculation:**  
  The library evaluates the input values against fuzzy sets using the following rules:
  - Triangular sets: Membership value rises or falls linearly.
  - Trapezoidal sets: Membership remains constant within the flat region.

- **Rule Application:**  
  Each input fuzzy set is mapped to an output fuzzy set based on the rules defined. For example:
  ```cpp
  fuzzy.setRule(0, 0, 0); // If input is VeryLow, output is VeryLow
  ```

- **Defuzzification:**  
  The centroid method calculates the crisp output:
  ```cpp
  output = (sum of weighted outputs) / (sum of memberships);
  ```

---

## Educational Focus

The FuzzyMamdani library is designed to:

1. Teach fuzzy logic principles through simple APIs.
2. Allow experimentation with various configurations.
3. Visualize fuzzy behavior via the serial monitor.

---

## License

This library is licensed under the **Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)** license.

- Educational use is free.
- Commercial use requires prior written authorization.

For full license details, see the [LICENSE](./LICENSE) file.

---

## Contact

If you have questions, suggestions, or require a commercial license, contact:  
**Kennet Morillo** - <kennetmorillostw@hotmail.com>
=======
# FuzzyMamdani
A beginner-friendly Fuzzy Logic library for Arduino based on the Mamdani model.
>>>>>>> fdd6a1c6d7daf879c810721466357adee12db4d8
