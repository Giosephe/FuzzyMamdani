/*
  FuzzyMamdani_InicioRapido.ino - Ejemplo para la Librería FuzzyMamdani
  Autor: Kennet Morillo
  Creado en: 15/01/2025
  Licencia: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
*/

#include <FuzzyMamdani.h>

// Instancia global de la librería FuzzyMamdani
FuzzyMamdani fuzzy;

void setup() {
  Serial.begin(9600); // Inicializar comunicación serial
  Serial.println("Ejemplo de Inicio Rápido de la Librería FuzzyMamdani");

  // Solicitar el punto de ajuste (SetPoint) al usuario
  float setPoint = solicitarSetPoint();
  fuzzy.setSetPoint(setPoint);

  // Configurar el número de conjuntos difusos (entrada y salida)
  fuzzy.setNumSets(4); // Usando 4 conjuntos en este ejemplo

  // Definir conjuntos difusos de entrada (error)
  FuzzySet eMuyBajo = {{0, 1, 3}, 'T'};        // Error muy pequeño (Triangular)
  FuzzySet eBajo    = {{2, 5, 15}, 'T'};       // Error pequeño (Triangular)
  FuzzySet eMedio   = {{8, 20, 25, 50}, 'O'};  // Error moderado (Trapezoidal)
  FuzzySet eAlto    = {{40, 60, 100, 100}, 'O'}; // Error grande (Trapezoidal)

  fuzzy.setInputSet(0, eMuyBajo);
  fuzzy.setInputSet(1, eBajo);
  fuzzy.setInputSet(2, eMedio);
  fuzzy.setInputSet(3, eAlto);

  // Definir conjuntos difusos de salida (control)
  FuzzySet cMuyBajo = {{0, 2, 6}, 'T'};        // Ajuste mínimo de control (Triangular)
  FuzzySet cBajo    = {{4, 6, 10, 20}, 'O'};   // Ajuste leve de control (Trapezoidal)
  FuzzySet cMedio   = {{18, 30, 55}, 'T'};     // Ajuste moderado de control (Triangular)
  FuzzySet cAlto    = {{45, 70, 100, 100}, 'O'}; // Ajuste alto de control (Trapezoidal)

  fuzzy.setOutputSet(0, cMuyBajo);
  fuzzy.setOutputSet(1, cBajo);
  fuzzy.setOutputSet(2, cMedio);
  fuzzy.setOutputSet(3, cAlto);

  // Configurar reglas difusas
  fuzzy.setRule(0, 0, 0); // Si el Error es MuyBajo, el Control es MuyBajo
  fuzzy.setRule(1, 1, 1); // Si el Error es Bajo, el Control es Bajo
  fuzzy.setRule(2, 2, 2); // Si el Error es Medio, el Control es Medio
  fuzzy.setRule(3, 3, 3); // Si el Error es Alto, el Control es Alto

  // Parámetros de configuración adicionales
  fuzzy.setIterations(20);       // Número de iteraciones para el cálculo del centroide
  fuzzy.setNegativeErrorOff(true); // Ignorar errores negativos

  Serial.println("Configuración completada.");
  Serial.println("Instrucciones:");
  Serial.println("1. Ingrese un valor numérico mediante el Monitor Serial.");
  Serial.println("2. El programa calculará y mostrará la salida de control.");
  Serial.println("3. Para probar entradas predefinidas, escriba 'prueba'.");
  Serial.println("4. Para cambiar el SetPoint, escriba 'setpoint X' (por ejemplo, 'setpoint 90').");
}

void loop() {
  if (Serial.available()) {
    String entradaUsuario = Serial.readStringUntil('\n'); // Leer entrada como una cadena
    entradaUsuario.trim(); // Eliminar espacios en blanco al inicio/final

    // Manejar pruebas predefinidas
    if (entradaUsuario.equalsIgnoreCase("prueba")) {
      ejecutarPruebasPredefinidas();
    }
    // Configurar dinámicamente el SetPoint
    else if (entradaUsuario.startsWith("setpoint ")) {
      float nuevoSetPoint = entradaUsuario.substring(9).toFloat();
      fuzzy.setSetPoint(nuevoSetPoint);
      Serial.print("Nuevo SetPoint configurado: ");
      Serial.println(nuevoSetPoint);
    }
    // Manejar entrada regular para calcular la salida difusa
    else {
      manejarEntradaDifusa(entradaUsuario);
    }
  }
}

// Función para solicitar el SetPoint al usuario
float solicitarSetPoint() {
  Serial.println("Por favor, ingrese el SetPoint inicial:");
  while (!Serial.available()) {
    delay(100); // Esperar entrada del usuario
  }
  String entrada = Serial.readStringUntil('\n');
  entrada.trim();
  float setPoint = entrada.toFloat();
  Serial.print("SetPoint inicial configurado en: ");
  Serial.println(setPoint);
  return setPoint;
}

// Función para ejecutar pruebas predefinidas
void ejecutarPruebasPredefinidas() {
  float setPoint = fuzzy.getSetPoint(); // Obtener el SetPoint actual
  float errores[] = {60, 45, 25, 10, 5, 1}; // Errores definidos
  Serial.println("Ejecutando pruebas predefinidas...");

  for (int i = 0; i < sizeof(errores) / sizeof(errores[0]); i++) {
    float entradaPrueba = setPoint - errores[i]; // Calcular entrada de prueba
    float salida = fuzzy.computeOutput(entradaPrueba);
    mostrarResultados(entradaPrueba, salida, setPoint - entradaPrueba); // Incluir error en los resultados
  }
}

// Función para manejar entrada regular
void manejarEntradaDifusa(String entradaUsuario) {
  if (!entradaUsuario.toFloat() && entradaUsuario != "0") {
    Serial.println("Error: Entrada no válida. Ingrese un valor numérico.");
  } else {
    float entrada = entradaUsuario.toFloat();
    float setPoint = fuzzy.getSetPoint(); // Obtener el SetPoint actual
    if (entrada >= 0 && entrada <= 100) {
      float salida = fuzzy.computeOutput(entrada);
      if (isnan(salida)) {
        Serial.println("Error: No se puede calcular la salida. Verifique la configuración de los conjuntos difusos.");
      } else {
        mostrarResultados(entrada, salida, setPoint - entrada); // Incluir error en los resultados
      }
    } else {
      Serial.println("Error: Entrada fuera de rango. Ingrese un valor entre 0 y 100.");
    }
  }
}

// Función para mostrar resultados de manera formateada
void mostrarResultados(float entrada, float salida, float error) {
  Serial.println("========== RESULTADO ==========");
  Serial.print("Valor de Entrada: ");
  Serial.println(entrada);
  Serial.print("Error: ");
  Serial.println(error);
  Serial.print("Salida de Control: ");
  Serial.println(salida);
  Serial.println("===============================");
}