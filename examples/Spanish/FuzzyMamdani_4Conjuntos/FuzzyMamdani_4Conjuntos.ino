/*
  FuzzyMamdani_4Conjuntos.ino - Ejemplo con 4 conjuntos difusos
  Autor: Kennet Morillo
  Creado en: 15/01/2025
  Licencia: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
*/

#include <FuzzyMamdani.h>

FuzzyMamdani fuzzy;

void setup() {
  Serial.begin(9600);
  Serial.println("Ejemplo FuzzyMamdani: 4 Conjuntos");

  fuzzy.setNumSets(4);

  FuzzySet eMuyBajo = {{0, 5, 10}, 'T'};
  FuzzySet eBajo    = {{8, 15, 25}, 'T'};
  FuzzySet eMedio   = {{20, 40, 60}, 'T'};
  FuzzySet eAlto    = {{50, 75, 100}, 'T'};

  fuzzy.setInputSet(0, eMuyBajo);
  fuzzy.setInputSet(1, eBajo);
  fuzzy.setInputSet(2, eMedio);
  fuzzy.setInputSet(3, eAlto);

  FuzzySet cMuyBajo = {{0, 5, 10}, 'T'};
  FuzzySet cBajo    = {{8, 15, 25}, 'T'};
  FuzzySet cMedio   = {{20, 40, 60}, 'T'};
  FuzzySet cAlto    = {{50, 75, 100}, 'T'};

  fuzzy.setOutputSet(0, cMuyBajo);
  fuzzy.setOutputSet(1, cBajo);
  fuzzy.setOutputSet(2, cMedio);
  fuzzy.setOutputSet(3, cAlto);

  fuzzy.setRule(0, 0, 0);
  fuzzy.setRule(1, 1, 1);
  fuzzy.setRule(2, 2, 2);
  fuzzy.setRule(3, 3, 3);

  fuzzy.setSetPoint(50);
  fuzzy.setIterations(20);

  Serial.println("Configuración completada. Ingrese valores de entrada mediante el Monitor Serial.");
}

void loop() {
  if (Serial.available()) {
    float input = Serial.parseFloat();
    while (Serial.available()) Serial.read();

    float output = fuzzy.computeOutput(input);

    Serial.print("Entrada: ");
    Serial.println(input);
    Serial.print("Salida de control: ");
    Serial.println(output);
  }
}