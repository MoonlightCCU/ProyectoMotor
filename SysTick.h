/*
 * SysTick.h
 *
 *  Created on: May 10, 2023
 *      Author: Carlos Canul
 */
#include <stdint.h>
#include "tm4c1294ncpdt.h"


//Prototipo de función que sirve para inicializar las configuraciones del SysTick
void SysTick_Conf(float);

//Prototipo de función que sirve para inicializar el SysTick
void SysTick_Init(void);

//Prototipo de función que sirve para detener el SysTick
void SysTick_Stop(void);
