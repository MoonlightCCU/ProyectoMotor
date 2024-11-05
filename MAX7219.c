#include "Max7219.h"

void MAX7219_Ini(void){
  SYSCTL_RCGCSSI_R |=0x01;							//Prende modulo 0 de SSI0	
  SYSCTL_RCGCGPIO_R |=0x01;							// prendo puerto A por que ahi estan los pines del modulo 0
  while((SYSCTL_PRGPIO_R&0x0001)==0){}	// Espere que prenda el puerto A

  GPIO_PORTA_AFSEL_R |=0x1C;						//Asigno funciones alternativas digitales a pin 2, 3, 4
  GPIO_PORTA_DEN_R |=0x1C;							//lo pongo como digital 
  GPIO_PORTA_PCTL_R =(GPIO_PORTA_PCTL_R&0xFFF000FF)+0x000FFF00; //asigno a pines 2, 3 y 4 funcion OSSI0
  GPIO_PORTA_AMSEL_R=0;									//Desactivo funcion analogica
  
  SSI0_CR1_R&=~SSI_CR1_SSE;						//desactiva la operacion del modulo QSSI0
  SSI0_CR1_R&=~SSI_CR1_MS;						//Maestro
  SSI0_CR1_R&=~SSI_CR1_MODE_M;				//modo Legacy SSI mode
  SSI0_CR1_R&=~SSI_CR1_FSSHLDFRM;  		//Hold SSInFss for the whole frame
    
  SSI0_CPSR_R=(SSI0_CPSR_R&~SSI_CPSR_CPSDVSR_M)+2;	//CPSDVSR=2
  SSI0_CR0_R=~(SSI_CR0_SCR_M|		//SCR=0. La velocidad es de 8 Mhz
                SSI_CR0_SPH|			//SPH=0
                SSI_CR0_SPO);		//SPO=0											
  SSI0_CR0_R=(SSI0_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;		//FRF=0  Freescale SPI Frame Format
  SSI0_CR0_R=(SSI0_CR0_R|SSI_CR0_DSS_M);		//DSS =0xF  16-bit data	
    
  SSI0_CR1_R|=SSI_CR1_SSE;			//activa la operacion del modulo QSSI0
}

void Max7219_Transmit(uint16_t dato){
	while ((SSI0_SR_R&SSI_SR_TNF)==0){}//Mientras el buffer de transmision este lleno, no hace nada
	SSI0_DR_R=dato; //Si el buffer de transmision esta vacio manda al max7219 el dato.
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
