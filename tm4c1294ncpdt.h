//*****************************************************************************
//
// tm4c1294ncpdt.h - TM4C1294NCPDT Register Definitions
//
// Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// This is part of revision 2.1.0.12573 of the Tiva Firmware Development Package.
// Edited by Daniel Valvano, May 8, 2014 so GPIO ports use the same names as
// TM4C123 LaunchPad, but access the GPIO on AHB
// For example port A on  
//   the header for TM4C123            #define GPIO_PORTA_DATA_R      (*((volatile uint32_t *)0x400043FC)
//   TI's standard header for TM4C1294 #define GPIO_PORTA_AHB_DATA_R  (*((volatile uint32_t *)0x400583FC))
//   this header for TM4C1294          #define GPIO_PORTA_DATA_R      (*((volatile uint32_t *)0x400583FC))
// Only GPIO definitions changed. ALl other definitions are identical
//*****************************************************************************

#ifndef __TM4C1294NCPDT_H__
#define __TM4C1294NCPDT_H__


//*****************************************************************************
//
// SSI registers (SSI0)
//
//*****************************************************************************
#define SSI0_CR0_R              (*((volatile uint32_t *)0x40008000))
#define SSI0_CR1_R              (*((volatile uint32_t *)0x40008004))
#define SSI0_DR_R               (*((volatile uint32_t *)0x40008008))
#define SSI0_SR_R               (*((volatile uint32_t *)0x4000800C))
#define SSI0_CPSR_R             (*((volatile uint32_t *)0x40008010))

//*****************************************************************************
//
// PWM registers (PWM0)
//
//*****************************************************************************
#define PWM0_CTL_R              (*((volatile uint32_t *)0x40028000))
#define PWM0_ENABLE_R           (*((volatile uint32_t *)0x40028008))
#define PWM0_0_CTL_R            (*((volatile uint32_t *)0x40028040))
#define PWM0_0_LOAD_R           (*((volatile uint32_t *)0x40028050))
#define PWM0_0_CMPB_R           (*((volatile uint32_t *)0x4002805C))
#define PWM0_0_GENB_R           (*((volatile uint32_t *)0x40028064))
#define PWM0_CC_R               (*((volatile uint32_t *)0x40028FC8))

//*****************************************************************************
//
// QEI registers (QEI0)
//
//*****************************************************************************
#define QEI0_CTL_R              (*((volatile uint32_t *)0x4002C000))
#define QEI0_LOAD_R             (*((volatile uint32_t *)0x4002C010))
#define QEI0_SPEED_R            (*((volatile uint32_t *)0x4002C01C))

//*****************************************************************************
//
// GPIO registers (PORTA AHB)
//
//*****************************************************************************
#define GPIO_PORTA_DATA_R       (*((volatile uint32_t *)0x400583FC))
#define GPIO_PORTA_DIR_R        (*((volatile uint32_t *)0x40058400))
#define GPIO_PORTA_AFSEL_R      (*((volatile uint32_t *)0x40058420))
#define GPIO_PORTA_DEN_R        (*((volatile uint32_t *)0x4005851C))
#define GPIO_PORTA_AMSEL_R      (*((volatile uint32_t *)0x40058528))
#define GPIO_PORTA_PCTL_R       (*((volatile uint32_t *)0x4005852C))

//*****************************************************************************
//
// GPIO registers (PORTB AHB)
//
//*****************************************************************************
#define GPIO_PORTB_DATA_BITS_R  ((volatile uint32_t *)0x40059000)
#define GPIO_PORTB_DATA_R       (*((volatile uint32_t *)0x400593FC))
#define GPIO_PORTB_DIR_R        (*((volatile uint32_t *)0x40059400))
#define GPIO_PORTB_AFSEL_R      (*((volatile uint32_t *)0x40059420))
#define GPIO_PORTB_PUR_R        (*((volatile uint32_t *)0x40059510))
#define GPIO_PORTB_DEN_R        (*((volatile uint32_t *)0x4005951C))
#define GPIO_PORTB_AMSEL_R      (*((volatile uint32_t *)0x40059528))
#define GPIO_PORTB_PCTL_R       (*((volatile uint32_t *)0x4005952C))

