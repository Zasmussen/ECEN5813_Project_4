#include "project3.h"


void project3()
{
#ifdef SPI
  spi_test();
#endif
#ifdef PROF
  profiling();
#endif
  while(1)
  {

  }
}

void spi_test()
{
#ifdef KL25Z
  SPI_init();
  uint8_t config;
  uint32_t i;
  //uint8_t * r_address = (uint8_t *)malloc(6);
  uint8_t * w_address = (uint8_t *)malloc(6);
  for(i=0;i<5;i++)
  {
    *(w_address+i) = 0xDE;
  }

  //while(1)
  //{



  GPIO_Configure();
  UART_configure();
  uint8_t digits;
  uint8_t * send = (uint8_t *)reserve_words(10);
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = 0xFFFFFFFF;
  uint32_t length,start,end;

    SysTick->VAL = 0;
    start = SysTick->VAL;
    nrf_write_config(0x0A);
    config = nrf_read_config();
    end = SysTick->VAL;
    length = start-end;
    UART_send_n((uint8_t *)"*****PROFILING*****\r\n",21);
    UART_send_n((uint8_t *)"config write is ",16);
    digits = my_itoa(0x0A,send,16);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)"\n\r",2);
    UART_send_n((uint8_t *)"config read is ",15);
    digits = my_itoa(config,send,16);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)"\n\r",2);
    UART_send_n((uint8_t *)"config took ",12);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);


    SysTick->VAL = 0;
    start = SysTick->VAL;
    nrf_write_rf_setup(0x0B);
    config = nrf_read_rf_setup();
    end = SysTick->VAL;
    length = start-end;
    UART_send_n((uint8_t *)"rf_setup write is ",18);
    digits = my_itoa(0x0B,send,16);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)"\n\r",2);
    UART_send_n((uint8_t *)"rf_setup read is ",17);
    digits = my_itoa(config,send,16);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)"\n\r",2);
    UART_send_n((uint8_t *)"rf_setup took ",14);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);


    SysTick->VAL = 0;
    start = SysTick->VAL;
    nrf_write_rf_ch(0x0C);
    config = nrf_read_rf_ch();
    end = SysTick->VAL;
    length = start-end;
    UART_send_n((uint8_t *)"rf_ch write is ",15);
    digits = my_itoa(0x0C,send,16);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)"\n\r",2);
    UART_send_n((uint8_t *)"rf_ch read is ",14);
    digits = my_itoa(config,send,16);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)"\n\r",2);
    UART_send_n((uint8_t *)"rf_ch took ",11);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);

  //}
  #endif
}

void profiling()
{
#ifdef KL25Z
  GPIO_Configure();
  UART_configure();
  uint8_t digits;
  uint8_t * send = (uint8_t *)reserve_words(10);
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = 0xFFFFFFFF;
  uint32_t length,start,end;
#endif
  uint8_t * src = (uint8_t *)malloc(5100);
  uint8_t * dst = (uint8_t *)malloc(5100);
  reset_memory(src,dst);



/* Standard memmove */
  // 10 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  memmove(dst,src,10);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"*****PROFILING*****\r\n",21);
  UART_send_n((uint8_t *)"**memmove**\r\n",13);
  UART_send_n((uint8_t *)"Standard 10 Byte Memmove took ",30);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);


  // 100 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  memmove(dst,src,100);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);

  UART_send_n((uint8_t *)"Standard 100 Byte Memmove took ",31);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 1000 bytes
  #ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  memmove(dst,src,1000);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);

  UART_send_n((uint8_t *)"Standard 1000 Byte Memmove took ",32);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 5000 bytes
  #ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  memmove(dst,src,5000);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"Standard 5000 Byte Memmove took ",32);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);



/* My memmove */
  // 10 bytes
  #ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  my_memmove(src,dst,10);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"My 10 Byte Memmove took ",24);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 100 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  my_memmove(src,dst,100);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"My 100 Byte Memmove took ",25);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 1000 bytes
  #ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  my_memmove(src,dst,1000);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"My 1000 Byte Memmove took ",26);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 5000 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  my_memmove(src,dst,5000);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"My 5000 Byte Memmove took ",26);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);


