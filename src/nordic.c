/**
 * @file nordic.c
 * @brief HAL for the NRF24L01
 *
 * High level abstraction library for communication
 * with the NRF24L01 chip using SPI
 *
 * @author Zachary Asmussen
 * @date March 12th, 2018
 *
 */

#include "nordic.h"

uint8_t nrf_read_register(uint8_t reg)
{
  uint8_t byte = 0;
  #ifdef KL25Z
  ENABLE_SS;
  SPI_write_byte(reg);
  SPI_read_byte(&byte);
  SPI_write_byte(reg);
  SPI_read_byte(&byte);
  DISABLE_SS;
  #endif
  return byte;
}



void nrf_write_register(uint8_t reg, uint8_t value)
{
  #ifdef KL25Z
  ENABLE_SS;
  uint8_t byte;
  SPI_write_byte(0x20|reg);
  SPI_read_byte(&byte);
  SPI_write_byte(value);
  SPI_read_byte(&byte);
  DISABLE_SS;
  #endif
}



uint8_t nrf_read_status()
{
  uint8_t status = nrf_read_register(NRF_STATUS_REG);
  return status;
}



void nrf_write_config(uint8_t config)
{
  nrf_write_register(NRF_CONFIG_REG, config);
}



uint8_t nrf_read_config()
{
  uint8_t config = nrf_read_register(NRF_CONFIG_REG);
  return config;
}



uint8_t nrf_read_rf_setup()
{
  uint8_t setup = nrf_read_register(NRF_RF_SETUP_REG);
  return setup;
}



void nrf_write_rf_setup(uint8_t config)
{
  nrf_write_register(NRF_RF_SETUP_REG, config);
}



uint8_t nrf_read_rf_ch()
{
  uint8_t ch = nrf_read_register(NRF_RF_CH_REG);
  return ch;
}



void nrf_write_rf_ch(uint8_t channel)
{
  nrf_write_register(NRF_RF_CH_REG, channel);
}



void nrf_read_TX_ADDR(uint8_t * address)
{
  #ifdef KL25Z
  ENABLE_SS;
  SPI_write_byte(NRF_TX_ADDR_REG);
  SPI_read_byte(address);
  SPI_write_byte(0);
  SPI_read_byte(address);
  SPI_write_byte(0);
  SPI_read_byte(++address);
  SPI_write_byte(0);
  SPI_read_byte(++address);
  SPI_write_byte(0);
  SPI_read_byte(++address);
  SPI_write_byte(0);
  SPI_read_byte(++address);
  DISABLE_SS;
  #endif
}



void nrf_write_TX_ADDR(uint8_t * tx_addr)
{
  #ifdef KL25Z
  ENABLE_SS;
  uint8_t byte;
  SPI_write_byte(0x20|NRF_TX_ADDR_REG);
  SPI_read_byte(&byte);
  SPI_write_byte(*tx_addr);
  SPI_read_byte(&byte);
  SPI_write_byte(*(tx_addr+1));
  SPI_read_byte(&byte);
  SPI_write_byte(*(tx_addr+2));
  SPI_read_byte(&byte);
  SPI_write_byte(*(tx_addr+3));
  SPI_read_byte(&byte);
  SPI_write_byte(*(tx_addr+4));
  SPI_read_byte(&byte);
  DISABLE_SS;
  #endif
}



uint8_t nrf_read_fifo_status()
{
  uint8_t FIFO = nrf_read_register(NRF_FIFO_STATUS_REG);
  return FIFO;
}



void nrf_flush_tx_fifo()
{
  #ifdef KL25Z
  SPI_write_byte(NRF_FLUSH_TX_COMMAND);
  #endif
}



void nrf_flush_rx_fifo()
{
  #ifdef KL25Z
  SPI_write_byte(NRF_FLUSH_RX_COMMAND);
  #endif
}
