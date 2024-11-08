#include <stdint.h>

// PID structure
typedef struct {
  uint8_t RPM_min;
  uint8_t RPM_max;
  uint8_t RPM_adj;
  float RPM;
  volatile uint8_t vel;
  volatile uint32_t SWST;
}poner_vel;

void Poner_Vel_Init(poner_vel *, uint8_t, uint8_t, uint8_t,float,volatile uint8_t, volatile uint32_t);
void Poner_Vel_Wait(poner_vel *);
void Poner_Vel_Update(poner_vel *);
