#include "FPU.h"

void FPU_INIT(){
  /* Coprocessor Access Control (CPAC):
  *  The CPAC register specifies the access privileges for coprocessors.
  *  Type RW, reset 0x00000000.
  *  [21:20] CP10: CP10 Coprocessor Access Privilege. 0x3 Full Access
  *  [23:22] CP11: CP11 Coprocessor Access Privilege. 0x3 Full Access
  */
  NVIC_CPAC_R |= (NVIC_CPAC_CP11_FULL|NVIC_CPAC_CP10_FULL);

  /* Floating-Point Context Control (FPCC):
  *  The FPCC register sets or returns FPU control data. Type RW, reset 0xC0000000
  *  [31]ASPEN: Automatic State Preservation Enable. When set, enables the use of the
  *   FRACTV bit in the CONTROL register on execution of a floating-point instruction
  *   This results in automatic hardware state preservation and restoration, for 
  *   floating-point context, on exception entry and exit.
  *  [30]LSPEN: Lazy State Preservation Enable. When set, enables automatic lazy state
  *   preservation for floating-point context.
  *  NVIC_FPCC_R |= 0xC0000000; //default on reset. ASPEN = 1 y LSPEN = 1 
  */

  /* Floating-Point Context Address (FPCA):
  *  The FPCA register holds the location of the unpopulated floating-point register
  *  space allocated on an exception stack frame. Type RW, reset -
  *  [31:3] ADDRESS: The location of the unpopulated floating-point register space
  *   allocated on an exception stack frame.
  *  NVIC_FPCA_R = ?;
  */

  /* Floating-Point Default Status Control (FPDSC):
  *  The FPDSC register holds the default values for the Floating-Point Status Control
  *  (FPSC) register. Type RW, reset 0x00000000.
  *  [23:22] RMODE: RMODE bit Default. This bit holds the default value for the RMODE
  *   bit field in the FPSC register.
  *  [24] FZ: FZ bit Default. This bit holds the default value for the FZ bit in the
  *   FPSC register.
  *  [25] DN: DN bit Default. This bit holds the default value for the DN bit in the
  *   FPSC register.
  *  [26] AHP: AHP bit default. This bit holds the default value for the AHP bit in the
  *   FPSC register.
  *  NVIC_FPDSC_R = ?;
  */
}
