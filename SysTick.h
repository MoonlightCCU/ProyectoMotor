/*
 * SysTick.h
 *
 *  Created on: May 10, 2023
 *      Author: Carlos Canul
 */
#include <stdint.h>
#include "tm4c1294ncpdt.h"


//Función para inicializar las configuraciones del SysTick
void SysTick_Conf(float);
void SysTick_Init(void);
void SysTick_Stop(void);
