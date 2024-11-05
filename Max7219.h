#include <stdint.h>
#include "tm4c1294ncpdt.h"

#define shutMode	  0x0C00
#define Nperacion		0x0C01
#define Dcode				0x09FF
#define Intensidad	0x0A02
#define SCAN				0x0B07
//#define Test				0x0F01

void Max7219_Transmit(uint16_t dato);
void velocidadreal(uint32_t velocidad);
void velocidaddeseada(uint32_t velocidad);
void MAX7219_Ini(void);
