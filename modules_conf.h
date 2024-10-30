/*
 * pvelocidad.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#ifndef MODCONF_H
#define MODCONF_H

/*
 * Valores para la configuración del PWM
 */
#define div         32      //El valor del divisor de sysclk(16MHz) para el PWM
#define freq        500     //La frequencia que deseamos
#define dutyc       5       //El % por cada pulsación de los botones
#define dutyc_max   97      //El % maximo que no podra ser superado por la suma

#endif
