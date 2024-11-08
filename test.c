#include <stdio.h>
#include "test.h"

void Poner_Vel_Init(poner_vel *start, uint8_t RPM_min, uint8_t RPM_max, uint8_t RPM_adj, float RPM,volatile uint8_t vel, volatile uint32_t SWST){
  start->RPM_min = RPM_min;
  start->RPM_max = RPM_max;
  start->RPM_adj = RPM_adj;
  start->RPM = RPM;
  start->vel = vel;
  start->SWST = SWST;
}

void Poner_Vel_Wait(poner_vel *start){
  start->vel = 10;
  printf("\nEl valor de vel en Poner_Vel_Wait es: %d",start->vel);
  Poner_Vel_Update(start);
}

void Poner_Vel_Update(poner_vel *start){
  start->RPM = 120;
  start->SWST = 0x03;
  printf("\nEl valor de RPM en Poner_Vel_Update es: %f",start->RPM);
  printf("\nEl vaor de SWST en Poner_Vel_Update es: %04x",start->SWST);
}
