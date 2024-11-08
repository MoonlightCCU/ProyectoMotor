/*
 * pvelocidad.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#include "pvelocidad.h"

//uint8_t RPM_min = 0;			//RPM minimo
//uint8_t RPM_max = 130;		//RPM maximo
//uint8_t RPM_adj = 5; 		//Incremento o Decremento del RPM
//float speed = 50.0; 		//Velocidad inicial
//volatile uint8_t vel = 0;
//volatile uint32_t SWST = 0;
void Poner_Vel_Init(poner_vel *pvelocidad, uint8_t RPM_min, uint8_t RPM_max, uint8_t RPM_adj, float RPM, volatile uint8_t vel, volatile uint32_t SWST){
  pvelocidad->RPM_min = RPM_min;
  pvelocidad->RPM_max = RPM_max;
  pvelocidad->RPM_adj = RPM_adj;
  pvelocidad->RPM = RPM;
  pvelocidad->vel = vel;
  pvelocidad->SWST = SWST;
  PuertoB_Conf();
  PuertoJ_Conf();
}

void Poner_Vel_Wait(poner_vel *pvelocidad){
	if((GPIO_PORTB_DATA_R & 0x01) == 0) {  		 //Detecta si el botón en PortB fue presionado
		while((GPIO_PORTB_DATA_R & 0x01) == 0);  //Espera a que se suelte el botón ?? Tal vez haya que comentar esto
		pvelocidad->vel = 1;  														 	 //Activa la señal para entrar a `poner_velocidad`
	}

	if(pvelocidad->vel == 1) {
		Poner_Vel_Update(pvelocidad);	//Llama a 'poner_velocidad'
		pvelocidad->vel = 0;  //Reinicia la señal de velocidad para volver a esperar otra pulsación
	}
}

void Poner_Vel_Update(poner_vel *pvelocidad){
  do{
    //Mientras el boton siga pulsado no hacer nada, hasta que se suelte
    //Leo el estado del boton
    pvelocidad->SWST = GPIO_PORTJ_DATA_R;

    //If para disminuir la velocidad del motor
    //Si PJ0 = 0x01 (esta pulsado), disminuyo los RPM segun el valor en RPM_adj en cada pulsación
    if(pvelocidad->SWST == 0x01) {
      if(pvelocidad->RPM <= pvelocidad->RPM_min){
        //no hacer nada
      }else{
        pvelocidad->RPM -= pvelocidad->RPM_adj;	//Decrementar los rpm segun RPM_adj
        //Si el valor de rpm es menor o igual a 0, entonces lo hago cero para apagar el motor
        //pero si no es menor disminuyo en 5%.
        if(pvelocidad->RPM <= pvelocidad->RPM_adj){
          pvelocidad->RPM = pvelocidad->RPM_min;	//Apago el motor
        }
        velocidaddeseada((uint16_t)pvelocidad->RPM); //TRANSMITO AL MAX7219
        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while (GPIO_PORTJ_DATA_R == 0x01) {} // Esperar hasta soltar el botón
      }
    }

    //If para aumentar la velocidad del motor
    //Si PJ1 = 0x02 (esta pulsado), aumento los RPM segun el valor en RPM_adj en cada pulsación
    if(pvelocidad->SWST == 0x02) {
      if (pvelocidad->RPM >= pvelocidad->RPM_max){
        //no hacer nada
      }else{
        pvelocidad->RPM += pvelocidad->RPM_adj;	//Incrementar los rpm segun RPM_adj
        //Si el valor de rpm sobrepasa los 130 rpm, el valor maximo de rpm
        if(pvelocidad->RPM >= pvelocidad->RPM_max){
          pvelocidad->RPM = pvelocidad->RPM_max;	//Mantengo al 100% la velocidad del motor
        }
        velocidaddeseada((uint16_t)pvelocidad->RPM);	//TRANSMITO AL MAX7219
        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while (GPIO_PORTJ_DATA_R == 0x02) {} //Esperar hasta soltar el botón
      }
    }

    // Condición de salida si se detecta una nueva pulsación en el botón de PortB
    if((GPIO_PORTB_DATA_R & 0x01) == 0) {
      while((GPIO_PORTB_DATA_R & 0x01) == 0);  //Espera a que el botón de PortB se suelte
      break;  																 //Sale del do-while
    }
  }while(1);
}

/*
float poner_velocidad(float rpm, uint8_t minRPM, uint8_t maxRPM, uint8_t adjRPM){
  do{
    //Mientras el boton siga pulsado no hacer nada, hasta que se suelte
    //Leo el estado del boton
    SWST = GPIO_PORTJ_DATA_R;

    //If para disminuir la velocidad del motor
    //Si PJ0 = 0x01 (esta pulsado), disminuyo los RPM segun el valor en RPM_adj en cada pulsación
    if(SWST == 0x01) {
      if(rpm <= minRPM){
        //no hacer nada
      }else{
        rpm -= adjRPM;	//Decrementar los rpm segun RPM_adj
        //Si el valor de rpm es menor o igual a 0, entonces lo hago cero para apagar el motor
        //pero si no es menor disminuyo en 5%.
        if(rpm <= adjRPM){
          rpm = minRPM;	//Apago el motor
        }
        velocidaddeseada((uint16_t)rpm); //TRANSMITO AL MAX7219
        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while (GPIO_PORTJ_DATA_R == 0x01) {} // Esperar hasta soltar el botón
      }
    }

    //If para aumentar la velocidad del motor
    //Si PJ1 = 0x02 (esta pulsado), aumento los RPM segun el valor en RPM_adj en cada pulsación
    if(SWST == 0x02) {
      if (rpm >= maxRPM){
        //no hacer nada
      }else{
        rpm += adjRPM;	//Incrementar los rpm segun RPM_adj
        //Si el valor de rpm sobrepasa los 130 rpm, el valor maximo de rpm
        if(rpm >= maxRPM){
          rpm = maxRPM;	//Mantengo al 100% la velocidad del motor
        }
        velocidaddeseada((uint16_t)rpm);	//TRANSMITO AL MAX7219
        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while (GPIO_PORTJ_DATA_R == 0x02) {} //Esperar hasta soltar el botón
      }
    }

    // Condición de salida si se detecta una nueva pulsación en el botón de PortB
    if((GPIO_PORTB_DATA_R & 0x01) == 0) {
      while((GPIO_PORTB_DATA_R & 0x01) == 0);  //Espera a que el botón de PortB se suelte
      break;  																 //Sale del do-while
    }
  }while(1);

	return rpm;	//Conserva el valor actual en el MAX7219
}
*/

