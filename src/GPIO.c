/**
 * @file GPIO.c
 * @brief KL25Z GPIO abstraction layer function implementations
 *
 * Here we abstract the use of General Purpose Input Output registers
 * to control I/O pins on the KL25Z. This implements the functions
 * defined in GPIO.h
 *
 * @author Zachary Asmussen
 * @date February 21st, 2018
 *
 */

#include "GPIO.h"
#include "MKL25Z4.h"

void GPIO_Configure()
{
  SIM_SCGC5 |= (SIM_SCGC5_PORTB_MASK);
  SIM_SCGC5 |= (SIM_SCGC5_PORTD_MASK);

  PORTB_PCR18 |= PORT_PCR_MUX(1);
  PORTB_PCR19 |= PORT_PCR_MUX(1);
  PORTD_PCR1 |= PORT_PCR_MUX(1);

  GPIOB->PDDR |= (RGB_RED_PIN);
  GPIOB->PDDR |= (RGB_GREEN_PIN);
  GPIOD->PDDR |= (RGB_BLUE_PIN);

  GPIOB->PDOR |= (RGB_RED_PIN);
  GPIOB->PDOR |= (RGB_GREEN_PIN);
  GPIOD->PDOR |= (RGB_BLUE_PIN);
  return;
}


void Toggle_Red_LED()
{
  GPIOB->PDOR ^= RGB_RED_PIN;
  return;
}


void PORTB_Set(uint8_t bit_num)
{
  GPIOB->PSOR |= (1 << bit_num);
  return;
}


void PORTD_Set(uint8_t bit_num)
{
  GPIOD->PSOR |= (1 << bit_num);
  return;
}


void PORTB_Clear(uint8_t bit_num)
{
  GPIOB->PCOR |= (1 << bit_num);
  return;
}


void PORTD_Clear(uint8_t bit_num)
{
  GPIOD->PCOR |= (1 << bit_num);
  return;
}


void PORTB_Toggle(uint8_t bit_num)
{
  GPIOB->PTOR |= (1 << bit_num);
  return;
}


void PORTD_Toggle(uint8_t bit_num)
{
  GPIOD->PTOR |= (1 << bit_num);
  return;
}


void GPIO_nrf_init()
{
  /* Allow port manipulation */
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

  /* Set MISO, MOSI, SCK, and PCS0 pins */
  PORTC_PCR4 |= (PORT_PCR_MUX(1) | PORT_PCR_IRQC(0));  // PTC4 - SPI0_PCS0 ALT2
  PORTC_PCR5 |= (PORT_PCR_MUX(2) | PORT_PCR_IRQC(0));  // PTC5 - SPI0_SCK ALT2
  PORTC_PCR6 |= (PORT_PCR_MUX(2) | PORT_PCR_IRQC(0));  // PTC6 - SPI0_MOSI ALT2
  PORTC_PCR7 |= (PORT_PCR_MUX(2) | PORT_PCR_IRQC(0));  // PTC7 - SPI0_MISO ALT2

  PORTC_PCR0 |= (PORT_PCR_MUX(1) | PORT_PCR_IRQC(0));  // PTC4 - SPI0_PCS0 ALT2
  /* SS pin setup */
  GPIOC->PDDR |= (1<<4);
  GPIOC->PDOR |= (1<<4);

  /* CE pin setup */
  GPIOC->PDDR |= (1<<0);
  GPIOC->PDOR &= ~(1<<0);


}
