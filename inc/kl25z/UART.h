
/**
 * @file UART.h
 * @brief UART configuration sending and receiving
 *
 *
 * @author Zachary Asmussen
 * @date February 21st, 2018
 *
 */
#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>
#include <stdlib.h>
#include "MKL25Z4.h"
#include "circbuf.h"


#define BAUD_RATE       19200
#define UART0_CLOCK     48000000
#define OSR             0x0F
#define CALCULATED_BDH  (((DEFAULT_SYSTEM_CLOCK/((OSR+1)*BAUD_RATE))&0x1F00)>>8)
#define CALCULATED_BDL  ((DEFAULT_SYSTEM_CLOCK/((OSR+1)*BAUD_RATE))&0xFF)
#define PCR2            2
#define IRQC            0
#define ISF1            1
#define UARTCLR         3
#define FLLPLL          1
#define  FLLPLLCLR      1
#define FLLSEL          0
#define RXCLR           1
#define RXSEL           0
#define TXCLR           3
#define TXSEL           0
#define C1PT            0
#define C1PE            0
#define C1ILT           1
#define C1WAKE          0
#define C1M             0
#define C1RSRC          0
#define C1DOZEEN        0
#define C1LOOPS         0
#define C2SBK           0
#define C2RWU           0
#define C2RE            1
#define C2TE            1
#define C2ILIE          0
#define C2RIE           1
#define C2TCIE          0
#define C2TIE           0
/**
 * @brief Configures UART settings
 *
 * This function configures our UART settings
 *
 * @return is the status of the function
 */
uint8_t UART_configure();


/**
 * @brief Sends UART byte
 *
 * @param value is the value to send
 * @return is the status of the function
 */
uint8_t UART_send(uint8_t value);


/**
 * @brief Sends n UART bytes
 *
 * @param value is the pointer to the array to send
 * @param size is the size of the array
 * @return is the status of the function
 */
uint8_t UART_send_n(uint8_t * value, size_t size);


/**
 * @brief Receives UART byte
 *
 * @param value is where to store received byte
 * @return is the status of the function
 */
uint8_t UART_receive(uint8_t * value);


/**
 * @brief Receivces n UART bytes
 *
 * @param value is where to store received bytes
 * @param size is the amount to receive
 * @return is the status of the function
 */
uint8_t UART_receive_n(uint8_t * value, size_t size);

/**
 * @brief Interrupt handler for UART0
 *
 */
void UART0_IRQHandler();

#endif
