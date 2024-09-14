/*
 * Peripheral_Setup.c
 *
 *  Created on: 10 Nov 2024
 *      Author: Vande
 */
#include "Peripheral_Setup.h"


void Setup_GPIO(void){
	EALLOW;
	// LED 31 A, 2
	// LED 34 B, 1
	GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;

	GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;

	GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;

	GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

	GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;
	GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;

	GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;
	GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;

	//PWM 1A e 1B
	GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;

	GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;

	//PWM 7A e 8A
	GpioCtrlRegs.GPEGMUX2.bit.GPIO157 = 0;
	GpioCtrlRegs.GPEMUX2.bit.GPIO157 = 1;
	GpioCtrlRegs.GPEPUD.bit.GPIO157 = 1;

	GpioCtrlRegs.GPEGMUX2.bit.GPIO159 = 0;
	GpioCtrlRegs.GPEMUX2.bit.GPIO159 = 1;
	GpioCtrlRegs.GPEPUD.bit.GPIO159 = 1;
	EDIS;
}

void Setup_ePWM(void){
	EALLOW;
	CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM7 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM8 = 1;

	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

	EPwm1Regs.TBPRD = 2000;							// Set timer period
	EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD >> 1;

	EPwm1Regs.TBPHS.bit.TBPHS = 0;             		// Phase is 0
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
	EPwm1Regs.TBCTR = 0x0000;                       // Clear counter
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// Count up/down
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        	// Disable phase loading
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       	// Clock ratio to SYSCLKOUT
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    	// Load registers every ZERO
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;    	// Load registers every ZERO
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

	EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// set actions for EPWM1A
	EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;

	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active Hi complementary
	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; 	// enable Dead-band module
	EPwm1Regs.DBFED.bit.DBFED = 100; 				// FED = 20 TBCLKs
	EPwm1Regs.DBRED.bit.DBRED = 100; 				// RED = 20 TBCLKs

	// PWM 7A
	EPwm7Regs.TBPRD = 2000;							// Set timer period
	EPwm7Regs.CMPA.bit.CMPA = 0;
	EPwm7Regs.TBPHS.bit.TBPHS = 2000;             		// Phase is 0
	EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm7Regs.TBCTR = 0x0000;                       // Clear counter
	EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// Count up/down
	EPwm7Regs.TBCTL.bit.PHSEN = TB_ENABLE;        	// Disable phase loading
	EPwm7Regs.TBCTL.bit.PHSDIR = TB_DOWN;        	// Phase UP/DOWN
	EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       	// Clock ratio to SYSCLKOUT
	EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    	// Load registers every ZERO
	EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;

	EPwm7Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
	EPwm7Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
	EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// set actions for EPWM1A
	EPwm7Regs.AQCTLA.bit.CAD = AQ_SET;

	// PWM 7B
	EPwm8Regs.TBPRD = 2000;							// Set timer period
	EPwm8Regs.CMPA.bit.CMPA = 0;
	EPwm8Regs.TBPHS.bit.TBPHS = 1000;             		// Phase is 0
	EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm8Regs.TBCTR = 0x0000;                       // Clear counter
	EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// Count up/down
	EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE;        	// Disable phase loading
	EPwm8Regs.TBCTL.bit.PHSDIR = TB_DOWN;        	// Phase UP/DOWN
	EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       	// Clock ratio to SYSCLKOUT
	EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    	// Load registers every ZERO
	EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;

	EPwm8Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
	EPwm8Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
	EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR; 			// set actions for EPWM1A
	EPwm8Regs.AQCTLA.bit.CAD = AQ_SET;


	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

	EDIS;

}

