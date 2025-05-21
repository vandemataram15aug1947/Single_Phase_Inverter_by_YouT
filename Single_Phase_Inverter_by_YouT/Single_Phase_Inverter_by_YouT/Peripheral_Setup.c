/*
 * Peripheral_Setup.c
 *
 *  Created on: 10 Nov 2024
 *      Author: Vande
 */

#include "Peripheral_Setup.h"

/*
 * Function: Setup_GPIO
 * --------------------
 * Configures GPIO pins for LEDs and ePWM signals.
 */
void Setup_GPIO(void) {
    EALLOW;

    /* Configure GPIO31 (LED on GPIO31 - Port A, Pin 2) */
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO31   = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO31   = 1;
    GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;

    /* Configure GPIO34 (LED on GPIO34 - Port B, Pin 1) */
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34  = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO34   = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34   = 1;
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;

    /* Configure PWM1A on GPIO0 */
    GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO0   = 1;

    /* Configure PWM1B on GPIO1 */
    GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO1   = 1;

    /* Configure PWM7A on GPIO157 */
    GpioCtrlRegs.GPEGMUX2.bit.GPIO157 = 0;
    GpioCtrlRegs.GPEMUX2.bit.GPIO157  = 1;
    GpioCtrlRegs.GPEPUD.bit.GPIO157   = 1;

    /* Configure PWM8A on GPIO159 */
    GpioCtrlRegs.GPEGMUX2.bit.GPIO159 = 0;
    GpioCtrlRegs.GPEMUX2.bit.GPIO159  = 1;
    GpioCtrlRegs.GPEPUD.bit.GPIO159   = 1;

    EDIS;
}

/*
 * Function: Setup_ePWM
 * --------------------
 * Configures ePWM1, ePWM7, and ePWM8 modules for up-down counting,
 * PWM generation with dead-band (on ePWM1), and synchronization.
 */
void Setup_ePWM(void) {
    EALLOW;

    /* Enable clocks for ePWM1, ePWM7, and ePWM8 */
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM7 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM8 = 1;

    /* Disable TBCLK synchronization before configuration */
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    /* === ePWM1 Configuration === */
    EPwm1Regs.TBPRD = 2000;
    EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD >> 1;
    EPwm1Regs.TBPHS.bit.TBPHS = 0;
    EPwm1Regs.TBCTR = 0x0000;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;

    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBRED.bit.DBRED = 100;
    EPwm1Regs.DBFED.bit.DBFED = 100;

    /* === ePWM7 Configuration === */
    EPwm7Regs.TBPRD = 2000;
    EPwm7Regs.CMPA.bit.CMPA = 0;
    EPwm7Regs.TBPHS.bit.TBPHS = 2000;
    EPwm7Regs.TBCTR = 0x0000;
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm7Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm7Regs.TBCTL.bit.PHSDIR = TB_DOWN;
    EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;

    EPwm7Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm7Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm7Regs.AQCTLA.bit.CAD = AQ_SET;

    /* === ePWM8 Configuration === */
    EPwm8Regs.TBPRD = 2000;
    EPwm8Regs.CMPA.bit.CMPA = 0;
    EPwm8Regs.TBPHS.bit.TBPHS = 1000;
    EPwm8Regs.TBCTR = 0x0000;
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm8Regs.TBCTL.bit.PHSDIR = TB_DOWN;
    EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;

    EPwm8Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm8Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm8Regs.AQCTLA.bit.CAD = AQ_SET;

    /* Re-enable TBCLK synchronization */
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    EDIS;
}
