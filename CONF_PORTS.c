/*
 * conf_Ports.c
 *
 *  Created on: Jan, 2021
 *      Author: Carlos Canul
 */

#include "CONF_PORTS.h"

//Las siguientes funciones son para configurar los puertos a utilizar
void PuertoA_Conf(){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; //Activa puerto A.
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0)==0){} //Espera a que puerto A este listo
	GPIO_PORTA_DEN_R |= 0XFF; //Todos los pines como GPIO Digital
	GPIO_PORTA_DIR_R |= 0XFF; //Todos los pines como salida.
	GPIO_PORTA_AFSEL_R &= 0X00; //Sin función alternativa
	GPIO_PORTA_AMSEL_R &= 0X00; //Ninguna funcion analogica
	GPIO_PORTA_PCTL_R &= 0X00000000; //Ninguna funcion especial a los pines.
}

void PuertoA_LCD(){
  //Configuración del puerto A como salida para LCD
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; //Activa puerto A.
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0)==0){} //Espera a que puerto A este listo
  GPIO_PORTA_DEN_R |= 0XFF; //Todos los pines como GPIO Digital
  GPIO_PORTA_DIR_R |= 0XFF; //Todos los pines como salida.
  GPIO_PORTA_AFSEL_R &= 0X00; //Sin función alternativa
  GPIO_PORTA_AMSEL_R &= 0X00; //Ninguna funcion analogica
  GPIO_PORTA_PCTL_R &= 0X00000000; //Ninguna funcion especial a los pines.
  GPIO_PORTA_DR8R_R = 0xFF;  //Activa salida con 8mA para los pines del puerto A (!IMPORTANTE)
}

void PuertoA_Nokia5110(){
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;        //Prendo puerto A
  while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R0)==0){}      //Espere a que prenda el puerto

  GPIO_PORTA_LOCK_R = 0x4C4F434B; //Desbloqueo el puerto A.
  GPIO_PORTA_CR_R = 0xFF; //Permito los cambios en los pines del puerto A.
  GPIO_PORTA_DEN_R |= 0xDC; //Configuro pines 2,3,4,6,7 del puerto A como digitales
  GPIO_PORTA_AFSEL_R |=0x1C; //1C //Asigno funciones alternativas digitales a los bits 2,3,4 del puerto A
  GPIO_PORTA_AFSEL_R &= ~0xC0; //Desactiva funciones alt a los bits PA6,7
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFF000FF)+0x000FFF00; //Asigno la función digital 15 a los pines 2,3,4 del puerto A
  GPIO_PORTA_AMSEL_R &= ~0xDC; //Desactivo funcion analogica del puerto A pin 2,3,4,6,7
  GPIO_PORTA_DIR_R = (GPIO_PORTA_DIR_R|0xC0); //Configuro pin 6,7 del puerto A como salida
  //GPIO_PORTA_DR8R_R = 0xFF;  //Activa salida con 8mA para los pines del puerto A (!IMPORTANTE)
}

void PuertoA0_Conf_T0CCP0(){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10; //Activa puerto A.
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R10)==0){} //Espera a que puerto A este listo
	//Configura puerto A pin 0 como entrada PCTL = 3 (T0CCP0)
	GPIO_PORTL_DEN_R |= 0x03;
	GPIO_PORTL_DIR_R |= 0x00;
	GPIO_PORTL_AFSEL_R |= 0x03;
	GPIO_PORTL_PCTL_R |= 0x00000033;
}

void PuertoB_Int(){
  //Configura los dos botones de la tiva con interrupciones
  //Revisar el proyecto Interrupts o PLL_LCD, modificar startup
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //activa puerto B
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1)==0){} //Espera a que puerto B este listo
  GPIO_PORTB_DEN_R |= 0x1F;   //GPIO DIGITAL
  GPIO_PORTB_DIR_R &= ~0x1F;    //Pin 0:4 como entrada.
  GPIO_PORTB_AFSEL_R &= 0x00;  //Sin función alternativa
  GPIO_PORTB_AMSEL_R &= 0x00; //Ninguna función analogica
  GPIO_PORTB_PCTL_R &= 0x00;  //Ninguna función especial a los pines.
  GPIO_PORTB_PUR_R |= 0x1F;   //Activo resistencia pull-up

  // Configuración PORTJ1, 0 para activación de interrupción por "falling edge"
  GPIO_PORTB_IS_R &= ~(1<<4)|~(1<<3)|~(1<<2)|~(1<<1)|~(1<<0);     //Hacer que los bits 0:4 sean "edge sensitive"
  GPIO_PORTB_IBE_R &= ~(1<<4)|~(1<<3)|~(1<<2)|~(1<<1)|~(1<<0);    //Activación es controlda por IEV
  GPIO_PORTB_IEV_R &= ~(1<<4)|~(1<<3)|~(1<<2)|~(1<<1)|~(1<<0);    //Activación por "faling edge"
  GPIO_PORTB_ICR_R |= (1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);      //Limpiar cualquier interrupción de prioridad
  GPIO_PORTB_IM_R |= (1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);       //Desenmascarar interrupción

  // Activar interrupción en el registro NVIC y configurar prioridad en 3
  NVIC_PRI0_R = (3<<13);     //Interrupción de prioridad 3
  NVIC_EN0_R |= (1<<1);      //Activar bit de interrupción 1 (Puerto B)(bit1 de EN0)
}

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

