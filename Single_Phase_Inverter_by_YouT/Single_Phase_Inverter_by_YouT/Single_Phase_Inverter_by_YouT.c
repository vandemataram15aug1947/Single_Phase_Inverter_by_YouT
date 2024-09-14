/*
 * Single_Phase_Inverter_by_YouT.c
 *
 Created on: 10 Nov 2024
 *      Author: Vande
 */

#include "Peripheral_Setup.h"
#include "math.h"

/**
 * main.c
 */
uint32_t count = 0, index = 0;
uint16_t sinetable[125];

__interrupt void isr_cpu_timer0(void);

int main(void){
	InitSysCtrl();							// Initialize System Control:

	EALLOW;
	CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;
	EDIS;

	DINT;									// Disable CPU interrupts
	InitPieCtrl();							// Initialize the PIE control registers to their default state
	IER = 0x0000;							// Disable CPU interrupts
	IFR = 0x0000;							// Clear all CPU interrupt flags:
	InitPieVectTable();						// Initialize the PIE vector table

	Setup_GPIO();
	Setup_ePWM();

	EALLOW;
	PieVectTable.TIMER0_INT = &isr_cpu_timer0;
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1; 		//Timer 0
	EDIS;
	IER |= M_INT1;

	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 200, 160);
	CpuTimer0Regs.TCR.all = 0x4001;

	for(index = 0; index < 125; index++){
		sinetable[index] = (uint16_t)(1000.0*(1.0 + sin(6.28318531/125.0*((float)index))));
	}
	index = 0;

	EINT;  									// Enable Global interrupt INTM
	ERTM;  									// Enable Global realtime interrupt DBGM
	GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
	GpioDataRegs.GPADAT.bit.GPIO31 = 0;
	while(1){
		for(count = 0; count < 0x00FFFFFF; count++){

		}
		GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
		//GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
	}
	return 0;
}

__interrupt void isr_cpu_timer0(void){
	GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

	index = (index == 124) ? 0 : (index+1);

	EPwm7Regs.CMPA.bit.CMPA = sinetable[index];
	EPwm8Regs.CMPA.bit.CMPA = sinetable[index];

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
