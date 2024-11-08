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
#include "CONF_PORTS.h"

void conf_Global_PWM0(uint8_t,uint16_t);
int PWM_LOAD(uint8_t, uint16_t);
int PWM_DUTYC(uint8_t, uint8_t, uint16_t);
void conf_PWM0_GenB(float);

#endif
