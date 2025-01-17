/*
  FuzzyMamdani_3Sets.ino - Ejemplo con 3 conjuntos difusos
  Autor: Kennet Morillo
  Creado en: 15/01/2025
  Licencia: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
*/

#include <FuzzyMamdani.h>

// Instancia global de la librería FuzzyMamdani
FuzzyMamdani fuzzy;

void setup() {
  Serial.begin(9600);
  Serial.println("Ejemplo FuzzyMamdani: 3 Conjuntos");

  // Configurar el número de conjuntos difusos
  fuzzy.setNumSets(3);

  // Definir conjuntos difusos de entrada (error)
  FuzzySet eBajo    = {{0, 10, 20}, 'T'};
  FuzzySet eMedio   = {{15, 30, 45}, 'T'};
  FuzzySet eAlto    = {{40, 70, 100}, 'T'};

  fuzzy.setInputSet(0, eBajo);
  fuzzy.setInputSet(1, eMedio);
  fuzzy.setInputSet(2, eAlto);

  // Definir conjuntos difusos de salida (control)
  FuzzySet cBajo    = {{0, 10, 20}, 'T'};
  FuzzySet cMedio   = {{15, 40, 60}, 'T'};
  FuzzySet cAlto    = {{50, 75, 100}, 'T'};

  fuzzy.setOutputSet(0, cBajo);
  fuzzy.setOutputSet(1, cMedio);
  fuzzy.setOutputSet(2, cAlto);

  // Configurar reglas difusas
  fuzzy.setRule(0, 0, 0);
  fuzzy.setRule(1, 1, 1);
  fuzzy.setRule(2, 2, 2);

  // Configuración adicional
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