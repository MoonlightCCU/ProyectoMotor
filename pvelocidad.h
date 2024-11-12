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

//Estructura poner_vel
typedef struct {
  uint8_t RPM_min;          //Las RPM min, en nuestro caso cero
  uint8_t RPM_max;          //Las RPM maximas, en nuestro caso 130
  uint8_t RPM_adj;          //El tamaño del ajuste para la suma y resta
  float RPM;                //Las RPM que se desean fijar
  float RPM_prev;
  volatile uint8_t vel;     //Variable Para entrar al menu de fijacion
  volatile uint32_t SWST;   //Variable para almacenar el estado del boton
}poner_vel;

//Prototipo para la funcion de inicializacion el modulo
void Poner_Vel_Init(poner_vel *, uint8_t, float);

//Prototipo para la funcion de comprobar la pulsacion del boton B0
void Poner_Vel_Wait(poner_vel *);

//Prototipo para la funcion de poner o fijar la velocidad
void Poner_Vel_Update(poner_vel *);

//Prototipos para configurar los botones de los puertos a utilizar (J0, J1 y B0)
void PuertoB_Conf(void);
void PuertoJ_Conf(void);

#endif
