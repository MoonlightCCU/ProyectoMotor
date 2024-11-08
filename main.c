/*
 * main.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#include "CONF_PORTS.h"
#include "PWM.h"
#include "pvelocidad.h"
#include "Max7219.h"
#include "PID.h"
#include "FPU.h"
#include "SysTick.h"
#include "QEI.h"

//max7219 pin 1 VCC-->TIVA C 5.00
//max7219 pin 2 GND -->TIVA C GND
//max7219 pin 3 DIN -->TIVA C PA4  SSI0XDAT0 
//max7219 pin 4 /CS -->TIVA C PA3  SSI0Fss 
//max7219 pin 5 CLK -->TIVA C PA2  SSI0Clk 
//max7219 pin x DOUT --> No se usa

int main(void){
  //Activo las operaciones de punto flotante del microcontrolador
  FPU_INIT();

  PID_Controller pid;
  //PID_Init(&pid,Kp,Ki,Kd)
  PID_Init(&pid, 1.0, 0.1, 0.01); // Example gains
  
  poner_vel pvelocidad;
  //Poner_Vel_Init(&pvelocidad,RPM_min,RPM_max,RPM_adj,RPM,vel,SWST);
  Poner_Vel_Init(&pvelocidad, 0, 130, 5, 30.0, 0, 0);

  float dt = 0.01; // Time step

	PuertoB_Conf();
	PuertoJ_Conf();
	
	MAX7219_Ini();
	max7219_config();
  
  //PWM_Conf_Global(div,500);
  conf_Global_PWM0(32,500);

  //Transmito al MAX7219 la velocidad inicial del motor, el cual es 0
	velocidaddeseada((uint16_t)pvelocidad.RPM);
  
  //Tiempo de muestreo dt, en este caso dt = 0.01 segundos
  SysTick_Conf(dt);

	while(1){
    Poner_Vel_Wait(&pvelocidad);
    float setpoint = pvelocidad.RPM;
    float measured_value = medirvelocidadmotor(); // Implement this function to read your sensor
    float control_output = PID_Update(&pid, setpoint, measured_value, dt);
    conf_PWM0_GenB(control_output); // Implement this function to set PWM output
    SysTick_Init();
    while(NVIC_ST_CTRL_R != 0x00010001){
      //dt = 0.01s = 10ms
    }
    SysTick_Stop();
  }
}
