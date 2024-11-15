#include "Max7219.h"

void MAX7219_Init(MAX7219 *max){
  max->shutMode = 0x0C00;
  max->Nperacion = 0x0C01;
  max->Dcode = 0x09FF;
  max->Intensidad = 0x0A02;
  max->SCAN = 0x0B07;
  SPI0_PortA_Conf();
  SPI0_Config();
  MAX7219_Config(max);
}

void SPI0_Config(){
  SYSCTL_RCGCSSI_R |= 0x01; // Habilitar el módulo SSI0 para la comunicación SPI

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
}

void MAX7219_Transmit(uint16_t dato){
  // Esperar hasta que el buffer de transmisión esté vacío
  while ((SSI0_SR_R & SSI_SR_TNF) == 0) {}
  // Transmitir el dato al MAX7219 cuando el buffer esté vacío
  SSI0_DR_R = dato;
}

// Configuración inicial del MAX7219 para manejar los dígitos del display
void MAX7219_Config(MAX7219 *max){
  MAX7219_Transmit(max->Dcode); // Enviar configuración de no operación al MAX7219
  MAX7219_Transmit(max->Dcode);     // Configurar el MAX7219 para usar el decodificador interno
  MAX7219_Transmit(max->Intensidad); // Configurar la intensidad de brillo (5/32) según la hoja de datos
  MAX7219_Transmit(max->SCAN);      // Configurar el número de dígitos que se escanean en el display

  // Enviar datos para inicializar cada dígito en el display
  for(uint8_t i = 0; i < 8; i++){
    MAX7219_Transmit(0x0100 * (i+1));
  }
}

void MAX7219_VelocidadR(uint16_t velocidad){
  for (uint8_t i = 0; i < 3; i++){
    MAX7219_Transmit(0x040A);
    uint16_t valor_transmitir = velocidad % 10;
    MAX7219_Transmit (valor_transmitir + (0x0100 * (i+1)));
    velocidad = velocidad / 10;
  }
}

void MAX7219_VelocidadD(uint16_t velocidad){
  for (uint8_t i = 5; i < 8; i++){
    MAX7219_Transmit(0x050A);
    uint16_t valor_transmitir = velocidad % 10;
    MAX7219_Transmit (valor_transmitir + (0x0100 * (i+1)));
    velocidad = velocidad / 10;
  }
}


void REG_SPEED(uint16_t velocidad){
  for (uint8_t i = 0; i < 4; i++){
    //MAX7219_Transmit(0x050A);
    uint16_t valor_transmitir = velocidad % 10;
    MAX7219_Transmit (valor_transmitir + (0x0100 * (i+1)));
    velocidad = velocidad / 10;
  }
}

void SPI0_PortA_Conf(){
  SYSCTL_RCGCGPIO_R |= 0x01; // Habilitar el puerto A, donde están los pines del módulo SSI0
  while ((SYSCTL_PRGPIO_R & 0x0001) == 0) {} // Esperar hasta que el puerto A esté listo para configurarse

  GPIO_PORTA_AFSEL_R |= 0x1C; // Asignar funciones alternativas digitales a los pines PA2, PA3 y PA4
  GPIO_PORTA_DEN_R |= 0x1C;   // Habilitar el modo digital en los pines PA2, PA3 y PA4
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFF000FF) + 0x000FFF00; // Configurar PA2, PA3 y PA4 para la función SSI0
  GPIO_PORTA_AMSEL_R = 0; // Desactivar la función analógica en el puerto A
}
