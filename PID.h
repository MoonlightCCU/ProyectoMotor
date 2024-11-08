// Source https://www.quora.com/How-do-I-implement-a-PID-controller-using-a-Tiva-C-TM4C123G-Launchpad-Cortex-M4
#include <stdint.h>

// PID structure
typedef struct {
  float Kp;          // Proportional gain
  float Ki;          // Integral gain
  float Kd;          // Derivative gain
  float prev_error;  // Previous error
  float integral;    // Integral value
}PID_Controller;

void PID_Init(PID_Controller *, float, float, float);
float PID_Update(PID_Controller *, float, float, float);
