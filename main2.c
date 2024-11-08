/*
 * main.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#include "test.h"
#include <stdio.h>

int main(void){
  poner_vel start;
  Poner_Vel_Init(&start, 0, 130, 5, 30.0, 0, 0);
  printf("El valor de RPM en main antes de Poner_Vel_Wait es: %f\n",start.RPM);
  printf("\nEl valor de vel en main antes de Poner_Vel_Wait es: %d",start.vel);
  printf("\nEl valor de SWST en el main antes de Poner_Vel_Wait es: %04x",start.SWST);
  
  printf("\n\n");
  Poner_Vel_Wait(&start);

  printf("\n Los valores despues de Poner_Vel_Wait son: ");
  printf("\nEl valor de RPM en main es: %f",start.RPM);
  printf("\nEl valor de vel en main es: %d",start.vel);
  printf("\nEl valor de SWST en el main es: %04x",start.SWST);
}
