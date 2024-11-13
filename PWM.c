/*
 * PWM.c
 *
 *  Created on: Mar, 2022
 *      Author: Carlos Canul
 */

#include "PWM.h"

void PWM0_Init(PWM_MODULE *PWM, uint8_t div, uint16_t freq){ //uint8_t dutyc){
  PWM->div = div;
  PWM->freq = freq;
  PWM->LOAD = 16000000/(div*freq);
  PWM->dutyc = 0; //[0:999] donde 0 = 0% del ciclo de trabajo y 999 = 100%
  /*
  if(dutyc == 0){
    PWM->dutyc = 0;
  }else {
    PWM->dutyc = ((dutyc*PWM->LOAD)/100) - 1;
    //Por ejemplo: Queremos un cliclo de trabajo del 50% ==> PWM->dutyc = ((50%*1000)/100)-1 = 499
  }
  //PWM->y_float = 0.0;
  */
  PWM0_PortF_Conf();
  PWM0_CONF(PWM);
}

/*
 *  Función para inicializar el PWM
 *  Recibe una direccion de la estructura PWM y crea un puntero para obtener los
 *  valores para configurar el PWM.
 */
void PWM0_CONF(PWM_MODULE *PWM){
	//Paso 1: Activar el reloj del PWM
	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0; //Enable and provide a clock to PWM module 0 in Run mode.
	
	/*
   * Configurar primero el puerto, después llamar la configuración del PWM
   * Una alternativa podría ser el añadir el inicio del PWM en otra función (PWM0_ENABLE_R)
   *
   * Paso 2, 3 y 4: Activar el reloj para el puerto a utilizar, en este caso el puerto F y
   * configurar la funcion alternativa.
   * Configurado en PWM0_Init()
   */

	//Paso 5: Configuración del PWM Clock (PWMCC). Divisor = 32, entonces (16MHz/32) = 500 KHz = 500000 Hz 
  if(PWM->div == 2){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_2);
  } else if (PWM->div == 4){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_4);
  } else if (PWM->div == 8){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_8);
  } else if (PWM->div == 16){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_16);
  } else if (PWM->div == 32){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_32);
  } else if (PWM->div == 64){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_64);
  } else {
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_32);
  }
  
	//Paso 6: Configuro PWM en countdown y configuro los generadores.
	PWM0_0_CTL_R |= 0x00000000;
	
	//Para el GeneradorB, Cuando Cont = Load, entonces PMW0GENB = HIGH y cuando Cont=CMPB, entonces PMW0GENB = LOW
	PWM0_0_GENB_R |= 0x00000C08; //Este es el generador que utilizo.
	
	//Paso 7: PWM0LOAD. 500Hz, entonces (500KHz/500Hz)=1000
	PWM0_0_LOAD_R = PWM->LOAD;

	//Paso 9: M0PWM1 = 0% (deafult) Duty Cycle
	PWM0_0_CMPB_R = PWM->dutyc;
	
	//Paso 10: Inicializo los Timers en PWM generador 0.
	PWM0_0_CTL_R |= 0x00000001;
	
	//Paso 11: Activo PWM salidas. En este solo configuro para que salga por PF1 y desactivo para PF0
	//Porque no utilizo el Generador A (PF0)
	PWM0_ENABLE_R |= 0x00000002;
}

//En esta funcion configuro el comparador B, para el GeneradorB(PF1). Esta
//funcion es la que llamo para modificar el valor del comparador B.
void PWM0_Update_GenB(float y){
	//Paso 9: M0PWM1 = y% Duty Cycle
  float yp = (1000*y)/130;
  if((uint16_t)yp == 0){
    PWM0_0_CMPB_R = 0;
  }else if((uint16_t)yp == 1000){
    PWM0_0_CMPB_R = 999;
  }else {
    PWM0_0_CMPB_R = (uint16_t)yp;
  }
}

void PWM0_PortF_Conf(){
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
