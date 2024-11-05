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
#include "Max7219.h"

//max7219 pin 1 VCC-->TIVA C 5.00
//max7219 pin 2 GND -->TIVA C GND
//max7219 pin 3 DIN -->TIVA C PA4  SSI0XDAT0 
//max7219 pin 4 /CS -->TIVA C PA3  SSI0Fss 
//max7219 pin 5 CLK -->TIVA C PA2  SSI0Clk 
//max7219 pin x DOUT --> No se usa

int main(void){
	PuertoB_Conf();
	PuertoJ_Conf();
	
	MAX7219_Ini();
	
	Max7219_Transmit(Dcode);		 //Le mandamos al max7219 que va a utilizar el decodificador
	Max7219_Transmit(Intensidad);//Le mandamos la intensidad 5/32 al max7219, segun el datasheet
	Max7219_Transmit(SCAN);
	Max7219_Transmit(shutMode);
	Max7219_Transmit(Nperacion); //Le mandamos al max7219 que no va a realizar nada ?????
	
	velocidaddeseada(speed); //Transmito al MAX7219 la velocidad inicial del motor, el cual es 0
	while(1){
    wait_input();
  }
}
