/*
 * conf_ports.h
 *
 *  Created on: jan, 2021
 *      Author: Carlos Canul
 */

#include <stdint.h>
#include "tm4c1294ncpdt.h"

//Prototipos de las funciones del archivo "conf_ports.c"
//Libreria de mi propia autoria para cunfigurar los puertos

//Función para configurar el puerto A como salida.
void PuertoA_Conf(void);

//Función para configurar el puerto A como salida para la LCD
void PuertoA_LCD(void);

//Función para configurar el puerto A como salida para la LCD del Nokia 5110
void PuertoA_Nokia5110(void);

//Configura el puerto B pines 0:4 como entradas con interrupciones y resistencia pull-up
void PuertoB_Int(void);

//Función para configurar los botones del puerto J
void PuertoJ_Conf(void);

//Función para configurar los botones del puerto J con interrupciones
void PuertoJ_Int(void);

//Función para configurar el puerto PK7 como salida RTC
void PuertoK7_Conf_RTC(void);

//Función para configurar PA0 como entrada de Timer0A
void PuertoA0_Conf_T0CCP0(void);

//Función para configurar PF0 Y PF4 como salidas (Leds de la Tiva C)
void PuertoF_Conf_Leds(void);

//Función para configurar GeneradorA(PF0) y GeneradorB(PF1) como salidas para PWM
void PuertoF_Conf_PWM(void);

//Configura el puerto K pines 0:3 como salidas
void PuertoK_Conf(void);

//Configura el puerto L pines 0:3 como salidas
void PuertoL_Conf(void);

//Configura el puerto L pines PL1(PhA) y PL2(PhB) como entradas para el modulo de cuadratura
void PuertoL_Conf_QEI(void);
