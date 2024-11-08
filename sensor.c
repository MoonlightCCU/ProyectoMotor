#include "QEI.h"

/*
En este modulo se habilita el QEI0 de la tiva TM4C1294NCPDT, para lo cual se configuran los pines PL1 y PL2 como funciones alternativas y luego se les
asiga QEI, se activa el modo de captura de velocidad del QEI0 y se asigna un load de 15999999, para capturar el total de los pulsos del encoder en un 
segundo.
*/

// Inicializaci�n del m�dulo QEI (Quadrature Encoder Interface)
void QEI_init(void){
  // Habilitar el reloj para el m�dulo QEI0. Esto permite que el m�dulo QEI0 reciba un reloj para su operaci�n.
  SYSCTL_RCGCQEI_R |= SYSCTL_RCGCQEI_R0;

  // Habilitar el reloj para el puerto L, donde est�n conectados los pines del encoder.
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10;

  // Esperar hasta que el puerto L est� listo para ser configurado.
  while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R10) == 0) {};

  // Configurar los pines PL1 y PL2 para que usen funciones alternativas, ya que estos pines deben usarse para el QEI.
  GPIO_PORTL_AFSEL_R |= 0x06;  // El valor 0x06 habilita funciones alternativas en los bits 1 y 2 (PL1 y PL2).

  // Asignar la funci�n QEI a los pines PL1 y PL2 mediante el registro PCTL.
  GPIO_PORTL_PCTL_R = (GPIO_PORTL_PCTL_R & 0xFFFFF00F) | 0x00000660;

  // Habilitar el modo digital para los pines PL1 y PL2.
  GPIO_PORTL_DEN_R |= 0x06;

  // Asegurar que el m�dulo QEI0 est� listo antes de configurarlo.
  while ((SYSCTL_PRQEI_R & SYSCTL_PRQEI_R0) == 0) {}

  // Configurar el control del QEI:
  // Habilitar el filtro de se�al para evitar errores en la lectura y configurar el contador de filtro para suavizar las se�ales del encoder.
  QEI0_CTL_R |= QEI_CTL_FILTEN | QEI_CTL_FILTCNT_M;

  // Deshabilitar el modo de reset autom�tico en el QEI cuando se detecte el punto de referencia.
  QEI0_CTL_R &= ~QEI_CTL_RESMODE;

  // Habilitar el modo de captura, que permite registrar cambios en los pines PhA y PhB del encoder.
  QEI0_CTL_R |= QEI_CTL_CAPMODE;

  // Habilitar la captura de velocidad en el QEI0 para calcular las RPM.
  QEI0_CTL_R |= QEI_CTL_VELEN;

  // Configurar el registro de carga (LOAD) para establecer un periodo de muestreo de velocidad de 1 segundo.
  // Esto se basa en un reloj de 16 MHz, por lo que 16000000 - 1 equivale a un segundo de carga.
  QEI0_LOAD_R = 16000000 - 1;

  // Finalmente, habilitar el m�dulo QEI0.
  QEI0_CTL_R |= QEI_CTL_ENABLE;
}

// Funci�n para medir la velocidad del motor en RPM
float medirvelocidadmotor(void){
  // Leer el valor actual del registro de velocidad QEI0 (n�mero de pulsos en el periodo de velocidad).
  float speed = QEI0_SPEED_R;

  // Calcular las RPM usando la f�rmula: rpm = (pulsos / PPR) * 60.
  // Asumiendo que el PPR (Pulsos por revoluci�n) es 2240, de acuerdo con las especificaciones del encoder.
  float rpm = (speed / 2240) * 60;

  return rpm; // Retorna el valor calculado en RPM.
}

