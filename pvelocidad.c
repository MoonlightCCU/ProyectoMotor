/*
 * pvelocidad.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#include "pvelocidad.h"
#include "Max7219.h"

//Funcion para inicializar los valores del modulo y de los puertos a utilizar
void Poner_Vel_Init(poner_vel *pvelocidad, uint8_t RPM_adj, float RPM){
  pvelocidad->RPM_min = 0;
  pvelocidad->RPM_max = 130;
  pvelocidad->RPM_adj = RPM_adj;
  pvelocidad->RPM_prev = 0.0;
  pvelocidad->RPM = RPM;
  pvelocidad->vel = 0;
  pvelocidad->SWST = 0;
  PuertoB_Conf();
  PuertoJ_Conf();
}

//Funcion para sensar la pulsacion del boton B0, si se detecta pulsacion
//Se procede a entrar al menu para fijar la velocidad deseada.
void Poner_Vel_Wait(poner_vel *pvelocidad){
	if((GPIO_PORTB_DATA_R & 0x01) == 0) {      //Detecta si el botón en PortB fue presionado
		while((GPIO_PORTB_DATA_R & 0x01) == 0);  //Espera a que se suelte el botón ?? Tal vez haya que comentar esto
		pvelocidad->vel = 1;                     //Activa la señal para entrar a `Poner_Vel_Update`
	}

	if(pvelocidad->vel == 1) {
		Poner_Vel_Update(pvelocidad); //Llama a 'Poner_Vel_Update'
		pvelocidad->vel = 0;  //Reinicia la señal de velocidad para volver a esperar otra pulsación
	}
}

//Funcion para cambiar o fijar la velocidad deseada
void Poner_Vel_Update(poner_vel *pvelocidad){
  do{
    //Leo el estado del boton
    pvelocidad->SWST = GPIO_PORTJ_DATA_R;

    //If para disminuir la velocidad del motor
    //Si PJ = 0x01 (esta pulsado PJ1), disminuyo los RPM segun el valor en RPM_adj en cada pulsación
    if(pvelocidad->SWST == 0x01) {
      if((uint8_t)pvelocidad->RPM == pvelocidad->RPM_min){
        //no hacer nada
      }else{
        pvelocidad->RPM -= pvelocidad->RPM_adj; //Decrementar los rpm segun RPM_adj
        //Si el valor de rpm es menor o igual a 0, entonces lo hago cero para apagar el motor
        //pero si no es menor disminuyo en 5.
        if((int)pvelocidad->RPM < pvelocidad->RPM_min){
          pvelocidad->RPM = pvelocidad->RPM_min;	//Apago el motor
        }
        MAX7219_VelocidadD((uint16_t)pvelocidad->RPM); //TRANSMITO AL MAX7219

        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while(GPIO_PORTJ_DATA_R == 0x01){} // Esperar hasta soltar el botón
      }
    }

    //If para aumentar la velocidad del motor
    //Si PJ = 0x02 (esta pulsado PJ0), aumento los RPM segun el valor en RPM_adj en cada pulsación
    if(pvelocidad->SWST == 0x02) {
      if ((uint8_t)pvelocidad->RPM == pvelocidad->RPM_max){
        //no hacer nada
      }else{
        pvelocidad->RPM += pvelocidad->RPM_adj; //Incrementar los rpm segun RPM_adj
        //Si el valor de rpm sobrepasa los 130 rpm o es igual, fijo el valor maximo de rpm
        if((int)pvelocidad->RPM > pvelocidad->RPM_max){
          pvelocidad->RPM = pvelocidad->RPM_max;  //Mantengo al 100% la velocidad del motor
        }
        MAX7219_VelocidadD((uint16_t)pvelocidad->RPM); //TRANSMITO AL MAX7219

        //Mientras siga pulsado el boton, no hago nada.
        //Esto es para evitar que se siga ejecutando el if()
        while(GPIO_PORTJ_DATA_R == 0x02){} //Esperar hasta soltar el botón
      }
    }

    // Condición de salida si se detecta una nueva pulsación en el botón de PortB
    if((GPIO_PORTB_DATA_R & 0x01) == 0) {
      while((GPIO_PORTB_DATA_R & 0x01) == 0){}  //Espera a que el botón de PortB se suelte
      break;                                   //Sale del do-while
    }
  }while(1);
}

//Configuración del puerto B para el boton externo en PB0
void PuertoB_Conf(){
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;          //Activa puerto B
  while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1)==0){}  //Espera a que puerto B este listo
  GPIO_PORTB_DIR_R = 0x00;      //Pin 0 como entrada PB0
  GPIO_PORTB_AFSEL_R &= 0x00;   //Sin función alternativa
  GPIO_PORTB_DEN_R |= 0x01;     //GPIO DIGITAL
  GPIO_PORTB_AMSEL_R &= 0x00;   //Ninguna función analogica
  GPIO_PORTB_PCTL_R &= 0x00;    //Ninguna función especial a los pines.
  GPIO_PORTB_PUR_R |= 0x01;     //Activo resistencia pull-up
}

//Configuración del puerto J para el los botones de la Tiva 
void PuertoJ_Conf(){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R8;         //Activa puerto J
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R8)==0){} //Espera a que puerto J este listo
	GPIO_PORTJ_DIR_R = 0x00;      //Pin 0 y 1 como entrada, PJ0 y PJ1
	GPIO_PORTJ_AFSEL_R = 0x00;    //Sin función alternativa
	GPIO_PORTJ_DEN_R |= 0x03;     //GPIO DIGITAL
	GPIO_PORTJ_AMSEL_R &= 0x00;   //Ninguna función analogica
	GPIO_PORTJ_PCTL_R &= 0x00;    //Ninguna función especial a los pines.
	GPIO_PORTJ_PUR_R |= 0x03;     //Activo resistencia pull-up
}