//*****************************************************************************
//
// GPIO registers (PORTF AHB)
//
//*****************************************************************************
#define GPIO_PORTF_DATA_BITS_R  ((volatile uint32_t *)0x4005D000)
#define GPIO_PORTF_DATA_R       (*((volatile uint32_t *)0x4005D3FC))
#define GPIO_PORTF_DIR_R        (*((volatile uint32_t *)0x4005D400))
#define GPIO_PORTF_AFSEL_R      (*((volatile uint32_t *)0x4005D420))
#define GPIO_PORTF_DEN_R        (*((volatile uint32_t *)0x4005D51C))
#define GPIO_PORTF_AMSEL_R      (*((volatile uint32_t *)0x4005D528))
#define GPIO_PORTF_PCTL_R       (*((volatile uint32_t *)0x4005D52C))

//*****************************************************************************
//
// GPIO registers (PORTJ AHB)
//
//*****************************************************************************
#define GPIO_PORTJ_DATA_BITS_R  ((volatile uint32_t *)0x40060000)
#define GPIO_PORTJ_DATA_R       (*((volatile uint32_t *)0x400603FC))
#define GPIO_PORTJ_DIR_R        (*((volatile uint32_t *)0x40060400))
#define GPIO_PORTJ_AFSEL_R      (*((volatile uint32_t *)0x40060420))
#define GPIO_PORTJ_PUR_R        (*((volatile uint32_t *)0x40060510))
#define GPIO_PORTJ_DEN_R        (*((volatile uint32_t *)0x4006051C))
#define GPIO_PORTJ_AMSEL_R      (*((volatile uint32_t *)0x40060528))
#define GPIO_PORTJ_PCTL_R       (*((volatile uint32_t *)0x4006052C))

//*****************************************************************************
//
// GPIO registers (PORTL)
//
//*****************************************************************************
#define GPIO_PORTL_DATA_BITS_R  ((volatile uint32_t *)0x40062000)
#define GPIO_PORTL_DATA_R       (*((volatile uint32_t *)0x400623FC))
#define GPIO_PORTL_AFSEL_R      (*((volatile uint32_t *)0x40062420))
#define GPIO_PORTL_DEN_R        (*((volatile uint32_t *)0x4006251C))
#define GPIO_PORTL_PCTL_R       (*((volatile uint32_t *)0x4006252C))

//*****************************************************************************
//
// System Control registers (SYSCTL)
//
//*****************************************************************************
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_RCGCSSI_R        (*((volatile uint32_t *)0x400FE61C))
#define SYSCTL_RCGCPWM_R        (*((volatile uint32_t *)0x400FE640))
#define SYSCTL_RCGCQEI_R        (*((volatile uint32_t *)0x400FE644))
#define SYSCTL_PRGPIO_R         (*((volatile uint32_t *)0x400FEA08))
#define SYSCTL_PRQEI_R          (*((volatile uint32_t *)0x400FEA44))

