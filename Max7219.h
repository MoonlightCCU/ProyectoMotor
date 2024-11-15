#ifndef MAX7219_SPI0
#define MAX7219_SPI0

#include <stdint.h>
#include "tm4c1294ncpdt.h"

//max7219 pin 1 VCC-->TIVA C 5.00
//max7219 pin 2 GND -->TIVA C GND
//max7219 pin 3 DIN -->TIVA C PA4  SSI0XDAT0 
//max7219 pin 4 /CS -->TIVA C PA3  SSI0Fss 
//max7219 pin 5 CLK -->TIVA C PA2  SSI0Clk 
//max7219 pin x DOUT --> No se usa


typedef struct {
  uint8_t a;          // Ganancia Proporcional
  uint8_t b;          // Ganancia Integral
  uint16_t shutMode;
  uint16_t Nperacion;
  uint16_t Dcode;
  uint16_t Intensidad;
  uint16_t SCAN;
  uint16_t sep;          // Ganancia Derivativa
  uint16_t valor_transmitir;  // Error Previo
}MAX7219;

//Prototipo de función que sirve para inicializar los valores del PID
void MAX7219_Init(MAX7219 *);

//Prototipo de función que sirve para calcular el PID
void SPI0_Config();

void MAX7219_Config(MAX7219 *);

void MAX7219_Speed(MAX7219 *, uint16_t, uint8_t);

void REG_SPEED(MAX7219 *, uint16_t);

void MAX7219_Transmit(uint16_t);

void SPI0_PortA_Conf(void);

//void velocidadreal(MAX7219 *);
//void velocidaddeseada(MAX7219 *);

#endif
