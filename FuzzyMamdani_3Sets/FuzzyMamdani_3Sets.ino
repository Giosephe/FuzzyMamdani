/*
  FuzzyMamdani_3Sets.ino - Example with 3 fuzzy sets
  Author: Kennet Morillo
  Created on: 15/01/2025
  License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
*/

#include <FuzzyMamdani.h>

// Global instance of the FuzzyMamdani library
FuzzyMamdani fuzzy;

void setup() {
  Serial.begin(9600);
  Serial.println("FuzzyMamdani Example: 3 Sets");

  // Set the number of fuzzy sets
  fuzzy.setNumSets(3);

  // Define input (error) fuzzy sets
  FuzzySet eLow    = {{0, 10, 20}, 'T'};
  FuzzySet eMedium = {{15, 30, 45}, 'T'};
  FuzzySet eHigh   = {{40, 70, 100}, 'T'};

  fuzzy.setInputSet(0, eLow);
  fuzzy.setInputSet(1, eMedium);
  fuzzy.setInputSet(2, eHigh);

  // Define output (control) fuzzy sets
  FuzzySet cLow    = {{0, 10, 20}, 'T'};
  FuzzySet cMedium = {{15, 40, 60}, 'T'};
  FuzzySet cHigh   = {{50, 75, 100}, 'T'};

  fuzzy.setOutputSet(0, cLow);
  fuzzy.setOutputSet(1, cMedium);
  fuzzy.setOutputSet(2, cHigh);

  // Configure fuzzy inference rules
  fuzzy.setRule(0, 0, 0);
  fuzzy.setRule(1, 1, 1);
  fuzzy.setRule(2, 2, 2);

  // Additional configuration
  fuzzy.setSetPoint(50);
  fuzzy.setIterations(20);

  Serial.println("Configuration completed. Enter input values via Serial.");
}

void loop() {
  if (Serial.available()) {
    float input = Serial.parseFloat();
    while (Serial.available()) Serial.read();

    float output = fuzzy.computeOutput(input);

    Serial.print("Input: ");
    Serial.println(input);
    Serial.print("Control Output: ");
    Serial.println(output);
  }
}