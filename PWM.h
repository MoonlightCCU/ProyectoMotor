/*
 * PWM.h
 *
 *  Created on: Mar, 2022
 *      Author: Carlos Canul
 */

#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "CONF_PORTS.h"

int conf_Global_PWM0(uint8_t div,uint16_t freq);
int PWM_LOAD(uint8_t div, uint16_t freq);
int PWM_DUTYC(uint8_t dutyc, uint8_t div, uint16_t freq);
void conf_PWM0_GenB(uint16_t y);
