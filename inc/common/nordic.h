/**
 * @file nordic.h
 * @brief HAL for the NRF24L01
 *
 * High level abstraction library for communication
 * with the NRF24L01 chip using SPI
 *
 * @author Zachary Asmussen
 * @date March 12th, 2018
 *
 */
#ifndef __NORDIC_H__
#define __NORDIC_H__

/* Includes */
#include <stdint.h>
#include <stdlib.h>
#ifdef KL25Z
#include "GPIO.h"
#include "spi.h"
#endif

/* NRF24L01 Register Addresses */
#define NRF_CONFIG_REG                        (0x00)
#define NRF_EN_AA_REG                         (0x01)
#define NRF_EN_RXADDR_REG                     (0x02)
#define NRF_SETUP_AW_REG                      (0x03)
#define NRF_SETUP_RETR_REG                    (0x04)
#define NRF_RF_CH_REG                         (0x05)
#define NRF_RF_SETUP_REG                      (0x06)
#define NRF_STATUS_REG                        (0x07)
#define NRF_OBSERVE_TX_REG                    (0x08)
#define NRF_CD_REG                            (0x09)
#define NRF_RX_ADDR_P0_REG                    (0x0A)
#define NRF_RX_ADDR_P1_REG                    (0x0B)
#define NRF_RX_ADDR_P2_REG                    (0x0C)
#define NRF_RX_ADDR_P3_REG                    (0x0D)
#define NRF_RX_ADDR_P4_REG                    (0x0E)
#define NRF_RX_ADDR_P5_REG                    (0x0F)
#define NRF_TX_ADDR_REG                       (0x10)
#define NRF_RX_PW_P0_REG                      (0x11)
#define NRF_RX_PW_P1_REG                      (0x12)
#define NRF_RX_PW_P2_REG                      (0x13)
#define NRF_RX_PW_P3_REG                      (0x14)
#define NRF_RX_PW_P4_REG                      (0x15)
#define NRF_RX_PW_P5_REG                      (0x16)
#define NRF_FIFO_STATUS_REG                   (0x17)
#define NRF_DYNOD_REG                         (0x1C)
#define NRF_FEATURE_REG                       (0x1D)



/* NRF24LO1 Register Masks */
/* CONFIG */
#define NRF_CONFIG_PRIM_RX_MASK               (0x01)
#define NRF_CONFIG_PWR_UP_MASK                (0x02)
#define NRF_CONFIG_CRCO_MASK                  (0x04)
#define NRF_CONFIG_EN_CRC_MASK                (0x08)
#define NRF_CONFIG_MASK_MAX_RT_MASK           (0x10)
#define NRF_CONFIG_MASK_TX_DS_MASK            (0x20)
#define NRF_CONFIG_MASK_RX_DR_MASK            (0x40)
/* RF_CH */
#define NRF_RF_CH_RF_CH_MASK                  (0x7F)
/* RF_SETUP */
#define NRF_RF_SETUP_LNA_HCURR_MASK           (0x01)
#define NRF_RF_SETUP_RF_PWR_MASK              (0x06)
#define NRF_RF_SETUP_RF_DR_MASK               (0x08)
#define NRF_RF_SETUP_PLL_LOCK_MASK            (0x10)
/* STATUS */
#define NRF_STATUS_TX_FULL_MASK               (0x01)
#define NRF_STATUS_RX_P_NO_MASK               (0x0E)
#define NRF_STATUS_MAX_RT_MASK                (0x10)
#define NRF_STATUS_TX_DS_MASK                 (0x20)
#define NRF_STATUS_RX_DR_MASK                 (0x40)



/* NRF24L01 Commands */
#define NRF_W_REGISTER_COMMAND                (0x20)
#define NRF_R_RX_PAYLOAD_COMMAND              (0x61)
#define NRF_W_TX_PAYLOAD_COMMAND              (0xA0)
#define NRF_FLUSH_TX_COMMAND                  (0xE1)
#define NRF_FLUSH_RX_COMMAND                  (0xE2)
#define NRF_REUSE_TX_PL_COMMAND               (0xE3)
#define NRF_ACTIVATE_COMMAND                  (0x50)
#define NRF_R_RX_PL_WID_COMMAND               (0x60)
#define NRF_W_ACK_PAYLOAD_COMMAND             (0xA8)
#define NRF_W_TX_PAYLOAD_NOACK_COMMAND        (0xB0)
#define NRF_NOP_COMMAND                       (0xFF)


