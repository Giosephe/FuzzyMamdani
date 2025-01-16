/*
  FuzzyMamdani.cpp - Fuzzy Logic Controller Library for Arduino
  Author: Kennet Morillo
  Created on: 15/01/2025
  License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International

  This file is part of the FuzzyMamdani library.
  Usage:
    - Educational use: Free of charge.
    - Commercial use: Requires prior written authorization.

  Contact: kennetmorillostw@hotmail.com
*/

#include "FuzzyMamdani.h"

// Constructor: Initialize default values
FuzzyMamdani::FuzzyMamdani() {
  _numSets = 3;             // Default number of sets
  _numIterations = 20;      // Default number of iterations
  _setPoint = 0.0;          // Default SetPoint
  _negativeErrorOff = true; // Default: Ignore negative errors

  // Initialize empty sets and rules
  for (byte i = 0; i < MAX_SETS; i++) {
    _inputs[i] = {{0, 0, 0, 0}, 'T'};
    _outputs[i] = {{0, 0, 0, 0}, 'T'};
    _rules[i] = {i, i}; // Default direct mapping
  }
}

// Set the number of fuzzy sets
void FuzzyMamdani::setNumSets(byte n) {
  _numSets = constrain(n, 3, MAX_SETS);
}

// Define an input fuzzy set
void FuzzyMamdani::setInputSet(byte idx, FuzzySet s) {
  if (idx < _numSets) _inputs[idx] = s;
}

// Define an output fuzzy set
void FuzzyMamdani::setOutputSet(byte idx, FuzzySet s) {
  if (idx < _numSets) _outputs[idx] = s;
}

// Define a fuzzy rule
void FuzzyMamdani::setRule(byte ruleIdx, byte inputIdx, byte outputIdx) {
  if (ruleIdx < _numSets && inputIdx < _numSets && outputIdx < _numSets) {
    _rules[ruleIdx].inputIdx = inputIdx;
    _rules[ruleIdx].outputIdx = outputIdx;
  }
}

// Set the number of iterations for centroid calculation
void FuzzyMamdani::setIterations(byte iterations) {
  _numIterations = iterations;
}

// Set the SetPoint
void FuzzyMamdani::setSetPoint(float sp) {
  _setPoint = sp;
}

// Get the current SetPoint
float FuzzyMamdani::getSetPoint() {
  return _setPoint;
}

// Ignore negative errors
void FuzzyMamdani::setNegativeErrorOff(bool off) {
  _negativeErrorOff = off;
}

// Compute the control output
float FuzzyMamdani::computeOutput(float currentInput) {
  float error = _setPoint - currentInput;
  if (_negativeErrorOff && error < 0) error = 0;
  return _inferenceEngine(error);
}

// Calculate the membership value for a given input and fuzzy set
float FuzzyMamdani::_calculateMembership(float x, const FuzzySet &s) {
  const float* p = s.points;
  if (s.type == 'T') {
    if (x <= p[0] || x >= p[2]) return 0.0;
    if (x < p[1]) return (x - p[0]) / (p[1] - p[0]);
    return (p[2] - x) / (p[2] - p[1]);
  } else if (s.type == 'O') {
    if (x <= p[0] || x >= p[3]) return 0.0;
    if (x < p[1]) return (x - p[0]) / (p[1] - p[0]);
    if (x <= p[2]) return 1.0;
    return (p[3] - x) / (p[3] - p[2]);
  }
  return 0.0;
}

// Inference engine to calculate the output
float FuzzyMamdani::_inferenceEngine(float error) {
  float rangeMin = 0.0, rangeMax = 100.0;
  float step = (rangeMax - rangeMin) / (_numIterations - 1);
  float numerator = 0.0, denominator = 0.0;

  for (int i = 0; i < _numIterations; i++) {
    float xOutput = rangeMin + i * step;
    float muFinal = 0.0;

    for (byte r = 0; r < _numSets; r++) {
      float muError = _calculateMembership(error, _inputs[_rules[r].inputIdx]);
      float muControl = _calculateMembership(xOutput, _outputs[_rules[r].outputIdx]);
      muFinal = max(muFinal, min(muError, muControl));
    }

    numerator += xOutput * muFinal;
    denominator += muFinal;
  }

  return (denominator == 0) ? 0.0 : numerator / denominator;
}