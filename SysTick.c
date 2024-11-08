/*
 * SysTick.c
 *
 *  Created on: May 10, 2023
 *      Author: canul
 */
#include "SysTick.h"

void SysTick_Conf(float dt){
  /* Ecuaciones para calcular el valor a cargar en el SysTick:
   * La frecuencia del PIOSC (Precision Internal Oscillator) = 16 MHz
   * => PIOSC/4 = 4 MHz
   * Tiempo = (valor cargado+1)Tiempo de oscilación
   * valor cargado+1 = Tiempo/Tiempo de oscilación
   * valor cargado = (Tiempo/Tiempo de oscilación)-1
   * valor cargado = (Tiempo*frecuencia de oscilación)-1
   * Tiempo = 0.01s, frecuencia = 4000000 Hz
   * valor a cargar = 39999
   */

  uint32_t reload = (dt*4000000)-1;

  NVIC_ST_CTRL_R &= 0x00; //Detengo el timer
  NVIC_ST_RELOAD_R = reload; //Valor del tick de 0.01 seg
  NVIC_ST_CURRENT_R = 0x00000000; //Inicio la cuenta del timer en cero
}

void SysTick_Init(){
  NVIC_ST_CTRL_R |= 0x01; //Inicio el timer sin interrupcion
}

void SysTick_Stop(){
  NVIC_ST_CTRL_R &= 0x00; //Detengo el timer
  NVIC_ST_CURRENT_R = 0x00000000; //Inicio la cuenta del timer en cero
}
