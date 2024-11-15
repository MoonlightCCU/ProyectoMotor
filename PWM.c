/*
 * PWM.c
 *
 *  Created on: Mar, 2022
 *      Author: Carlos Canul
 */

#include "PWM.h"

/*
 *  Función para inicializar el PWM
 *  Recibe dos valores, uno de 8 bits y otro de 16 bits, los cuales son div para divisor del relojdel
 *  del sistema y freq para la frequencia deseada
 */
void conf_Global_PWM0(uint8_t div,uint16_t freq){
	//Paso 1: Activar el reloj del PWM
	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0; //Enable and provide a clock to PWM module 0 in Run mode.
	
	/*
   * Configurar primero el puerto, después llamar la configuración del PWM
   * Una alternativa podría ser el añadir el inicio del PWM en otra función (PWM0_ENABLE_R)
   *
   * Paso 2, 3 y 4: Activar el reloj para el puerto a utilizar, en este caso el puerto F y
   * configurar la funcion alternativa.
   */
  PuertoF_Conf_PWM();

	//Paso 5: Configuración del PWM Clock (PWMCC). Divisor = 32, entonces (16MHz/32) = 500 KHz = 500000 Hz 
  if(div == 2){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_2);
  } else if (div == 4){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_4);
  } else if (div == 8){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_8);
  } else if (div == 16){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_16);
  } else if (div == 32){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_32);
  } else if (div == 64){
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_64);
  } else {
    PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_32);
  }
  
	//Paso 6: Configuro PWM en countdown y configuro los generadores.
	PWM0_0_CTL_R |= 0x00000000;
	
	//Para el GeneradorB, Cuando Cont = Load, entonces PMW0GENB = Low y cuando Cont=CMPB, entonces PMW0GENB = HIGH
	PWM0_0_GENB_R |= 0x0000080C; //Este es el generador que utilizo.
	
	//Paso 7: PWM0LOAD. 500Hz, entonces (500KHz/500Hz)=1000
	PWM0_0_LOAD_R = PWM_LOAD(div,freq);

	//Paso 9: M0PWM1 = 50% (deafult) Duty Cycle
	PWM0_0_CMPB_R = PWM_DUTYC(50,div,freq);
	
	//Paso 10: Inicializo los Timers en PWM generador 0.
	PWM0_0_CTL_R |= 0x00000001;
	
	//Paso 11: Activo PWM salidas. En este solo configuro para que salga por PF1 y desactivo para PF0
	//Porque no utilizo el Generador A (PF0)
	PWM0_ENABLE_R |= 0x00000002;
}

// Función para obetener el valor de load
int PWM_LOAD(uint8_t div, uint16_t freq){
  uint16_t LOAD = 16000000/(div*freq);
  return LOAD;
}

// Función para obtener el valor del comparador dado el duty cycle (0% a 100%)
int PWM_DUTYC(uint8_t dutyc, uint8_t div, uint16_t freq){
  uint16_t LOAD = PWM_LOAD(div,freq);
  uint16_t yp = ((dutyc*LOAD)/100) - 1;
  return yp;
}

//En esta funcion configuro el comparador B, para el GeneradorB(PF1). Esta
//funcion es la que llamo para modificar el valor del comparador B.
void conf_PWM0_GenB(float y){
  float yp = (1000*y)/130;
	//Paso 9: M0PWM1 = y% Duty Cycle
	PWM0_0_CMPB_R = (uint16_t)yp;
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
