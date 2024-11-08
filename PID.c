#include "PID.h"

// Initialize the PID controller
void PID_Init(PID_Controller *pid, float Kp, float Ki, float Kd) {
  pid->Kp = Kp;
  pid->Ki = Ki;
  pid->Kd = Kd;
  pid->prev_error = 0.0;
  pid->integral = 0.0;
}

// Update the PID controller
/* PID_Update crea un puntero con la direccion de la estructura pid para almacenar 2
 * valores (prev_error e integral) y acceder a Kp,Ki y Kd. con el valor de RMP
 * deseado y el valor actual del sensor (en RPM) calcula el error actual. Una vez
 * obtenido el error actual se calcula la integral con el valor de "dt". Para
 * calcular la derivada se resta el error actual menos el error previo y se divide
 * entre delta de t -> ((y2-y1)/(x2-x1)) donde y2 = error actual, y1 = error previo
 * y x2-x1 = dt.
 * Para calcular el PID: para el Proporcional se multiplica el error actual por la
 * ganancia Kp can la que se inicializo la estructura pid. Para la Integral se 
 * multiplica la integral que se calculo previamente por la ganancia Ki. Para la
 * derivada se multiplica la derivada calculada previamente por la ganancia Kd y
 * luego se suman los tres valores para obtener la salida del PID. Por ultimo es
 * importante almacenar el valor del error actual que en el siguiente ciclo pasara
 * a ser el error previo para calcular la derivada.
 */
float PID_Update(PID_Controller *pid, float setpoint, float measured_value, float dt){
  float error = setpoint - measured_value;
  pid->integral += error * dt;
  float derivative = (error - pid->prev_error) / dt;

  // Calculate control output
  float output = (pid->Kp * error) + (pid->Ki * pid->integral) + (pid->Kd * derivative);

  // Save current error for next derivative calculation
  pid->prev_error = error;

  return output;
}
