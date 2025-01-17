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
3. [Step-by-Step Configuration](#step-by-step-configuration)
4. [Basic Usage](#basic-usage)
5. [FAQ](#faq)
6. [Provided Examples](#provided-examples)
7. [Inference Engine Details](#inference-engine-details)
8. [Educational Focus](#educational-focus)
9. [License](#license)
10. [Contact](#contact)

---

## Features

- Supports **3, 4, or 5 fuzzy sets** for input and output.
- Easy configuration of fuzzy rules and membership functions.
- Implements the **centroid method** for defuzzification.
- Compatible with Arduino IDE.
- Provides examples for quick setup:
  - Using 3, 4, or 5 fuzzy sets.
  - Examples available in **English** and **Spanish**.

---

## Installation

1. Download the repository or clone it using:
   ```bash
   git clone https://github.com/Giosephe/FuzzyMamdani.git
   ```
2. Copy the `FuzzyMamdani` folder into your Arduino `libraries` folder:
   - On Windows: `Documents/Arduino/libraries/`
   - On macOS/Linux: `~/Arduino/libraries/`
3. Restart the Arduino IDE and verify the installation under **File > Examples > FuzzyMamdani**.

---

## Step-by-Step Configuration

### 3.1 Number of Fuzzy Sets
```cpp
fuzzy.setNumSets(4);
```
Indicates how many sets (3 to 5) you will use for input (Error) and output (Control).

### 3.2 Input Sets (Error)
Define each fuzzy set with its points:
```cpp
FuzzySet eLow = {{0, 5, 10}, 'T'}; // Example: triangular
fuzzy.setInputSet(0, eLow);
```
Repeat for other sets (1, 2, etc.).

### 3.3 Output Sets (Control)
Similar to input:
```cpp
FuzzySet cLow = {{0, 10, 20}, 'T'};
fuzzy.setOutputSet(0, cLow);
```

### 3.4 Fuzzy Rules
A rule links an input set index to an output set index:
```cpp
fuzzy.setRule(0, 0, 0);
fuzzy.setRule(1, 1, 1);
fuzzy.setRule(2, 2, 2);
```

### 3.5 Additional Parameters
- Discretization: `fuzzy.setIterations(20);`
- SetPoint: `fuzzy.setSetPoint(80);`
- Turn off negative error: `fuzzy.setNegativeErrorOff(true);`

---

## Basic Usage

Use this in the loop to calculate the control output:
```cpp
float output = fuzzy.computeOutput(currentInput);
```
Internally, it calculates:
```cpp
error = setPoint - currentInput;
```
Applies fuzzy rules and returns the output (centroid).

### Example: Temperature Control
```cpp
FuzzyMamdani fuzzy;

void setup() {
  Serial.begin(9600);
  fuzzy.setNumSets(3);

  FuzzySet eCold = {{0, 10, 20}, 'T'};
  FuzzySet eComfortable = {{15, 25, 35}, 'T'};
  FuzzySet eHot = {{30, 40, 50}, 'T'};
  fuzzy.setInputSet(0, eCold);
  fuzzy.setInputSet(1, eComfortable);
  fuzzy.setInputSet(2, eHot);

  FuzzySet cLow = {{0, 10, 20}, 'T'};
  FuzzySet cMedium = {{15, 25, 35}, 'T'};
  FuzzySet cHigh = {{30, 40, 50}, 'T'};
  fuzzy.setOutputSet(0, cLow);
  fuzzy.setOutputSet(1, cMedium);
  fuzzy.setOutputSet(2, cHigh);

  fuzzy.setRule(0, 0, 0);
  fuzzy.setRule(1, 1, 1);
  fuzzy.setRule(2, 2, 2);
  fuzzy.setSetPoint(25);
}

void loop() {
  float temperature = analogRead(A0) * (50.0 / 1023.0);
  float output = fuzzy.computeOutput(temperature);
  Serial.println(output);
}
```
---
## FAQ

**Q: What is the maximum number of fuzzy sets supported?**  
A: The library supports up to 5 fuzzy sets for both input and output.

**Q: Can I use this library with ESP32 or STM32 boards?**  
A: Yes, the library is compatible with any board supported by the Arduino IDE.

**Q: How can I test the library without hardware?**  
A: Use the Serial Monitor in the Arduino IDE to input values and observe the output.

**Q: Can I customize the membership functions?**  
A: Yes, you can define custom triangular or trapezoidal membership functions.

**Q: How do I change the SetPoint dynamically?**  
A: Use the Serial Monitor and type `setpoint X` (e.g., `setpoint 75`) to set a new SetPoint during runtime.

---

## Provided Examples

The FuzzyMamdani library includes several example sketches in **English** and **Spanish**:

**English Examples**:
- `English/FuzzyMamdani_3Sets/FuzzyMamdani_3Sets.ino`
- `English/FuzzyMamdani_4Sets/FuzzyMamdani_4Sets.ino`
- `English/FuzzyMamdani_5Sets/FuzzyMamdani_5Sets.ino`
- `English/FuzzyMamdani_QuickStart/FuzzyMamdani_QuickStart.ino`

**Spanish Examples**:
- `Spanish/FuzzyMamdani_3Sets/FuzzyMamdani_3Conjuntos.ino`
- `Spanish/FuzzyMamdani_4Sets/FuzzyMamdani_4Conjuntos.ino`
- `Spanish/FuzzyMamdani_5Sets/FuzzyMamdani_5Conjuntos.ino`
- `Spanish/FuzzyMamdani_QuickStart/FuzzyMamdani_InicioRapido.ino`

Each example demonstrates specific use cases:
- **FuzzyMamdani_3Sets**: Suitable for simple systems with three fuzzy sets.
- **FuzzyMamdani_4Sets**: Balances simplicity and precision with four sets.
- **FuzzyMamdani_5Sets**: Ideal for detailed control with five sets.
- **FuzzyMamdani_QuickStart**: A basic interactive demo via Serial Monitor.

---

## Inference Engine Details

The library calculates the crisp output using the **centroid method**, which involves:
1. Calculating the membership values for input fuzzy sets.
2. Applying the fuzzy rules to map input sets to output sets.
3. Computing the output centroid based on the weighted average of membership functions.

**Example Calculation:**
- **Input:** 40  
- **SetPoint:** 50  
- **Error:** 10  
- **Fuzzy Rule Applied:** `eMedium -> cMedium`  
- **Membership Calculation:**  
  - Membership of input in `eMedium`: 0.5  
  - Membership of output in `cMedium`: 0.5  
- **Centroid Output:**  
  ```
  Output = (Σ Weighted Outputs) / (Σ Membership Values)
         = (27.5 * 0.5) / (0.5)
         = 27.5
  ```

---

## Educational Focus

The FuzzyMamdani library is designed to:
- Teach fuzzy logic principles through simple APIs.
- Allow experimentation with various configurations.
- Visualize fuzzy behavior via the Serial Monitor for educational purposes.

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