//*****************************************************************************
//
// NVIC registers (NVIC)
//
//*****************************************************************************
#define NVIC_ACTLR_R            (*((volatile uint32_t *)0xE000E008))
#define NVIC_ST_CTRL_R          (*((volatile uint32_t *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile uint32_t *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile uint32_t *)0xE000E018))
#define NVIC_CPAC_R             (*((volatile uint32_t *)0xE000ED88))

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR0 register.
//
//*****************************************************************************
#define SSI_CR0_SCR_M           0x0000FF00  // SSI Serial Clock Rate
#define SSI_CR0_SPH             0x00000080  // SSI Serial Clock Phase
#define SSI_CR0_SPO             0x00000040  // SSI Serial Clock Polarity
#define SSI_CR0_FRF_M           0x00000030  // SSI Frame Format Select
#define SSI_CR0_FRF_MOTO        0x00000000  // Freescale SPI Frame Format
#define SSI_CR0_FRF_TI          0x00000010  // Synchronous Serial Frame Format
#define SSI_CR0_DSS_M           0x0000000F  // SSI Data Size Select
#define SSI_CR0_DSS_4           0x00000003  // 4-bit data
#define SSI_CR0_DSS_5           0x00000004  // 5-bit data
#define SSI_CR0_DSS_6           0x00000005  // 6-bit data
#define SSI_CR0_DSS_7           0x00000006  // 7-bit data
#define SSI_CR0_DSS_8           0x00000007  // 8-bit data
#define SSI_CR0_DSS_9           0x00000008  // 9-bit data
#define SSI_CR0_DSS_10          0x00000009  // 10-bit data
#define SSI_CR0_DSS_11          0x0000000A  // 11-bit data
#define SSI_CR0_DSS_12          0x0000000B  // 12-bit data
#define SSI_CR0_DSS_13          0x0000000C  // 13-bit data
#define SSI_CR0_DSS_14          0x0000000D  // 14-bit data
#define SSI_CR0_DSS_15          0x0000000E  // 15-bit data
#define SSI_CR0_DSS_16          0x0000000F  // 16-bit data
#define SSI_CR0_SCR_S           8

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR1 register.
//
//*****************************************************************************
#define SSI_CR1_EOM             0x00000800  // Stop Frame (End of Message)
#define SSI_CR1_FSSHLDFRM       0x00000400  // FSS Hold Frame
#define SSI_CR1_HSCLKEN         0x00000200  // High Speed Clock Enable
#define SSI_CR1_DIR             0x00000100  // SSI Direction of Operation
#define SSI_CR1_MODE_M          0x000000C0  // SSI Mode
#define SSI_CR1_EOT             0x00000010  // End of Transmission
#define SSI_CR1_MS              0x00000004  // SSI Master/Slave Select
#define SSI_CR1_SSE             0x00000002  // SSI Synchronous Serial Port
                                            // Enable
//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_SR register.
//
//*****************************************************************************
#define SSI_SR_BSY              0x00000010  // SSI Busy Bit
#define SSI_SR_RFF              0x00000008  // SSI Receive FIFO Full
#define SSI_SR_RNE              0x00000004  // SSI Receive FIFO Not Empty
#define SSI_SR_TNF              0x00000002  // SSI Transmit FIFO Not Full
#define SSI_SR_TFE              0x00000001  // SSI Transmit FIFO Empty

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CPSR register.
//
//*****************************************************************************
#define SSI_CPSR_CPSDVSR_M      0x000000FF  // SSI Clock Prescale Divisor
#define SSI_CPSR_CPSDVSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_0_MINFLTPER
// register.
//
//*****************************************************************************
#define PWM_0_MINFLTPER_M       0x0000FFFF  // Minimum Fault Period
#define PWM_0_MINFLTPER_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_CC register.
//
//*****************************************************************************
#define PWM_CC_USEPWM           0x00000100  // Use PWM Clock Divisor
#define PWM_CC_PWMDIV_M         0x00000007  // PWM Clock Divider
#define PWM_CC_PWMDIV_2         0x00000000  // /2
#define PWM_CC_PWMDIV_4         0x00000001  // /4
#define PWM_CC_PWMDIV_8         0x00000002  // /8
#define PWM_CC_PWMDIV_16        0x00000003  // /16
#define PWM_CC_PWMDIV_32        0x00000004  // /32
#define PWM_CC_PWMDIV_64        0x00000005  // /64

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_CTL register.
//
//*****************************************************************************
#define QEI_CTL_FILTCNT_M       0x000F0000  // Input Filter Prescale Count
#define QEI_CTL_FILTEN          0x00002000  // Enable Input Filter
#define QEI_CTL_STALLEN         0x00001000  // Stall QEI
#define QEI_CTL_INVI            0x00000800  // Invert Index Pulse
#define QEI_CTL_INVB            0x00000400  // Invert PhB
#define QEI_CTL_INVA            0x00000200  // Invert PhA
#define QEI_CTL_VELDIV_M        0x000001C0  // Predivide Velocity
#define QEI_CTL_VELDIV_1        0x00000000  // QEI clock /1
#define QEI_CTL_VELDIV_2        0x00000040  // QEI clock /2
#define QEI_CTL_VELDIV_4        0x00000080  // QEI clock /4
#define QEI_CTL_VELDIV_8        0x000000C0  // QEI clock /8
#define QEI_CTL_VELDIV_16       0x00000100  // QEI clock /16
#define QEI_CTL_VELDIV_32       0x00000140  // QEI clock /32
#define QEI_CTL_VELDIV_64       0x00000180  // QEI clock /64
#define QEI_CTL_VELDIV_128      0x000001C0  // QEI clock /128
#define QEI_CTL_VELEN           0x00000020  // Capture Velocity
#define QEI_CTL_RESMODE         0x00000010  // Reset Mode
#define QEI_CTL_CAPMODE         0x00000008  // Capture Mode
#define QEI_CTL_SIGMODE         0x00000004  // Signal Mode
#define QEI_CTL_SWAP            0x00000002  // Swap Signals
#define QEI_CTL_ENABLE          0x00000001  // Enable QEI
#define QEI_CTL_FILTCNT_S       16

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_STAT register.
//
//*****************************************************************************
#define QEI_STAT_DIRECTION      0x00000002  // Direction of Rotation
#define QEI_STAT_ERROR          0x00000001  // Error Detected

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_POS register.
//
//*****************************************************************************
#define QEI_POS_M               0xFFFFFFFF  // Current Position Integrator
                                            // Value
