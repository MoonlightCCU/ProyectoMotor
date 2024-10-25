/*
 * PWM.h
 *
 *  Created on: Mar, 2022
 *      Author: Carlos Canul
 */

#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "CONF_PORTS.h"

void conf_Global_PWM0(uint16_t,uint16_t);
void conf_PWM0_GenA(uint16_t);
void conf_PWM0_GenB(uint16_t);
