/*
 * pvelocidad.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#ifndef VELOCIDAD_H
#define VELOCIDAD_H

#include <stdint.h>
#include "Max7219.h"

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


//extern uint8_t RPM_min;    //RPM minimo
//extern uint8_t RPM_max;    //RPM maximo
//extern uint8_t RPM_adj;    //Incremento o Decremento del RPM
//extern float speed;      //Velocidad inicial
//extern volatile uint8_t vel;    //Variable de control para entrar a la funcion poner_velocidad()
//extern volatile uint32_t SWST;  //Variable para almacenar el estado de los botones J0 y J1
//
//void wait_input(void);
//float poner_velocidad(float, uint8_t, uint8_t, uint8_t);

void PuertoB_Conf(void);
void PuertoJ_Conf(void);

#endif
