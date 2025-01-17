# FuzzyMamdani Library - A Beginner-Friendly Fuzzy Logic Controller for Arduino

**Version:** 1.0  
**Author:** Kennet Morillo  
**License:** Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International  

The FuzzyMamdani library simplifies the implementation of fuzzy logic control systems based on the **Mamdani model**. Whether you're a beginner or a student, this library provides a clear path to understanding and applying fuzzy control systems.  

**Applications include:** Temperature regulation, motor speed control, and irrigation systems.

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
- Provides examples in **English** and **Spanish**.

---

## Installation

1. Download the repository or clone it using:
   ```bash
   git clone https://github.com/KennetMorillo/FuzzyMamdani.git
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

## Inference Engine Details

**Example:**
Input = 40, SetPoint = 50, Error = 10. Rules applied: `eMedium -> cMedium`. Output centroid calculated: 27.5.