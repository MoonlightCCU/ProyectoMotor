/*
 * main.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 */

#include "CONF_PORTS.h"
#include "PWM.h"
#include "pvelocidad.h"

#define div         32      //El valor del divisor de sysclk(16MHz) para el PWM
#define freq        500     //La frequencia que deseamos
#define dutyc       5       //El % por cada pulsación de los botones
#define dutyc_max   97      //El % maximo que no podra ser superado por la suma

// Aqui van las definiciones (poner tal vez en un archivo .c?)
//Declaro las dos variables para la configuracion del PWM
uint16_t y = 0;
uint16_t LOAD = 0;
volatile uint32_t SWST = 0;

//main function
int main(void){
  // Obtengo y al 50%, y el valor de LOAD para el registro PMW0_0_LOAD_R
  y = PWM_DUTYC(50,div,freq);
  LOAD = PWM_LOAD(div,freq); //Quizas pasarlo de una vez a conf_Global_PWM0?

	//Configuracion del puerto J
  PuertoJ_Conf();
	
	//Configuracion del PWM con duty cycle al 50% (por defecto) del valor cargado en el registro PMW0_0_LOAD_R
	conf_Global_PWM0(div,freq);
	
	while(1){
    if(GPIO_PORTJ_DATA_R == 0x04) {
      y = poner_velocidad(y,SWST,dutyc,dutyc_max,LOAD);
      //Aqui le pasamos el valor al PID y se encarga de lo demas
      conf_PWM0_GenB(y); //Esto debera ir dentro del modulo PID
    }
    // Aqui calcula el PID los valores?
    while(GPIO_PORTJ_DATA_R == 0x04){
      //Este while es para impedir los falsos disparos del boton
      //Esto lo complica todo porque aun no podemos usar interrupciones
    }
	}
}
