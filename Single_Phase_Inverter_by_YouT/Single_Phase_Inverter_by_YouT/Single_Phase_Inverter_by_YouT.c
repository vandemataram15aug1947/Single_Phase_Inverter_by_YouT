/*
 * Single_Phase_Inverter_by_YouT.c
 *
 * Created on: 10 Nov 2024
 * Author: Vande
 */

#include "Peripheral_Setup.h"
#include "math.h"

/* Global Variables */
uint32_t count = 0, index = 0;
uint16_t sinetable[125];

/* Function Prototypes */
__interrupt void isr_cpu_timer0(void);

/*
 * Function: main
 * --------------
 * Entry point of the program. Initializes system control, peripherals,
 * CPU timer and sine table, then enters an infinite loop toggling GPIOs.
 */
int main(void)
{
    InitSysCtrl();  /* Initialize System Control: PLL, WatchDog, enable Peripheral Clocks */

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;  /* Enable clock for CPU Timer 0 */
    EDIS;

    DINT;              /* Disable CPU interrupts */
    InitPieCtrl();     /* Initialize PIE control registers to default */
    IER = 0x0000;      /* Disable all CPU interrupts */
    IFR = 0x0000;      /* Clear all CPU interrupt flags */
    InitPieVectTable();/* Initialize the PIE vector table */

    Setup_GPIO();      /* Setup GPIO for LEDs and ePWM outputs */
    Setup_ePWM();      /* Configure ePWM modules */

    EALLOW;
    PieVectTable.TIMER0_INT = &isr_cpu_timer0;     /* Map Timer0 ISR */
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;             /* Enable INTx7 for Timer 0 */
    EDIS;
    IER |= M_INT1;      /* Enable CPU INT1 */

    InitCpuTimers();    /* Initialize CPU Timers */
    ConfigCpuTimer(&CpuTimer0, 200, 160); /* 200MHz SYSCLK, 160us Period */
    CpuTimer0Regs.TCR.all = 0x4001;       /* Enable Timer0 with interrupt */

    /* Generate sine lookup table */
    for(index = 0; index < 125; index++)
    {
        sinetable[index] = (uint16_t)(1000.0 * (1.0 + sin(6.28318531 / 125.0 * ((float)index))));
    }
    index = 0;

    EINT;  /* Enable global interrupt INTM */
    ERTM;  /* Enable real-time interrupt DBGM */

    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;  /* Set GPIO34 HIGH */
    GpioDataRegs.GPADAT.bit.GPIO31 = 0;  /* Set GPIO31 LOW */

    /* Main loop: simple delay + LED toggle */
    while(1)
    {
        for(count = 0; count < 0x00FFFFFF; count++)
        {
            /* Software delay */
        }

        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;  /* Toggle GPIO34 */
        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;  /* Toggle GPIO31 */
    }

    return 0;
}

/*
 * Function: isr_cpu_timer0
 * ------------------------
 * Interrupt Service Routine for CPU Timer 0.
 * Toggles GPIO31, updates index and sets PWM compare values using the sine table.
 */
__interrupt void isr_cpu_timer0(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;  /* Toggle GPIO31 */

    index = (index == 124) ? 0 : (index + 1);  /* Increment or wrap index */

    EPwm7Regs.CMPA.bit.CMPA = sinetable[index];  /* Update ePWM7 compare value */
    EPwm8Regs.CMPA.bit.CMPA = sinetable[index];  /* Update ePWM8 compare value */

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;  /* Acknowledge interrupt */
}
