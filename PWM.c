/*
 * PWM.c
 *
 *  Created on: Mar, 2022
 *      Author: Carlos Canul
 */

#include "PWM.h"

//Función para inicializar el PWM
//Recibe dos valores de 16 bits, los cuales son x para PWM0 Generador A y y para PMW0 Generador B
void conf_Global_PWM0(uint16_t x, uint16_t y){
	//Paso 1: Activar el reloj del PWM
	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0; //Enable and provide a clock to PWM module 0 in Run mode.
	
	/*
    Configurar primero el puerto, después llamar la configuración del PWM
    Una alternativa podría ser el añadir el inicio del PWM en otra función (PWM0_ENABLE_R)

    Paso 2: Activar el reloj para el puerto a utilizar, en este caso el puerto F
	  En CONF_PORTS.c

	  Paso 3 y 4: Configurar funcion alternativa
	  En CONF_PORTS.c
  */
  PuertoF_Conf_PWM();

	//Paso 5: Configuración del PWM Clock (PWMCC). Divisor = 64, entonces (16MHz/64) = 250 KHz = 250000 Hz 
	PWM0_CC_R |= (PWM_CC_USEPWM | PWM_CC_PWMDIV_64); //PWM_CC_USEPWM para activar el reloj con divisor
	
	//Paso 6: Configuro PWM en countdown y configuro los generadores.
	PWM0_0_CTL_R |= 0x00000000;
	
	//Para el GeneradorA, Cuando Cont = Load, entonces PMW0GENA = Low y cuando Cont=CMPA, entonces PMW0GENA = HIGH
	PWM0_0_GENA_R |= 0x00000048; //No utilizo este generador porque esta conectado a un led de la Tiva C
	
	//Para el GeneradorB, Cuando Cont = Load, entonces PMW0GENB = Low y cuando Cont=CMPB, entonces PMW0GENB = HIGH
	PWM0_0_GENB_R |= 0x0000080C; //Este es el generador que utilizo.
	
	//Paso 7: PWM0LOAD. 50Hz, entonces (250KHz/50Hz)=5000
	PWM0_0_LOAD_R = 0x00001388;
	
	//Paso 8: M0PWM0 = 50% (default) Duty Cycle. Esta configurado al 50% desde el main()
	PWM0_0_CMPA_R =x; //No utilizo este generador
	
	//Paso 9: M0PWM1 = 50% (deafult) Duty Cycle. Esta configurado al 50% desde el main() y
	//desde ahi puedo ponerle el valor deseado.
	PWM0_0_CMPB_R =y;
	
	//Paso 10: Inicializo los Timers en PWM generador 0.
	PWM0_0_CTL_R |= 0x00000001;
	
	//Paso 11: Activo PWM salidas. En este solo configuro para que salga por PF1 y desactivo para PF0
	//Porque no utilizo el Generador A (PF0)
	PWM0_ENABLE_R |= 0x00000002;
}

//En esta funcion configuro el comparador A, para el GeneradorA(PF0), pero
//Como no lo utilizo, no es necesario.
void conf_PWM0_GenA(uint16_t x){
	//Paso 8: M0PWM0 = x% Duty Cycle
	PWM0_0_CMPA_R = x;
}

//En esta funcion configuro el comparador B, para el GeneradorB(PF1). Esta
//funcion es la que llamo para modificar el valor del comparador B.
void conf_PWM0_GenB(uint16_t y){
	//Paso 9: M0PWM1 = y% Duty Cycle
	PWM0_0_CMPB_R = y;
}
