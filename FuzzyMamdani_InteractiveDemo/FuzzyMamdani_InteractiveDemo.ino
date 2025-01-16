/*
  FuzzyMamdani_QuickStart.ino - Example for the FuzzyMamdani Library
  Author: Kennet Morillo
  Created on: 15/01/2025
  License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
*/

#include <FuzzyMamdani.h>

// Global instance of the FuzzyMamdani library
FuzzyMamdani fuzzy;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  Serial.println("FuzzyMamdani Library Quick Start Example");

  // Request SetPoint from the user
  float setPoint = requestSetPoint();
  fuzzy.setSetPoint(setPoint);

  // Set the number of fuzzy sets (input and output)
  fuzzy.setNumSets(4); // Using 4 sets in this example

  // Define input (error) fuzzy sets
  FuzzySet eVeryLow = {{0, 1, 3}, 'T'};       // Very small error (Triangular)
  FuzzySet eLow     = {{2, 5, 15}, 'T'};      // Small error (Triangular)
  FuzzySet eMedium  = {{8, 20, 25, 50}, 'O'}; // Moderate error (Trapezoidal)
  FuzzySet eHigh    = {{40, 60, 100, 100}, 'O'}; // Large error (Trapezoidal)

  fuzzy.setInputSet(0, eVeryLow);
  fuzzy.setInputSet(1, eLow);
  fuzzy.setInputSet(2, eMedium);
  fuzzy.setInputSet(3, eHigh);

  // Define output (control) fuzzy sets
  FuzzySet cVeryLow = {{0, 2, 6}, 'T'};       // Minimal control action (Triangular)
  FuzzySet cLow     = {{4, 6, 10, 20}, 'O'};  // Slight control adjustment (Trapezoidal)
  FuzzySet cMedium  = {{18, 30, 55}, 'T'};    // Moderate control adjustment (Triangular)
  FuzzySet cHigh    = {{45, 70, 100, 100}, 'O'}; // Strong control with trapezoidal range

  fuzzy.setOutputSet(0, cVeryLow);
  fuzzy.setOutputSet(1, cLow);
  fuzzy.setOutputSet(2, cMedium);
  fuzzy.setOutputSet(3, cHigh);

  // Configure fuzzy inference rules
  fuzzy.setRule(0, 0, 0); // If Error is VeryLow, Control is VeryLow
  fuzzy.setRule(1, 1, 1); // If Error is Low, Control is Low
  fuzzy.setRule(2, 2, 2); // If Error is Medium, Control is Medium
  fuzzy.setRule(3, 3, 3); // If Error is High, Control is High

  // Additional configuration parameters
  fuzzy.setIterations(20);       // Number of iterations for centroid calculation
  fuzzy.setNegativeErrorOff(true); // Ignore negative errors

  Serial.println("Configuration completed.");
  Serial.println("Instructions:");
  Serial.println("1. Enter a numerical input via Serial Monitor.");
  Serial.println("2. The program will calculate and display the control output.");
  Serial.println("3. To test predefined inputs, type 'test'.");
  Serial.println("4. To change the SetPoint, type 'setpoint X' (e.g., 'setpoint 90').");
}

void loop() {
  if (Serial.available()) {
    String userInput = Serial.readStringUntil('\n'); // Read input as a string
    userInput.trim(); // Remove any leading/trailing whitespace

    // Handle predefined test inputs
    if (userInput.equalsIgnoreCase("test")) {
      runPredefinedTests();
    }
    // Handle dynamic SetPoint configuration
    else if (userInput.startsWith("setpoint ")) {
      float newSetPoint = userInput.substring(9).toFloat();
      fuzzy.setSetPoint(newSetPoint);
      Serial.print("New SetPoint configured: ");
      Serial.println(newSetPoint);
    }
    // Handle regular input for fuzzy output calculation
    else {
      handleFuzzyInput(userInput);
    }
  }
}

// Function to request SetPoint from the user
float requestSetPoint() {
  Serial.println("Please enter the initial SetPoint:");
  while (!Serial.available()) {
    delay(100); // Wait for user input
  }
  String input = Serial.readStringUntil('\n');
  input.trim();
  float setPoint = input.toFloat();
  Serial.print("Initial SetPoint set to: ");
  Serial.println(setPoint);
  return setPoint;
}

// Function to handle predefined tests dynamically
void runPredefinedTests() {
  float setPoint = fuzzy.getSetPoint(); // Get the current SetPoint
  float errors[] = {60, 45, 25, 10, 5, 1}; // Defined errors
  Serial.println("Running predefined tests...");

  for (int i = 0; i < sizeof(errors) / sizeof(errors[0]); i++) {
    float testInput = setPoint - errors[i]; // Calculate test input
    float output = fuzzy.computeOutput(testInput);
    displayResults(testInput, output, setPoint - testInput); // Include error in results
  }
}

// Function to handle regular input and validate
void handleFuzzyInput(String userInput) {
  if (!userInput.toFloat() && userInput != "0") {
    Serial.println("Error: Invalid input. Please enter a numeric value.");
  } else {
    float input = userInput.toFloat();
    float setPoint = fuzzy.getSetPoint(); // Get current SetPoint
    if (input >= 0 && input <= 100) {
      float output = fuzzy.computeOutput(input);
      if (isnan(output)) {
        Serial.println("Error: Unable to compute output. Check fuzzy set configuration.");
      } else {
        displayResults(input, output, setPoint - input); // Include error in results
      }
    } else {
      Serial.println("Error: Input out of range. Please enter a value between 0 and 100.");
    }
  }
}

// Function to display results in a formatted way
void displayResults(float input, float output, float error) {
  Serial.println("========== RESULT ==========");
  Serial.print("Input Value: ");
  Serial.println(input);
  Serial.print("Error: ");
  Serial.println(error);
  Serial.print("Control Output: ");
  Serial.println(output);
  Serial.println("=============================");
}