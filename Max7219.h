#include <stdint.h>
#include "tm4c1294ncpdt.h"

//max7219 pin 1 VCC-->TIVA C 5.00
//max7219 pin 2 GND -->TIVA C GND
//max7219 pin 3 DIN -->TIVA C PA4  SSI0XDAT0 
//max7219 pin 4 /CS -->TIVA C PA3  SSI0Fss 
//max7219 pin 5 CLK -->TIVA C PA2  SSI0Clk 
//max7219 pin x DOUT --> No se usa

#define shutMode    0x0C00
#define Nperacion   0x0C01
#define Dcode       0x09FF
#define Intensidad  0x0A02
#define SCAN        0x0B07
//#define Test      0x0F01

void Max7219_Transmit(uint16_t dato);
void velocidadreal(uint16_t velocidad);
void velocidaddeseada(uint16_t velocidad);
void MAX7219_Ini(void);
void max7219_config(void);
