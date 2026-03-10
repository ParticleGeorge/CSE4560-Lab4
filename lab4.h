/*
 *
 */

#ifndef LAB4_H_
#define LAB4_H_


#include <stdint.h>                            // Standard Integer - data type definitions
#include <stdio.h>                             // Standard I/O definitions
#include <stdarg.h>
#include <math.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>    // TI Platform library
#include "uart.h"

#define UART_BAUDRATE     115200
#define M_PI              acos(-1.0)

/**
 * @brief Embedded Systems (ES) Lab2
 *
 * Task 1: Interrupts
 */
void task1(void);
/**
 * Task 2: Timers & PWM
 */
void task2(void);



#endif /* LAB4_H_ */
