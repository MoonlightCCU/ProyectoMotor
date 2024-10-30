/*
 * pvelocidad.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#include "pvelocidad.h"

int poner_velocidad(uint16_t y,uint8_t dutyc, uint8_t dutyc_max, uint8_t div, uint16_t freq){
  volatile uint32_t SWST;
  uint16_t dutyct = PWM_DUTYC(dutyc, div, freq);
  uint16_t dutyct_max = PWM_DUTYC(dutyc_max,div,freq);
  uint16_t LOAD = PWM_LOAD(div,freq);
  do{
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
      if(y == (LOAD - 1)){
        //no hacer nada
      } else {
        y = y + dutyct;
        //Si el valor de "y" sobrepasa el 97%, lo pongo a (LOAD - 1) que viene siendo el 99% del valor cargado
        //En el registro del load.
        if(y >= dutyct_max){
          y = LOAD - 1; //Mantengo al 100% la intensidad del motor
        }
        //Aplico el valor de "y" al Comparador B del Generador B
        conf_PWM0_GenB(y);

        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while(GPIO_PORTJ_DATA_R == 0x02){}
      }
    }

    // Condición de salida si se detecta una nueva pulsación en el botón de PortB
    if((GPIO_PORTB_DATA_R & 0x01) == 0) {
      while((GPIO_PORTB_DATA_R & 0x01) == 0){}  //Espera a que el botón de PortB se suelte
      break;  // Sale del do-while
    }
  } while(1);
  return y;
}