#ifdef KL25Z
/* DMA memmove */
  // 10 bytes 1 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,10,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 10 Byte 1 Byte Burst Memmove took ",38);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 10 bytes 2 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,10,2);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 10 Byte 2 Byte Burst Memmove took ",38);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 10 bytes 4 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,10,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 10 Byte 4 Byte Burst Memmove took ",38);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 100 bytes 1 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,100,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 100 Byte 1 Byte Burst Memmove took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 100 bytes 2 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,100,2);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 100 Byte 2 Byte Burst Memmove took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 100 bytes 4 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,100,4);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 100 Byte 4 Byte Burst Memmove took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 1000 bytes 1 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,1000,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 1000 Byte 1 Byte Burst Memmove took ",40);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 1000 bytes 2 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,1000,2);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 1000 Byte 2 Byte Burst Memmove took ",40);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 1000 bytes 4 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,1000,4);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 1000 Byte 4 Byte Burst Memmove took ",40);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 5000 bytes 1 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,5000,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 5000 Byte 1 Byte Burst Memmove took ",40);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 5000 bytes 2 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,5000,2);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 5000 Byte 2 Byte Burst Memmove took ",40);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 5000 bytes 4 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memmove_dma(src,dst,5000,4);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 5000 Byte 4 Byte Burst Memmove took ",40);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
    UART_send_n((uint8_t *)"\n\r",2);
  #endif
  reset_memory(src,dst);
#endif


/* Standard memset */
  // 10 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  memset(src,0xFF,10);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"**memset**\r\n",12);
  UART_send_n((uint8_t *)"Standard 10 Byte Memset took ",29);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 100 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  memset(src,0xFF,100);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  UART_send_n((uint8_t *)"Standard 100 Byte Memset took ",30);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 1000 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  memset(src,0xFF,1000);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"Standard 1000 Byte Memset took ",31);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 5000 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  memset(src,0xFF,5000);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"Standard 5000 Byte Memset took ",31);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);


/* My memset */
  // 10 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  my_memset(src,10,0xFF);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"My 10 Byte Memset took ",23);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 100 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  my_memset(src,100,0xFF);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"My 100 Byte Memset took ",24);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 1000 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  my_memset(src,1000,0xFF);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"My 1000 Byte Memset took ",25);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

  // 5000 bytes
#ifdef KL25Z
  SysTick->VAL = 0;
  start = SysTick->VAL;
  my_memset(src,5000,0xFF);
  end = SysTick->VAL;
  length = start-end;
  UART_send_n((uint8_t *)"My 5000 Byte Memset took ",25);
  digits = my_itoa(length,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)" clock cycles\n\r",15);
#endif
  reset_memory(src,dst);

#ifdef KL25Z
/* DMA memset */
  // 10 bytes 1 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,10,0xFF,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 10 Byte 1 Byte Burst Memset took ",37);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 10 bytes 2 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,10,0xFF,2);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 10 Byte 2 Byte Burst Memset took ",37);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 10 bytes 4 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,10,0xFF,4);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 10 Byte 4 Byte Burst Memset took ",37);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 100 bytes 1 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,100,0xFF,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 100 Byte 1 Byte Burst Memset took ",38);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 100 bytes 2 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,100,0xFF,2);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 100 Byte 2 Byte Burst Memset took ",38);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 100 bytes 4 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,100,0xFF,4);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 100 Byte 4 Byte Burst Memset took ",38);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 1000 bytes 1 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,1000,0xFF,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 1000 Byte 1 Byte Burst Memset took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 1000 bytes 2 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,1000,0xFF,2);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 1000 Byte 2 Byte Burst Memset took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 1000 bytes 4 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,1000,0xFF,4);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 1000 Byte 4 Byte Burst Memset took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 5000 bytes 1 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,5000,0xFF,1);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 5000 Byte 1 Byte Burst Memset took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 5000 bytes 2 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,5000,0xFF,2);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 5000 Byte 2 Byte Burst Memset took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);

  // 5000 bytes 4 byte burst
  SysTick->VAL = 0;
  dma_done = 0;
  start = SysTick->VAL;
  memset_dma(src,5000,0xFF,4);
  while(!dma_done);
  end = SysTick->VAL;
  length = start-end;
  PRINTF("%d\n",length);
  #ifdef KL25Z
    UART_send_n((uint8_t *)"DMA 5000 Byte 4 Byte Burst Memset took ",39);
    digits = my_itoa(length,send,10);
    UART_send_n(send,digits-1);
    UART_send_n((uint8_t *)" clock cycles\n\r",15);
  #endif
  reset_memory(src,dst);
#endif
}

void reset_memory(uint8_t * src, uint8_t * dst)
{
  uint32_t i;
  for(i=0;i<5100;i++)
  {
    *(src+i) = 0xDE;
    *(dst+i) = 0xAD;
  }
}
