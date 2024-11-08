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

//Prototipo de funcion para configurar el PWM
void conf_Global_PWM0(uint8_t,uint16_t);

//Prototipo de funcion para obtener el LOAD
int PWM_LOAD(uint8_t, uint16_t);

//Prototipo de funcion para obtener el ciclo de trabajo
int PWM_DUTYC(uint8_t, uint8_t, uint16_t);

//Prototipo de funcion para cambiar el ciclo de trabajo
void conf_PWM0_GenB(float);

//Prototipo de funcion para configurar el puerto F para la salida del PWM
void PuertoF_Conf_PWM(void);

#endif