//Configuración del puerto B para el boton externo en PB0
void PuertoB_Conf(void){
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;  			 //Activa puerto B
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1)==0){} //Espera a que puerto B este listo
  GPIO_PORTB_DIR_R 	  = 0x00;   //Pin 0 como entrada PB0
  GPIO_PORTB_AFSEL_R &= 0x00;   //Sin función alternativa	
  GPIO_PORTB_DEN_R 	 |= 0x01;   //GPIO DIGITAL
  GPIO_PORTB_AMSEL_R &= 0x00; 	//Ninguna función analogica
  GPIO_PORTB_PCTL_R  &= 0x00;   //Ninguna función especial a los pines.
  GPIO_PORTB_PUR_R 	 |= 0x01;   //Activo resistencia pull-up
}

//Configuración del puerto J para el los botones de la Tiva 
void PuertoJ_Conf(void){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R8; 				 //Activa puerto J
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R8)==0){} //Espera a que puerto J este listo
	GPIO_PORTJ_DIR_R 		= 0x00; 	//Pin 0 y 1 como entrada, PJ0 y PJ1
	GPIO_PORTJ_AFSEL_R 	= 0X00; 	//Sin función alternativa
	GPIO_PORTJ_DEN_R 	 |= 0X03; 	//GPIO DIGITAL
	GPIO_PORTJ_AMSEL_R &= 0X00; 	//Ninguna función analogica
	GPIO_PORTJ_PCTL_R  &= 0X00; 	//Ninguna función especial a los pines.
	GPIO_PORTJ_PUR_R 	 |= 0x03; 	//Activo resistencia pull-up
}
