/*
 * main.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 */

#include "CONF_PORTS.h"
#include "PWM.h"
#include "pvelocidad.h"
#include "tm4c1294ncpdt.h"

#define div         32      //El valor del divisor de sysclk(16MHz) para el PWM
#define freq        500     //La frequencia que deseamos
#define dutyc       5       //El % por cada pulsación de los botones
#define dutyc_max   97      //El % maximo que no podra ser superado por la suma

// Aqui van las definiciones (poner tal vez en un archivo .c?)
//Declaro las dos variables para la configuracion del PWM
//uint16_t yi = 0;
uint16_t LOAD = 0;
uint16_t y = 0;
volatile uint32_t SWT2 = 0;

//main function
int main(void){
  // Obtengo y al 50%, y el valor de LOAD para el registro PMW0_0_LOAD_R
  y = PWM_DUTYC(50,div,freq);
	//Configuracion del puerto J
  PuertoJ_Conf();
	PuertoB_conf();

	//Configuracion del PWM con duty cycle al 50% (por defecto) del valor cargado en el registro PMW0_0_LOAD_R
	conf_Global_PWM0(div,freq);
	
  //volatile uint32_t SWST = 0;
  //uint16_t dutyct = PWM_DUTYC(dutyc, div, freq);
  //uint16_t dutyct_max = PWM_DUTYC(dutyc_max,div,freq);
  //LOAD = PWM_LOAD(div,freq);
	while(1){
    SWT2 = GPIO_PORTB_DATA_R;
    if(SWT2 == 0x00) {
      y = poner_velocidad(y,dutyc,dutyc_max,div,freq);
      //Aqui le pasamos el valor al PID y se encarga de lo demas
      //conf_PWM0_GenB(y); //Esto debera ir dentro del modulo PID
    }
    while(GPIO_PORTB_DATA_R == 0x00){}
    // Aqui calcula el PID los valores?
  //do{
    //Mientras el boton siga pulsado no hacer nada, hasta que se suelte
    //while(GPIO_PORTB_DATA_R == 0x00){}
    /*
    //Leo el estado del boton.
    SWST = GPIO_PORTJ_DATA_R;

    //If para disminuir la velocidad del motor
    //Si PJ0 = 0x01, entonces disminuyo "y" de 5% en 5% por cada pulsación
    if(SWST == 0x01){
      if(y == 0){
        //no hacer nada
      } else{
        y = y - dutyct;
        //Si "y" es menor del 5%, entonces lo hago cero para apagar el motor
        //pero si no es menor disminuyo en 5%.
        if(y <= dutyct){
          y = 0; //Apago el motor.
        }
        // IMPORTANTE
        // Regresar el valor de "y" para que el modulo PID fije el valor del PWM
        // Imprimir el valor de "y" en la pantalla
        //Aplico el valor de "y" al comparador B del generador B.
        conf_PWM0_GenB(y);

        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while(GPIO_PORTJ_DATA_R == 0x01){}
      }
    }

    //If para aumentar la intensidad del motor
    //Si PJ1 = 0x02 (esta pulsado) aumento el valor de y en 5%
    if(SWST == 0x02){
      if(y == (LOAD-1)){
        //no hacer nada
      } else {
        y = y + dutyct;
        //Si el valor de "y" sobrepasa el 97%, lo pongo a (LOAD - 1) que viene siendo el 99% del valor cargado
        //En el registro del load.
        if(y >= dutyct_max){
          y = LOAD-1; //Mantengo al 100% la intensidad del motor
        }
        //Aplico el valor de "y" al Comparador B del Generador B
        conf_PWM0_GenB(y);

        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while(GPIO_PORTJ_DATA_R == 0x02){}
      }
    }
    */
	}
}
