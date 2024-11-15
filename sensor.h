#include <stdint.h>
#include "tm4c1294ncpdt.h"

typedef struct {
  float ratio_reduct;
  uint16_t ppr;
  uint8_t clk;
  uint8_t VELDIV;
  uint8_t LOAD;
  uint8_t edges;
  uint32_t bigNumber1;
  uint32_t bigNumber2;
  uint32_t velocity;
  float RPM_val;
}QEI0_SPEED;

//Prototipo para la función de inicializacion el modulo
void Sensor_Init(QEI0_SPEED *, uint16_t, float);

//Prototipo para la función de configuración del modulo
void QEI0_Conf(void);

//Prototipo para la función para obtener la velocidad actual
void Sensor_Speed(QEI0_SPEED *);

void Sensor_QEI0(QEI0_SPEED *);

//Prototipo para la función de configuración del puerto L
void QEI0_PortL_Conf(void);

//void QEI_init(void);
//float medirvelocidadmotor (void);
