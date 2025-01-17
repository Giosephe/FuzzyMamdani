/*
  FuzzyMamdani_5Sets.ino - Example with 5 fuzzy sets
  Author: Kennet Morillo
  Created on: 15/01/2025
  License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
*/

#include <FuzzyMamdani.h>

FuzzyMamdani fuzzy;

void setup() {
  Serial.begin(9600);
  Serial.println("FuzzyMamdani Example: 5 Sets");

  fuzzy.setNumSets(5);

  FuzzySet eVeryLow = {{0, 5, 10}, 'T'};
  FuzzySet eLow     = {{8, 15, 25}, 'T'};
  FuzzySet eMedium  = {{20, 40, 60}, 'T'};
  FuzzySet eHigh    = {{50, 70, 85}, 'T'};
  FuzzySet eVeryHigh = {{80, 90, 100}, 'T'};

  fuzzy.setInputSet(0, eVeryLow);
  fuzzy.setInputSet(1, eLow);
  fuzzy.setInputSet(2, eMedium);
  fuzzy.setInputSet(3, eHigh);
  fuzzy.setInputSet(4, eVeryHigh);

  FuzzySet cVeryLow = {{0, 5, 10}, 'T'};
  FuzzySet cLow     = {{8, 15, 25}, 'T'};
  FuzzySet cMedium  = {{20, 40, 60}, 'T'};
  FuzzySet cHigh    = {{50, 70, 85}, 'T'};
  FuzzySet cVeryHigh = {{80, 90, 100}, 'T'};

  fuzzy.setOutputSet(0, cVeryLow);
  fuzzy.setOutputSet(1, cLow);
  fuzzy.setOutputSet(2, cMedium);
  fuzzy.setOutputSet(3, cHigh);
  fuzzy.setOutputSet(4, cVeryHigh);

  fuzzy.setRule(0, 0, 0);
  fuzzy.setRule(1, 1, 1);
  fuzzy.setRule(2, 2, 2);
  fuzzy.setRule(3, 3, 3);
  fuzzy.setRule(4, 4, 4);

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