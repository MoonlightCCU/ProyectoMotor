#include <stdint.h>

// Estructura PID
typedef struct {
  float Kp;          // Ganancia Proporcional
  float Ki;          // Ganancia Integral
  float Kd;          // Ganancia Derivativa
  float prev_error;  // Error Previo
  float integral;    // Valor de la Integral
  float cout_prev;
  float control_output;
}PID_Controller;

//Prototipo de función que sirve para inicializar los valores del PID
void PID_Init(PID_Controller *, float, float, float);

//Prototipo de función que sirve para calcular el PID
void PID_Update(PID_Controller *, float, float, float);
