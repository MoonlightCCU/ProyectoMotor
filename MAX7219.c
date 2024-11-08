#include "Max7219.h"

void MAX7219_Ini(void){
  SYSCTL_RCGCSSI_R |= 0x01; // Habilitar el módulo SSI0 para la comunicación SPI
  SYSCTL_RCGCGPIO_R |= 0x01; // Habilitar el puerto A, donde están los pines del módulo SSI0
  while ((SYSCTL_PRGPIO_R & 0x0001) == 0) {} // Esperar hasta que el puerto A esté listo para configurarse

  GPIO_PORTA_AFSEL_R |= 0x1C; // Asignar funciones alternativas digitales a los pines PA2, PA3 y PA4
  GPIO_PORTA_DEN_R |= 0x1C;   // Habilitar el modo digital en los pines PA2, PA3 y PA4
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFF000FF) + 0x000FFF00; // Configurar PA2, PA3 y PA4 para la función SSI0
  GPIO_PORTA_AMSEL_R = 0; // Desactivar la función analógica en el puerto A

  SSI0_CR1_R &= ~SSI_CR1_SSE; // Desactivar la operación del módulo SSI0 mientras se configura
  SSI0_CR1_R &= ~SSI_CR1_MS; // Configurar como maestro
  SSI0_CR1_R &= ~SSI_CR1_MODE_M; // Configurar en modo "Legacy SSI mode"
  SSI0_CR1_R &= ~SSI_CR1_FSSHLDFRM; // Mantener el SSI0Fss en todo el marco de datos

  // Configuración de la velocidad de transmisión SPI
  SSI0_CPSR_R = (SSI0_CPSR_R & ~SSI_CPSR_CPSDVSR_M) + 2; // Establecer divisor de reloj en 2 para una velocidad de 8 MHz

  // Configuración del formato de comunicación SPI
  SSI0_CR0_R = ~(SSI_CR0_SCR_M | SSI_CR0_SPH | SSI_CR0_SPO); // Configurar velocidad de transmisión y polaridad
  SSI0_CR0_R = (SSI0_CR0_R & ~SSI_CR0_FRF_M) + SSI_CR0_FRF_MOTO; // Configurar en formato de marco Freescale SPI
  SSI0_CR0_R |= SSI_CR0_DSS_M; // Configurar para transmitir datos de 16 bits

  SSI0_CR1_R |= SSI_CR1_SSE; // Activar el módulo SSI0 para iniciar la operación

  max7219_config();
}

// Configuración inicial del MAX7219 para manejar los dígitos del display
void max7219_config(void){
  Max7219_Transmit(Nperacion); // Enviar configuración de no operación al MAX7219
  Max7219_Transmit(Dcode);     // Configurar el MAX7219 para usar el decodificador interno
  Max7219_Transmit(Intensidad); // Configurar la intensidad de brillo (5/32) según la hoja de datos
  Max7219_Transmit(SCAN);      // Configurar el número de dígitos que se escanean en el display

  // Enviar datos para inicializar cada dígito en el display
  Max7219_Transmit(0x0100); // Transmite numero 0 para el dígito 0
  Max7219_Transmit(0x0200); // Transmite numero 0 para el dígito 1
  Max7219_Transmit(0x0300); // Transmite numero 0 para el dígito 2
  Max7219_Transmit(0x0400); // Transmite numero 0 para el dígito 3
  Max7219_Transmit(0x0500); // Transmite numero 0 para el dígito 4
  Max7219_Transmit(0x0600); // Transmite numero 0 para el dígito 5
  Max7219_Transmit(0x0700); // Transmite numero 0 para el dígito 6
  Max7219_Transmit(0x0800); // Transmite numero 0 para el dígito 7
}

void Max7219_Transmit(uint16_t dato){
  // Esperar hasta que el buffer de transmisión esté vacío
  while ((SSI0_SR_R & SSI_SR_TNF) == 0) {}

  // Transmitir el dato al MAX7219 cuando el buffer esté vacío
  SSI0_DR_R = dato;
}

void velocidadreal(uint32_t velocidad){
	for (int i = 0; i < 3; i++){
		Max7219_Transmit(0x040A);
		uint32_t valor_transmitir = velocidad % 10;
		Max7219_Transmit (valor_transmitir + (0x0100 * (i+1)));
		velocidad = velocidad / 10;
	}
}

void velocidaddeseada(uint32_t velocidad){
	for (int i = 5; i < 8; i++){
		Max7219_Transmit(0x050A);
		uint32_t valor_transmitir = velocidad % 10;
		Max7219_Transmit (valor_transmitir + (0x0100 * (i+1)));
		velocidad = velocidad / 10;
	}
}
