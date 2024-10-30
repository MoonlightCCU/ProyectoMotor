/*
 * conf_Ports.c
 *
 *  Created on: Jan, 2021
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#include "CONF_PORTS.h"

//Las siguientes funciones son para configurar los puertos a utilizar
void PuertoB_conf(){
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //activa puerto B
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1)==0){} //Espera a que puerto B este listo
  GPIO_PORTB_DEN_R |= 0x01;   //GPIO DIGITAL
  GPIO_PORTB_DIR_R &= ~0x01;    //Pin 0 como entrada.
  GPIO_PORTB_AFSEL_R &= 0x00;  //Sin función alternativa
  GPIO_PORTB_AMSEL_R &= 0x00; //Ninguna función analogica
  GPIO_PORTB_PCTL_R &= 0x00;  //Ninguna función especial a los pines.
  GPIO_PORTB_PUR_R |= 0x01;   //Activo resistencia pull-up
}

void PuertoF_Conf_PWM(){
  //Paso 2: Activar el reloj para el puerto a utilizar, en este caso el puerto F
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	while((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R5)==0){
    //Espera a que puerto F este listo
  }

	//Paso 3 y 4: Configurar funcion alternativa
	GPIO_PORTF_AFSEL_R |= 0x03; //Para funcion alternativa
	GPIO_PORTF_DEN_R |= 0x03; //GPIO DIGITAL
	GPIO_PORTF_PCTL_R &= 0xFFFFFF00;
	GPIO_PORTF_PCTL_R |= 0x00000066; //Funcion alternativa bit 6 para los generadores del modulo
}

void PuertoJ_Conf(){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R8; //activa puerto J
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R8)==0){} //Espera a que puerto J este listo
	GPIO_PORTJ_DIR_R = 0x00; // Pin 0 y 1 como entrada. (Puerto J, los dos botones conectados a la Tiva C)
	GPIO_PORTJ_AFSEL_R = 0X00; //Sin función alternativa
	GPIO_PORTJ_DEN_R |= 0X03; //GPIO DIGITAL
	GPIO_PORTJ_AMSEL_R &= 0X00; // Ninguna función analogica
	GPIO_PORTJ_PCTL_R &= 0X00; //Ninguna función especial a los pines.
	GPIO_PORTJ_PUR_R |= 0x03; //Activo resistencia pull-up
}
