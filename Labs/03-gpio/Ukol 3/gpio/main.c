/***********************************************************************
 *
 * Alternately toggle two LEDs when a push button is pressed. Use
 * functions from GPIO library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2019-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_RED_0     PC0     // AVR pin where red LED0 is connected
#define LED_RED_1     PC1     // AVR pin where red LED1 is connected
#define LED_RED_2     PC2     // AVR pin where red LED2 is connected
#define LED_RED_3     PC3     // AVR pin where red LED3 is connected
#define LED_RED_4     PC4     // AVR pin where red LED4 is connected
#define BTN         PD0     // AVR pin where button is connected
#define BLINK_DELAY 500
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include "gpio.h"           // GPIO library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs
 * when a push button is pressed. Functions from user-defined GPIO
 * library is used instead of low-level logic operations.
 */
int main(void)
{
    int8_t i;
    /* RED LED0 */
    GPIO_config_output(&DDRC, LED_RED_0);
    GPIO_write_high(&PORTC, LED_RED_0);

    /* RED LED1 */
    GPIO_config_output(&DDRC, LED_RED_1);
    GPIO_write_low(&PORTC, LED_RED_1);

    /* RED LED2 */
    GPIO_config_output(&DDRC, LED_RED_2);
    GPIO_write_low(&PORTC, LED_RED_2);

    /* RED LED3 */
    GPIO_config_output(&DDRC, LED_RED_3);
    GPIO_write_low(&PORTC, LED_RED_3);

    /* RED LED4 */
    GPIO_config_output(&DDRC, LED_RED_4);
    GPIO_write_low(&PORTC, LED_RED_4);

    /* push button */
    GPIO_config_input_pullup(&DDRD, BTN);

    // Infinite loop
    while (1)
    {
        for(i=0;i<4;i++)
        {
            // Pause several milliseconds
            _delay_ms(BLINK_DELAY);

            loop_until_bit_is_clear(PIND, BTN);

            GPIO_shift(&PORTC);
        }

        for(i=0;i<4;i++)
        {
            // Pause several milliseconds
            _delay_ms(BLINK_DELAY);

            loop_until_bit_is_clear(PIND, BTN);

            GPIO_unshift(&PORTC);
       }
    }

    // Will never reach this
    return 0;
}