#define QEI_POS_S               0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_MAXPOS register.
//
//*****************************************************************************
#define QEI_MAXPOS_M            0xFFFFFFFF  // Maximum Position Integrator
                                            // Value
#define QEI_MAXPOS_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_LOAD register.
//
//*****************************************************************************
#define QEI_LOAD_M              0xFFFFFFFF  // Velocity Timer Load Value
#define QEI_LOAD_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_TIME register.
//
//*****************************************************************************
#define QEI_TIME_M              0xFFFFFFFF  // Velocity Timer Current Value
#define QEI_TIME_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_COUNT register.
//
//*****************************************************************************
#define QEI_COUNT_M             0xFFFFFFFF  // Velocity Pulse Count
#define QEI_COUNT_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_SPEED register.
//
//*****************************************************************************
#define QEI_SPEED_M             0xFFFFFFFF  // Velocity
#define QEI_SPEED_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_INTEN register.
//
//*****************************************************************************
#define QEI_INTEN_ERROR         0x00000008  // Phase Error Interrupt Enable
#define QEI_INTEN_DIR           0x00000004  // Direction Change Interrupt
                                            // Enable
#define QEI_INTEN_TIMER         0x00000002  // Timer Expires Interrupt Enable
#define QEI_INTEN_INDEX         0x00000001  // Index Pulse Detected Interrupt
                                            // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_RIS register.
//
//*****************************************************************************
#define QEI_RIS_ERROR           0x00000008  // Phase Error Detected
#define QEI_RIS_DIR             0x00000004  // Direction Change Detected
#define QEI_RIS_TIMER           0x00000002  // Velocity Timer Expired
#define QEI_RIS_INDEX           0x00000001  // Index Pulse Asserted

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_ISC register.
//
//*****************************************************************************
#define QEI_ISC_ERROR           0x00000008  // Phase Error Interrupt
#define QEI_ISC_DIR             0x00000004  // Direction Change Interrupt
#define QEI_ISC_TIMER           0x00000002  // Velocity Timer Expired Interrupt
#define QEI_ISC_INDEX           0x00000001  // Index Pulse Interrupt


//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCGPIO
// register.
//
//*****************************************************************************
#define SYSCTL_RCGCGPIO_R14     0x00004000  // GPIO Port Q Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R13     0x00002000  // GPIO Port P Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R12     0x00001000  // GPIO Port N Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R11     0x00000800  // GPIO Port M Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R10     0x00000400  // GPIO Port L Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R9      0x00000200  // GPIO Port K Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R8      0x00000100  // GPIO Port J Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R7      0x00000080  // GPIO Port H Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R6      0x00000040  // GPIO Port G Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R5      0x00000020  // GPIO Port F Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R4      0x00000010  // GPIO Port E Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R3      0x00000008  // GPIO Port D Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R2      0x00000004  // GPIO Port C Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R1      0x00000002  // GPIO Port B Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCGPIO_R0      0x00000001  // GPIO Port A Run Mode Clock
                                            // Gating Control
