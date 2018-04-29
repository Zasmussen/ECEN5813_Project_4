/**
 * @file spi.h
 * @brief KL25Z SPI library
 *
 * Low level Serial Peripheral Interface library
 * for the KL25Z
 *
 * @author Zachary Asmussen
 * @date March 12th, 2018
 *
 */
#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>
#include <stdlib.h>
#include "MKL25Z4.h"
#include "GPIO.h"
#include "platform.h"


/**
 * @brief Initializes the SPI driver
 *
 * This function sets all registers to initial
 * values for the SPI driver
 *
 */
void SPI_init();



/**
 * @brief Reads a single SPI byte
 *
 * This function reads a byte to the KL25Z from
 * the SPI bus
 *
 * @param byte is the byte read from SPI
 *
 */
void SPI_read_byte(uint8_t * byte);



/**
 * @brief Writes a single SPI byte
 *
 * This function writes a byte from the KL25Z
 * to the SPI bus
 *
 * @param byte is the value to write
 *
 */
void SPI_write_byte(uint8_t byte);



/**
 * @brief Sends packet of bytes to SPI
 *
 * This function sends a string of bytes to the SPI bus
 * from a pointer with a certain length
 *
 * @param p is a pointer to the packet of bytes
 * @param length is the amount of bytes to send
 *
 */
void SPI_send_packet(uint8_t * p, size_t length);



/**
 * @brief Blocks SPI until transmission is complete
 *
 * When sending data through transmission this blocks the SPI
 * bus until it has completed
 *
 */
void SPI_flush();


#endif