void PuertoF_Conf_Leds(){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; //Activa puerto F.
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5)==0){} //Espera a que puerto F este listo
	//Configura puerto F pin 4 y 0 como salidas (Leds de la Tiva C)
	GPIO_PORTF_DEN_R |= 0x11;
	GPIO_PORTF_DIR_R |= 0x11;
	GPIO_PORTF_AFSEL_R &= 0X00;
	GPIO_PORTF_AMSEL_R &= 0X00;
	GPIO_PORTF_PCTL_R &= 0X00000000;
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

void PuertoJ_Int(){
  //Configura los dos botones de la tiva con interrupciones
  //Revisar el proyecto Interrupts o PLL_LCD, modificar startup
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R8; //activa puerto J
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R8)==0){} //Espera a que puerto J este listo
  GPIO_PORTJ_DEN_R |= 0x03;   //GPIO DIGITAL
  GPIO_PORTJ_DIR_R = 0x00;    //Pin 0 y 1 como entrada. (Puerto J, los dos botones conectados a la Tiva C)
  GPIO_PORTJ_AFSEL_R &= 0x00;  //Sin función alternativa
  GPIO_PORTJ_AMSEL_R &= 0x00; //Ninguna función analogica
  GPIO_PORTJ_PCTL_R &= 0x00;  //Ninguna función especial a los pines.
  GPIO_PORTJ_PUR_R |= 0x03;   //Activo resistencia pull-up

  // Configuración PORTJ1, 0 para activación de interrupción por "falling edge"
  GPIO_PORTJ_IS_R &= ~(1<<1)|~(1<<0);     //Hacer que los bits 1 y 0 sean "edge sensitive"
  GPIO_PORTJ_IBE_R &= ~(1<<1)|~(1<<0);    //Activación es controlda por IEV
  GPIO_PORTJ_IEV_R &= ~(1<<1)|~(1<<0);    //Activación por "faling edge"
  GPIO_PORTJ_ICR_R |= (1<<1)|(1<<0);      //Limpiar cualquier interrupción de prioridad
  GPIO_PORTJ_IM_R |= (1<<1)|(1<<0);       //Desenmascarar interrupción

  // Activar interrupción en el registro NVIC y configurar prioridad en 3
  NVIC_PRI12_R = (3<<29);     //Interrupción de prioridad 3
  NVIC_EN1_R |= (1<<19);      //Activar bit de interrupción 51 (Puerto J)(bit19 de EN1)
}

void PuertoK7_Conf_RTC(){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R9; //Activa puerto K
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R9)==0){} //Espera a que puerto K este listo
	//Configurar puerto K bit 7 con PCTL = 5 (RTCCLK)
	GPIO_PORTK_DEN_R |= 0x80;
	GPIO_PORTK_DIR_R |= 0x80;
	GPIO_PORTK_AFSEL_R |= 0x80;
	GPIO_PORTK_PCTL_R |= 0x50000000;
	GPIO_PORTK_AMSEL_R |= 0x00;
}

void PuertoK_Conf(){
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R9; //Activa puerto K
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R9)==0){} //Espera a que puerto K este listo
  GPIO_PORTK_DEN_R |= 0x0F;
  GPIO_PORTK_DIR_R |= 0x0F;
  GPIO_PORTK_AFSEL_R |= 0x00;
  GPIO_PORTK_AMSEL_R |= 0x00;
}

void PuertoL_Conf(){
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10; //Activa puerto L
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R10)==0){} //Espera a que puerto L este listo
  GPIO_PORTL_DEN_R |= 0x0F;
  GPIO_PORTL_DIR_R |= 0x0F;
  GPIO_PORTL_AFSEL_R |= 0x00;
  GPIO_PORTL_AMSEL_R |= 0x00;
}

void PuertoL_Conf_QEI(){
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10; //Prendo el puerto L.
	while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R10)==0){} //Espero que el puerto este listo.
	
	GPIO_PORTL_DEN_R |= 0x06; //Configuro Pines PL1(PhA) y PL2(PhB) en modo digital.
	GPIO_PORTL_AFSEL_R |= 0x06; //Activo funcion alternativa para los pines PL1 Y PL2.
	GPIO_PORTL_PCTL_R &= 0xFFFFF00F; //Pongo en cero pines PL1 y PL2, y dejo como estaban los demas pines.
	GPIO_PORTL_PCTL_R |= 0x00000660; //Activo funcion alternativa de los Pines PL1(PhA) y PL2(PhB).
}
