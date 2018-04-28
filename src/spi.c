/**
 * @file spi.c
 * @brief KL25Z SPI library
 *
 * Low level Serial Peripheral Interface library
 * for the KL25Z
 *
 * @author Zachary Asmussen
 * @date March 12th, 2018
 *
 */
#include "spi.h"


void SPI_init()
{
  /* Enable pins for SPI0 */
  GPIO_nrf_init();

  /* Enable clock gating for SPI0 */
  SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

  SPI0_C1 = SPI_C1_LSBFE(0)           // Transfers start with LSb first
            |SPI_C1_SSOE(0)           // SS pin is GPIO (unless MODFEN is 1 then it is automatic SS output)
            |SPI_C1_CPHA(0)           // First edge occurs on start of first cycle
            |SPI_C1_CPOL(0)           // Active high clock
            |SPI_C1_MSTR(1)           // Acts as master device
            |SPI_C1_SPTIE(0)          // Transmit buffer empty interrupt off
            |SPI_C1_SPE(0)            // SPI disabled
            |SPI_C1_SPIE(0);          // Receive buffer full interrupt off

  SPI0_C2 = SPI_C2_SPC0(0)            // Bidirectional mode off
            |SPI_C2_SPISWAI(0)        // SPI continues in wait mode
            |SPI_C2_RXDMAE(0)         // DMA disabled for SPI
            |SPI_C2_BIDIROE(0)        // Means nothing since bidirectional mode is off
            |SPI_C2_MODFEN(1)         // Sets SS pin to automatic select controlled by SPI
            |SPI_C2_TXDMAE(0)         // DMA disabled for SPI
            |SPI_C2_SPMIE(0);         // Receivce data buffer hardware match interript disabled

  SPI0_BR = SPI_BR_SPR(8) | SPI_BR_SPPR(2);   // Prescale divisor and baud rate divisor are 1 and 2 respectively
  SPI0_C1 |= SPI_C1_SPE(1);
}

void SPI_read_byte(uint8_t * byte)
{
  while(!(SPI0_S & SPI_S_SPRF_MASK));
  *byte = SPI0_D;
}

void SPI_write_byte(uint8_t byte)
{
  while(!(SPI0_S & SPI_S_SPTEF_MASK));
  SPI0_D = byte;
}

void SPI_send_packet(uint8_t * p, size_t length)
{
  uint32_t i;
  for(i=0;i<length;i++)
  {
    SPI_write_byte(*(p+i));
  }
}

void SPI_flush()
{
  while(!(SPI0_S & SPI_S_SPTEF_MASK));
}
