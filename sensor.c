#include "sensor.h"

/*
En este modulo se habilita el QEI0 de la tiva TM4C1294NCPDT, para lo cual se configuran los pines PL1 y PL2 como funciones alternativas y luego se les
asiga QEI, se activa el modo de captura de velocidad del QEI0 y se asigna un load de 15999999, para capturar el total de los pulsos del encoder en un 
segundo.

Indx0 -> PL3
PhA -> PL1 (Cable amarillo motor)
PhB -> PL2 (Cable verde motor)
*/

void Sensor_Init(QEI0_SPEED *sensor, uint16_t ppr, float ratio_reduct){
  sensor->ratio_reduct = ratio_reduct; //Posibles valores 75 y 44
  sensor->ppr = ppr;
  sensor->VELDIV = 1;     //Registro QEI0_CTL_R campo VELDIV = 0 ==> div = 1; VELDIV es una potencia de 2
  sensor->clk = 4;        //clock = 16MHz y LOAD = 4MHz ==> 16MHz/4M = 4 y 4MHz/4M = 1 (1/4 de reducción)
  sensor->LOAD = 1;       //RPM = (clk * VELDIV * SPEED * 60) / (LOAD * ppr * edges)
  sensor->edges = 4;      //CAPMODE = 1
  sensor->bigNumber1 = 0;
  sensor->bigNumber2 = 0;
  sensor->velocity = 0;
  sensor->RPM_val = 0.0;
  QEI0_PortL_Conf();
  QEI0_Conf();
}

// Inicialización del módulo QEI (Quadrature Encoder Interface)
void QEI0_Conf(){
	// Habilitar el reloj para el módulo QEI0. Esto permite que el módulo QEI0 reciba un reloj para su operación.
  SYSCTL_RCGCQEI_R |= SYSCTL_RCGCQEI_R0;

  // Asegurar que el módulo QEI0 esté listo antes de configurarlo.
  while ((SYSCTL_PRQEI_R & SYSCTL_PRQEI_R0) == 0) {};

  //0001 xx 1 0 0 0 0 000 1 0 1 0 0 0
  //0x12028 --> QEI0_CTL_R |= (QEI_CTL_CAPMODE | QEI_CTL_VELEN | QEI_CTL_VELDIV_1 | QEI_CTL_FILTEN | QEI_CTL_FILTCNT_1);
  //QEI0_CTL_R |= (QEI_CTL_CAPMODE | QEI_CTL_VELEN | QEI_CTL_VELDIV_1 | QEI_CTL_FILTEN | QEI_CTL_FILTCNT_1);

  // Configurar el control del QEI:
  // Habilitar el filtro de señal para evitar errores en la lectura y configurar el
  // contador de filtro para suavizar las señales del encoder.
  QEI0_CTL_R |= QEI_CTL_FILTEN | QEI_CTL_FILTCNT_1;

  // Configuro el divisor del reloj del QEI en 1
  QEI0_CTL_R |= QEI_CTL_VELDIV_1;

  // Habilitar la captura de velocidad en el QEI0 para calcular las RPM.
  QEI0_CTL_R |= QEI_CTL_VELEN;

  // Habilitar el modo de captura, que permite registrar cambios en los pines PhA y
  // PhB del encoder.
  QEI0_CTL_R |= QEI_CTL_CAPMODE;

  // Configurar el registro de carga (LOAD) para establecer un periodo de muestreo de
  // velocidad de 0.25 segundo. Esto se basa en un reloj de 16 MHz, por lo que:
  // (16000000*(1/4)) - 1 = 3999999 que equivale a un cuarto de segundo de carga.
  QEI0_LOAD_R = 4000000 - 1;

  // Finalmente, habilitar el módulo QEI0.
  QEI0_CTL_R |= QEI_CTL_ENABLE;
}

void Sensor_Speed(QEI0_SPEED *sensor){
  sensor->bigNumber1 = sensor->clk * sensor->VELDIV * QEI0_SPEED_R * 60;
  sensor->bigNumber2 = sensor->LOAD * sensor->ppr * sensor->edges;
  sensor->velocity = sensor->bigNumber1 / sensor->bigNumber2;
  sensor->RPM_val = sensor->velocity / sensor->ratio_reduct;
}

void Sensor_QEI0(QEI0_SPEED *sensor){
  sensor->ppr = QEI0_SPEED_R;
}

/*
//Se hace el calculo de las revoluciones por minuto del motor de acuerdo a las pulsaciones que se dan en un minuto
float medirvelocidadmotor (void){
  // Leer el valor actual del registro de velocidad QEI0 (número de pulsos en el periodo de velocidad).
  uint32_t speed = QEI0_SPEED_R;

  // Calcular las RPM usando la fórmula: rpm = (pulsos / PPR) * 60.
  // Asumiendo que el PPR (Pulsos por revolución) es 2240, de acuerdo con las especificaciones del encoder.
  uint32_t rpm = (speed / 110) * 6;
  //rpm = rpm / 10;
  return rpm; // Retorna el valor calculado en RPM.
}

void medvel1(int velocidad){
	// Leer el valor actual del registro de velocidad QEI0 (número de pulsos en el periodo de velocidad).
  uint32_t speed = QEI0_SPEED_R;

  // Calcular las RPM usando la fórmula: rpm = (pulsos / PPR) * 60.
  // De acuerdo con las especificaciones del encoder PPR = 11 y la relación con del motor con el motorreductor es de 1/78.
  // Entonces el PPR queda como 858 
  uint32_t rpm = (speed / 858) * 60;

  velocidad = QEI0_SPEED_R;
}
*/

void QEI0_PortL_Conf(){
  // Habilitar el reloj para el puerto L, donde están conectados los pines del encoder.
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10;

  // Esperar hasta que el puerto L esté listo para ser configurado.
  while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R10) == 0) {};

  // Configurar los pines PL1 y PL2 para que usen funciones alternativas, ya que estos pines deben usarse para el QEI.
  GPIO_PORTL_AFSEL_R |= 0x06;  // El valor 0x06 habilita funciones alternativas en los bits 1 y 2 (PL1 y PL2).

  //Se asigna la función QEI a los pines PL1 y PL2.
  GPIO_PORTL_PCTL_R = (GPIO_PORTL_PCTL_R & 0xFFFFF00F) | 0x00000660;

  // Habilitar el modo digital para los pines PL1 y PL2.
  GPIO_PORTL_DEN_R |= 0x06;
}
