/**
 * @file GPIO.h
 * @brief KL25Z GPIO abstraction layer for manipulating I/O
 *
 * Here we abstract the use of General Purpose Input Output registers
 * to control I/O pins on the KL25Z
 *
 * @author Zachary Asmussen
 * @date February 21st, 2018
 *
 */
#ifndef __GPIO_H__
#define __GPIO_H__
#include <stdint.h>
#include <stdlib.h>
#include "logger.h"
#include "logger_queue.h"

#define RGB_RED_PIN   (1 << 18)      // PTB18
#define RGB_GREEN_PIN (1 << 19)      // PTB19
#define RGB_BLUE_PIN  (1 << 1)      // PTD1

#define RGB_RED_ON()          (PORTB_Set(RGB_RED_PIN))
#define RGB_RED_OFF()         (PORTB_Clear(RGB_RED_PIN))
#define RGB_RED_TOGGLE()      (PORTB_Toggle(RGB_RED_PIN))

#define RGB_GREEN_ON()        (PORTB_Set(RGB_GREEN_PIN))
#define RGB_GREEN_OFF()       (PORTB_Clear(RGB_GREEN_PIN))
#define RGB_GREEN_TOGGLE()    (PORTB_Toggle(RGB_GREEN_PIN))

#define RGB_BLUE_ON()         (PORTB_Set(RGB_BLUE_PIN))
#define RGB_BLUE_OFF()        (PORTB_Clear(RGB_BLUE_PIN))
#define RGB_BLUE_TOGGLE()     (PORTB_Toggle(RGB_BLUE_PIN))

extern LB_t * logBuff;

/**
 * @brief Configures the RGB LED's
 *
 * This configures the RGB LED's of the KL25Z to be set to an output
 * mode with an initial value
 *
 */
void GPIO_Configure();



/**
 * @brief Toggles the red LED
 *
 * This abstractly toggles the red LED of the KL25Z through register
 * manipulation
 *
 */
void Toggle_Red_LED();



/**
 * @brief Sets a bit of Port B
 *
 * This function sets the bit specified by bit_num in GPIO port B to a 1
 *
 * @param bit_num is the speicifc bit in port B to be set
 */
void PORTB_Set(uint8_t bit_num);



/**
 * @brief Sets a bit of Port D
 *
 * This function sets the bit specified by bit_num in GPIO port D to a 1
 *
 * @param bit_num is the speicifc bit in port D to be set
 */
void PORTD_Set(uint8_t bit_num);



/**
 * @brief Clears a bit of Port D
 *
 * This function clears the bit specified by bit_num in GPIO port D to a 0
 *
 * @param bit_num is the speicifc bit in port D to be cleared
 */
void PORTB_Clear(uint8_t bit_num);



/**
 * @brief Clears a bit of Port D
 *
 * This function clears the bit specified by bit_num in GPIO port D to a 0
 *
 * @param bit_num is the speicifc bit in port D to be cleared
 */
void PORTD_Clear(uint8_t bit_num);



/**
 * @brief Toggles a bit of Port B
 *
 * This function toggles the bit specified by bit_num in GPIO port B.
 * If the bit is a 1 it will be cleared to a 0 and if it is a 0 it will
 * be set to a 1
 *
 * @param bit_num is the speicifc bit in port B to be toggled
 */
void PORTB_Toggle(uint8_t bit_num);



/**
 * @brief Toggles a bit of Port D
 *
 * This function toggles the bit specified by bit_num in GPIO port D.
 * If the bit is a 1 it will be cleared to a 0 and if it is a 0 it will
 * be set to a 1
 *
 * @param bit_num is the speicifc bit in port D to be toggled
 */
void PORTD_Toggle(uint8_t bit_num);



/**
 * @brief Initializes GPIO for NRF chip
 *
 * Sets correct registers to use SPI driver for communication with
 * the NRF24L01
 *
 */
void GPIO_nrf_init();

#endif
