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
float PID_Update(PID_Controller *pid, float setpoint, float measured_value, float dt){
  float error = setpoint - measured_value;
  pid->integral += error * dt;           // Integral term
  float derivative = (error - pid->prev_error) / dt; // Derivative term

  // Calculate control output
  float output = (pid->Kp * error) + (pid->Ki * pid->integral) + (pid->Kd * derivative);

  // Save current error for next derivative calculation
  pid->prev_error = error;

  return output;
}