//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCSSI register.
//
//*****************************************************************************
#define SYSCTL_RCGCSSI_R3       0x00000008  // SSI Module 3 Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCSSI_R2       0x00000004  // SSI Module 2 Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCSSI_R1       0x00000002  // SSI Module 1 Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCSSI_R0       0x00000001  // SSI Module 0 Run Mode Clock
                                            // Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCPWM register.
//
//*****************************************************************************
#define SYSCTL_RCGCPWM_R0       0x00000001  // PWM Module 0 Run Mode Clock
                                            // Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCQEI register.
//
//*****************************************************************************
#define SYSCTL_RCGCQEI_R0       0x00000001  // QEI Module 0 Run Mode Clock
                                            // Gating Control
//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRGPIO register.
//
//*****************************************************************************
#define SYSCTL_PRGPIO_R14       0x00004000  // GPIO Port Q Peripheral Ready
#define SYSCTL_PRGPIO_R13       0x00002000  // GPIO Port P Peripheral Ready
#define SYSCTL_PRGPIO_R12       0x00001000  // GPIO Port N Peripheral Ready
#define SYSCTL_PRGPIO_R11       0x00000800  // GPIO Port M Peripheral Ready
#define SYSCTL_PRGPIO_R10       0x00000400  // GPIO Port L Peripheral Ready
#define SYSCTL_PRGPIO_R9        0x00000200  // GPIO Port K Peripheral Ready
#define SYSCTL_PRGPIO_R8        0x00000100  // GPIO Port J Peripheral Ready
#define SYSCTL_PRGPIO_R7        0x00000080  // GPIO Port H Peripheral Ready
#define SYSCTL_PRGPIO_R6        0x00000040  // GPIO Port G Peripheral Ready
#define SYSCTL_PRGPIO_R5        0x00000020  // GPIO Port F Peripheral Ready
#define SYSCTL_PRGPIO_R4        0x00000010  // GPIO Port E Peripheral Ready
#define SYSCTL_PRGPIO_R3        0x00000008  // GPIO Port D Peripheral Ready
#define SYSCTL_PRGPIO_R2        0x00000004  // GPIO Port C Peripheral Ready
#define SYSCTL_PRGPIO_R1        0x00000002  // GPIO Port B Peripheral Ready
#define SYSCTL_PRGPIO_R0        0x00000001  // GPIO Port A Peripheral Ready


//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRACMP register.
//
//*****************************************************************************
#define SYSCTL_PRACMP_R0        0x00000001  // Analog Comparator Module 0
                                            // Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRPWM register.
//
//*****************************************************************************
#define SYSCTL_PRPWM_R0         0x00000001  // PWM Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRQEI register.
//
//*****************************************************************************
#define SYSCTL_PRQEI_R0         0x00000001  // QEI Module 0 Peripheral Ready

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_CPAC register.
//
//*****************************************************************************
#define NVIC_CPAC_CP11_M        0x00C00000  // CP11 Coprocessor Access
                                            // Privilege
#define NVIC_CPAC_CP11_DIS      0x00000000  // Access Denied
#define NVIC_CPAC_CP11_PRIV     0x00400000  // Privileged Access Only
#define NVIC_CPAC_CP11_FULL     0x00C00000  // Full Access
#define NVIC_CPAC_CP10_M        0x00300000  // CP10 Coprocessor Access
                                            // Privilege
#define NVIC_CPAC_CP10_DIS      0x00000000  // Access Denied
#define NVIC_CPAC_CP10_PRIV     0x00100000  // Privileged Access Only
#define NVIC_CPAC_CP10_FULL     0x00300000  // Full Access


//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED
#define SYSCTL_DID0_CLASS_SNOWFLAKE                                           \
                                0x000A0000  // Tiva(TM) C Series TM4C129-class
                                            // microcontrollers

//*****************************************************************************
//
// Deprecated defines for the bit fields in the SYSCTL_PWRTC register.
//
//*****************************************************************************
#define SYSCTL_PWRTC_VDDA_UBOR0 0x00000010  // VDDA Under BOR0 Status
#define SYSCTL_PWRTC_VDD_UBOR0  0x00000001  // VDD Under BOR0 Status

#endif

#endif // __TM4C1294NCPDT_H__
