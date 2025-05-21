/*
 * Peripheral_Setup.h
 *
 * Created on: 10 Nov 2024
 * Author: Vande
 */

#ifndef PERIPHERAL_SETUP_H_    /* Include guard to prevent multiple inclusion */
#define PERIPHERAL_SETUP_H_

/* Include necessary header for device-specific definitions */
#include "F28x_Project.h"

/* Function Prototypes */

/*
 * Function: Setup_GPIO
 * --------------------
 * Configures GPIO pins for:
 *  - LED output on GPIO31 (Port A) and GPIO34 (Port B)
 *  - ePWM output pins:
 *      - GPIO0 and GPIO1 for ePWM1A and ePWM1B
 *      - GPIO157 and GPIO159 for ePWM7A and ePWM8A
 */
void Setup_GPIO(void);

/*
 * Function: Setup_ePWM
 * ---------------------
 * Initializes and configures:
 *  - ePWM1 module for center-aligned PWM generation with dead-band
 *  - ePWM7 and ePWM8 modules for phase-shifted PWM generation
 */
void Setup_ePWM(void);

#endif /* PERIPHERAL_SETUP_H_ */
