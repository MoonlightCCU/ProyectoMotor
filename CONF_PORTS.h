/*
 * conf_ports.h
 *
 *  Created on: jan, 2021
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#ifndef CONFPORTS_H
#define CONFPORTS_H

#include <stdint.h>
#include "tm4c1294ncpdt.h"

//Prototipos de las funciones del archivo "conf_ports.c"
//Configura el pin 0 del puerto B como entrada pull-up
void PuertoB_conf(void);

//Función para configurar los botones del puerto J
void PuertoJ_Conf(void);

//Función para configurar GeneradorA(PF0) y GeneradorB(PF1) como salidas para PWM
void PuertoF_Conf_PWM(void);

#endif
