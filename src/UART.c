/**
 * @file UART.c
 * @brief UART configuration sending and receiving
 *
 * @author Zachary Asmussen
 * @date February 21st, 2018
 *
 */
#include "UART.h"
#include "platform.h"
#include "conversion.h"

extern CB_t * receive_buffer;

uint8_t UART_configure()
{
  /* Allow port manipulation */
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

  /* Set settings for port pins */
  PORTA_PCR1 = (PORT_PCR_MUX(PCR2) | PORT_PCR_IRQC(IRQC) | PORT_PCR_ISF(ISF1));
  PORTA_PCR2 = (PORT_PCR_MUX(PCR2) | PORT_PCR_IRQC(IRQC) | PORT_PCR_ISF(ISF1));

  /* Choose clock for UART0 */
  SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC(UARTCLR);
  SIM_SOPT2 |=  SIM_SOPT2_UART0SRC(FLLPLL);

  SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL(FLLPLLCLR);
  SIM_SOPT2 |=  SIM_SOPT2_PLLFLLSEL(FLLSEL);

  /* Choose TX and RX for UART0 */
  SIM_SOPT5 &= ~SIM_SOPT5_UART0RXSRC(RXCLR);
  SIM_SOPT5 |=  SIM_SOPT5_UART0RXSRC(RXSEL);

  SIM_SOPT5 &= ~SIM_SOPT5_UART0TXSRC(TXCLR);
  SIM_SOPT5 |=  SIM_SOPT5_UART0TXSRC(TXSEL);

  /* Allow clocking of UART 0 */
  SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

  /* Set Oversampling Ratio */
  UART0_C4 |= UART0_C4_OSR(OSR);

  /* Set BAUD and frame settings */
  UART0_BDH = UART0_BDH_SBR(CALCULATED_BDH)|UART0_BDH_SBNS(0)|UART0_BDH_RXEDGIE(0)|UART0_BDH_LBKDIE(0);
  UART0_BDL = UART0_BDL_SBR(CALCULATED_BDL);

  /* Set UART control settings */
  UART0_C1 = UART0_C1_PT(C1PT)|UART0_C1_PE(C1PE)|UART0_C1_ILT(C1ILT)|UART0_C1_WAKE(C1WAKE)|UART0_C1_M(C1M)|UART0_C1_RSRC(C1RSRC)|UART0_C1_DOZEEN(C1DOZEEN)|UART0_C1_LOOPS(C1LOOPS);
  UART0_C2 = UART0_C2_SBK(C2SBK)|UART0_C2_RWU(C2RWU)|UART0_C2_RE(C2RE)|UART0_C2_TE(C2TE)|UART0_C2_ILIE(C2ILIE)|UART0_C2_RIE(C2RIE)|UART0_C2_TCIE(C2TCIE)|UART0_C2_TIE(C2TIE);

  /* Enable interrupts */
  NVIC_EnableIRQ(UART0_IRQn);
  NVIC_ClearPendingIRQ(UART0_IRQn);
  __enable_irq();

  return 0;
}


uint8_t UART_send(uint8_t value)
{
  UART0_D = value;
  while(!((UART0_S1 & UART0_S1_TC_MASK)>>UART0_S1_TC_SHIFT));
  return 0;
}


uint8_t UART_send_n(uint8_t * value, size_t size)
{
  if(value == NULL || size <= 0)
  {
    return 1;
  }
  uint32_t i;
  for(i=0;i<size;i++)
  {
    UART0_D = *(value+i);
    while(!((UART0_S1 & UART0_S1_TC_MASK)>>UART0_S1_TC_SHIFT));
  }
  return 0;
}


uint8_t UART_receive(uint8_t * value)
{
  if(!value)
  {
    return 1;
  }

  while(!((UART0_S1 & UART0_S1_RDRF_MASK)>>UART0_S1_RDRF_SHIFT));
  *value = UART0_D;

  return 0;

}


uint8_t UART_receive_n(uint8_t * value, size_t size)
{
  if(!value)
  {
    return 1;
  }
  uint32_t i;
  for(i=0;i<size;i++)
  {
    while(!((UART0_S1 & UART0_S1_RDRF_MASK)>>UART0_S1_RDRF_SHIFT));
    *(value+i) = UART0_D;
  }
  return 0;
}


void UART0_IRQHandler()
{
  if((UART0_S1 & UART0_S1_RDRF_MASK))
  {
    uint8_t x = UART0_D;
    //x = my_atoi(&x,2,10);
    CB_buffer_add_item(receive_buffer,x);
  }

  if((UART0_S1 & UART_S1_TDRE_MASK))
  {

  }
  NVIC_ClearPendingIRQ(UART0_IRQn);
}
