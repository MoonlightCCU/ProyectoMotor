/*
 * main.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#include "modules_conf.h"
#include "CONF_PORTS.h"
#include "PWM.h"
#include "pvelocidad.h"

uint8_t vel;
uint16_t y;

//main function
int main(void){
	//Configuracion del puerto J
  PuertoJ_Conf();
	PuertoB_conf();

	//Configuracion del PWM con duty cycle al 50% (por defecto) del valor cargado en el registro PMW0_0_LOAD_R
	y = conf_Global_PWM0(div,freq);
	
	while(1){
    if((GPIO_PORTB_DATA_R & 0x01) == 0){        //Detecta si el botón en PortB fue presionado
      while((GPIO_PORTB_DATA_R & 0x01) == 0);   // Espera a que se suelte el botón
      vel = 1;                                  //Activa la señal para entrar a `poner_velocidad`
    }

    if(vel == 1) {
      y = poner_velocidad(y, dutyc, dutyc_max, div, freq);  // Llama a `poner_velocidad` con el ciclo de trabajo actual
      vel = 0;                                              //Reinicia la señal de velocidad para volver a esperar otra pulsación
    }
  }
}