/* Slave Select Enable/Disable */
#define SPI0_SS_PIN     (1 << 4)
#define ENABLE_SS       (GPIOC->PDOR &= ~(SPI0_SS_PIN))
#define DISABLE_SS      (GPIOC->PDOR |= (SPI0_SS_PIN))
#define POWER_UP_NRF    (config = nrf_read_config(); nrf_write_config(config|NRF_CONFIG_PWR_UP_MASK);)
#define POWER_DOWN_NRF  (config = nrf_read_config(); nrf_write_config(config&~(NRF_CONFIG_PWR_UP_MASK));)

/**
 * @brief Reads a register in the NRF
 *
 * Given a certain register this reads the value of that register
 * in the NRF and returns its value
 *
 * @param reg is the register to read
 * @return is the value at that location
 */
uint8_t nrf_read_register(uint8_t reg);



/**
 * @brief Writes to a register
 *
 * Given a register value this writes a certain value to the register
 * in the NRF chip
 *
 * @param reg is the register to change
 * @param value is the value to change it to
 */
void nrf_write_register(uint8_t reg, uint8_t value);



/**
 * @brief Reads status register
 *
 * This reads the value of the status register in the NRF chip
 *
 * @return is the value of the register
 */
uint8_t nrf_read_status();



/**
 * @brief Writes to config register
 *
 * This writes specifically to the configuration register
 * in the NRF chip
 *
 * @param config is the value to write to config
 */
void nrf_write_config(uint8_t config);



/**
 * @brief Reads the config register
 *
 * This reads the value currently in the config register
 * in the NRF chip
 *
 * @return is the value of the register
 */
uint8_t nrf_read_config();



/**
 * @brief Reads RF_SETUP register
 *
 * This reads the value currently in the RF_SETUP register
 * in the NRF chip
 *
 * @return is the value of the register
 */
uint8_t nrf_read_rf_setup();



/**
 * @brief Writes to RF_SETUP register
 *
 * This writes a byte of data to the RF_SETUP register in
 * the NRF chip
 *
 * @param config is the value to write
 */
void nrf_write_rf_setup(uint8_t config);



/**
 * @brief Reads RF_CH register
 *
 * This reads the value currently in the RF_CH register
 * in the NRF chip
 *
 * @return is the value of the register
 */
uint8_t nrf_read_rf_ch();



/**
 * @brief Writes to RF_CH register
 *
 * This writes a byte of data to the RF_CH register in
 * the NRF chip
 *
 * @param config is the value to write
 */
void nrf_write_rf_ch(uint8_t channel);



/**
 * @brief Reads 5 bytes from TX_ADDR register
 *
 * This reads the 5 bytes that are in the TX_ADDR register
 * in the NRF chip
 *
 * @param address is a pointer to the returned array of bytes
 */
void nrf_read_TX_ADDR(uint8_t * address);



/**
 * @brief Writes 5 bytes to the TX_ADDR register
 *
 * This writes 5 bytes to the TX_ADDR register in the NRF chip
 *
 * @param tx_addr is a pointer to the 5 bytes to write
 */
void nrf_write_TX_ADDR(uint8_t * tx_addr);



/**
 * @brief Reads FIFO_STATUS register
 *
 * This reads the value of the FIFO_STATUS register
 * in the NRF chip
 *
 * @return is the value of the register
 */
uint8_t nrf_read_fifo_status();



/**
 * @brief Sends FLUSH_TX command
 *
 * This sends the command FLUSH_TX to the NRF chip to
 * empty the TX buffer
 *
 */
void nrf_flush_tx_fifo();



/**
* @brief Sends FLUSH_RX command
*
* This sends the command FLUSH_RX to the NRF chip to
* empty the RX buffer
 *
 */
void nrf_flush_rx_fifo();


#endif
