/*
 * main.c
 *
 *  Created on: Oct, 2024
 *      Author: Carlos Canul
 *  Modified on: Oct, 2024
 *      By: Manuel Lucas
 */

#include "PWM.h"          //Modulo 1. PWM para el motor
#include "pvelocidad.h"   //Modulo 2. para poner velocidad
#include "Max7219.h"      //Modulo 3. para desplegar el valor actual y el fijado
#include "PID.h"          //Modulo 4. PID para controlar el motor
#include "sensor.h"       //Modulo 5. del sensor o modulo de cuadratura (QEI)
#include "FPU.h"          //Sirve para activar las operaciones de punto flotante
#include "SysTick.h"      //Sirve para el tiempo de muestreo

int main(void){
  //Activo las operaciones de punto flotante del microcontrolador
  FPU_INIT();

  //Creo estructura pid de tipo PID_Controller
  PID_Controller pid;
  //PID_Init(&pid,Kp,Ki,Kd)
  PID_Init(&pid, 1.0, 0.1, 0.01); // Example gains

  //Creo estructura pvelocidad de tipo poner_vel
  poner_vel pvelocidad;
  //Poner_Vel_Init(&pvelocidad, RPM_adj, RPM);
  Poner_Vel_Init(&pvelocidad, 5, 30.0);

  PWM_MODULE PWM;
  //PWM0_Init(&PWM, div, freq);
  PWM0_Init(&PWM, 32, 500);

  //Creo estructura sensor de tipo QEI0_SPEED
  QEI0_SPEED sensor;
  //Sensor_Init(&sensor, ppr, ratio_reduct);
  Sensor_Init(&sensor, 843, 75.0);

  //Time step para el PID
  float dt = 0.01;

  //Configuracion del Max7219
  MAX7219_Ini();

  //Transmito al MAX7219 la velocidad inicial del motor (pvelocidad.RPM)
  velocidaddeseada((uint16_t)pvelocidad.RPM);

  //Tiempo de muestreo dt, en este caso dt = 0.01 segundos
  SysTick_Conf(dt);

  while(1){
    //Mando por referencia la estructura pvelocidad y compruebo el estado del boton B0
    //para decidir si se cambia la velocidad de referencia
    Poner_Vel_Wait(&pvelocidad);

    Sensor_Speed(&sensor);
    velocidadreal((uint16_t)sensor.RPM_val);

    //Calculo el valor del PID pasandole por referencia la estructura pid, la velocidad
    //deseada, el valor de la velocidad actual y delta de t
    PID_Update(&pid, pvelocidad.RPM,sensor.RPM_val, dt);
    
    //Si la salida es la misma que la anterior se evita volver a cargar elmismo valor
    if(pid.cout_prev != pid.control_output){
      //Paso "control_output" al modulo PWM para ajustar la velocidad del motor
      PWM0_Update_GenB(pid.control_output);
      pid.cout_prev = pid.control_output;
    }

    SysTick_Init();
    while(NVIC_ST_CTRL_R != 0x00010001){
      //dt = 0.01s = 10ms
      //Espero que transcurra el tiempo dt para realizar los muestreos
    }
    //Detengo el SysTick y reinicio el contador en cero
    SysTick_Stop();
  }
}
