/*
 * pvelocidad.c
 *
 * Created on: Oct, 2024
 *     Author: w,x,y,z
 */

#include "pvelocidad.h"

int poner_velocidad(uint16_t y, volatile uint32_t SWST,uint8_t dutyc, uint8_t dutyc_max, uint16_t LOAD){
  do{
    //Mientras el boton siga pulsado no hacer nada, hasta que se suelte
    while(GPIO_PORTB_DATA_R == 0x00){}

    //Leo el estado del boton.
    SWST = GPIO_PORTJ_DATA_R;

    //If para disminuir la velocidad del motor
    //Si PJ0 = 0x01, entonces disminuyo "y" de 5% en 5% por cada pulsación
    if(SWST == 0x01){
      if(y == 0){
        //no hacer nada
      } else{
        y = y - dutyc;
        //Si "y" es menor del 5%, entonces lo hago cero para apagar el motor
        //pero si no es menor disminuyo en 5%.
        if(y <= dutyc){
          y = 0; //Apago el motor.
        }
        // IMPORTANTE
        // Regresar el valor de "y" para que el modulo PID fije el valor del PWM
        // Imprimir el valor de "y" en la pantalla
        //Aplico el valor de "y" al comparador B del generador B.
        //conf_PWM0_GenB(y);

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
        y = y + dutyc;
        //Si el valor de "y" sobrepasa el 97%, lo pongo a (LOAD - 1) que viene siendo el 99% del valor cargado
        //En el registro del load.
        if(y >= dutyc_max){
          y = LOAD - 1; //Mantengo al 100% la intensidad del motor
        }
        //Aplico el valor de "y" al Comparador B del Generador B
        //conf_PWM0_GenB(y);

        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while(GPIO_PORTJ_DATA_R == 0x02){}
      }
    }
  } while(GPIO_PORTB_DATA_R != 0x00);
  return y;
}
