/*
 * main.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 */

#include "CONF_PORTS.h"
#include "PWM.h"

//main function
int main(void){
	//Declaro las dos variables para la configuracion del PWM
	//100% = 5000 , entonces el 50% = (5000/2)-1
	uint16_t x=2499, y=2499;
	
	//Declaro una variable para almacenar el estado de los botones del puerto J.
	volatile uint32_t SWST = 0;
	
	//Configuracion del puerto J
  PuertoJ_Conf();
	
	//Configuracion del PWM con los valores al 50% del valor cargado en el registro PMW0_0_LOAD_R
	conf_Global_PWM0(x,y);
	
	//Del 50% voy subiendo o bajando con ayuda del siguiente while()
	while(1){
		//Leo el estado del boton.
		SWST = GPIO_PORTJ_DATA_R;
		
		//If para disminuir la intensidad del foco
		//Si PJ0 = 0x01, entonces disminuyo "y" de 249 en 249 por cada pulsación
		//249 es equivalente a un 5% de 5000(Valor del load)
		if(SWST == 0x01){
			y=y-249;
			//Si "y" es menor del 5%, entonces lo devuelvo a 250 para mantener siempre al 5% y no apagar
			//el foco, pero si no es menor disminuyo en 5%.
			if(y <= 249){
				y = 250; //Mantengo el foco al 5% de su intensidad.
			}else{
				//Aplico el valor de "y" al comparador B del generador B.
				conf_PWM0_GenB(y);
				
				//Mientras siga pulsado el boton, no hago nada.
				//Esto es para evitar que se siga ejecutando el if()
				while(GPIO_PORTJ_DATA_R == 0x01){}
			}
			
		}
		
		//If para aumentar la intensidad del foco
		//Si PJ1 = 0x02 (esta pulsado) aumento el valor de y en 5%
		if(SWST == 0x02){
			y = y+249;
			//Si el valor de y sobrepasa 4999, lo regreso a 4998 que viene siendo el 99% del valor cargado
			//En el registro del load.
			if(y >= 4999){
				y = 4998; //Mantengo al 99% la intensidad del foco.
			}else{
				//Aplico el valor de "y" al Comparador B del Generador B
				conf_PWM0_GenB(y);
				
				//Mientras siga pulsado el boton, no hago nada.
				//Esto es para evitar que se siga ejecutando el if()
				while(GPIO_PORTJ_DATA_R == 0x02){}
			}
		}
	}
}
