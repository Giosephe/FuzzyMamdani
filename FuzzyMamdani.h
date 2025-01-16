/*
  FuzzyMamdani.h - Fuzzy Logic Controller Library for Arduino
  Author: Kennet Morillo
  Created on: 15/01/2025
  License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International

  This file is part of the FuzzyMamdani library.
  Usage:
    - Educational use: Free of charge.
    - Commercial use: Requires prior written authorization.

  Contact: kennetmorillostw@hotmail.com
*/

#ifndef FuzzyMamdani_h
#define FuzzyMamdani_h

#include "Arduino.h"

// Maximum number of fuzzy sets supported
#define MAX_SETS 5

// Structure for a Fuzzy Set
struct FuzzySet {
  float points[4]; // {Min, Mid1, Mid2, Max} if trapezoidal; {Min, Mid, Max} if triangular
  char type;       // 'T' for triangular, 'O' for trapezoidal
};

// Structure to relate an input set to an output set
struct Rule {
  byte inputIdx;   // Index of the input set
  byte outputIdx;  // Index of the output set
};

// Main class of the library
class FuzzyMamdani {
public:
  // Constructor
  FuzzyMamdani();

  // Configuration methods
  void setNumSets(byte n);                 // Number of fuzzy sets (3 to 5)
  void setInputSet(byte idx, FuzzySet s);  // Define an input fuzzy set
  void setOutputSet(byte idx, FuzzySet s); // Define an output fuzzy set
  void setRule(byte ruleIdx, byte inputIdx, byte outputIdx); // Define a fuzzy rule

  void setIterations(byte iterations);     // Number of discretization iterations
  void setSetPoint(float sp);              // Define SetPoint
  float getSetPoint();                     // Retrieve the current SetPoint
  void setNegativeErrorOff(bool off);      // Ignore negative errors (optional)

  // Operation
  float computeOutput(float currentInput); // Calculate the control output (centroid)

private:
  // Attributes
  byte _numSets;             // Number of enabled fuzzy sets
  FuzzySet _inputs[MAX_SETS];
  FuzzySet _outputs[MAX_SETS];
  Rule _rules[MAX_SETS];     // Rules linking input to output sets

  byte _numIterations;       // Discretization points for centroid calculation
  float _setPoint;           // Target value
  bool  _negativeErrorOff;   // Flag to ignore negative errors

  // Internal methods
  float _calculateMembership(float x, const FuzzySet &s);
  float _inferenceEngine(float error);
};

#endif