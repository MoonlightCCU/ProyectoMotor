/*
 * PWM.h
 *
 *  Created on: Mar, 2022
 *      Author: Carlos Canul
 */

#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include "tm4c1294ncpdt.h"

// Estructura PWM
typedef struct {
  uint8_t div;        //Valor del divisor
  uint16_t freq;      //Valor de la frecuencia deseada
  uint16_t LOAD;      //Valor del LOAD en base a div y freq
  uint16_t dutyc;     //Ciclo de trabajo (0:999) deseado (default = 0);
  //float y_float;    //Variable para almacenar la entrada PID
}PWM_MODULE;

//Prototipo de función que sirve para inicializar los valores del PWM
void PWM0_Init(PWM_MODULE *, uint8_t, uint16_t);//, uint8_t);

//Prototipo de funcion para configurar el PWM
void PWM0_CONF(PWM_MODULE *);

//Prototipo de función que sirve para actualizar el ciclo de trabajo
void PWM0_Update_GenB(float);

//Prototipo de funcion para configurar el puerto F para la salida del PWM
void PWM0_PortF_Conf(void);

#endif
