#include "platform.h"
#include "project2.h"
#include "memory.h"
#include "conversion.h"
#include "debug.h"
#include "GPIO.h"
#include "circbuf.h"
#include "UART.h"
#ifdef HOST
#include <stdio.h>
#endif

CB_t * receive_buffer = NULL;
uint32_t alph = 0;
uint32_t numer = 0;
uint32_t punc = 0;
uint32_t misc = 0;

#define RECEIVE_SIZE    128
void project2()
{
#ifdef KL25Z
  GPIO_Configure();
  UART_configure();
#endif

  CB_init(&receive_buffer,RECEIVE_SIZE);
  while(1)
  {
#ifdef KL25Z
    while(!receive_buffer->count);
    uint8_t character;
    CB_buffer_remove_item(receive_buffer,&character);
#endif

    if(character == 0x1b)
    {
      dump_statistics();
      return;
    }
    if((character >= 65 && character <= 90) || (character >= 97 && character <= 122))
    {
      alph++;
    }
    else if(character >= 48 && character <= 57)
    {
      numer++;
    }
    else if((character >= 33 && character <= 47) || (character >= 58 && character <= 64) || (character >= 91 && character <= 96) || (character >= 123 && character <= 126))
    {
      punc++;
    }
    else
    {
      misc++;
    }
  }
}

void dump_statistics()
{
#ifdef KL25Z
	uint8_t * send = (uint8_t *)reserve_words(10);;
  uint8_t digits;
  UART_send_n((uint8_t *)"Statistics\n\r",12);
  UART_send_n((uint8_t *)"-----------\n\r",13);
  UART_send_n((uint8_t *)"Alphabetic\n\r",12);
  digits = my_itoa(alph,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)"\n\r\n\r",4);

  UART_send_n((uint8_t *)"Numeric\n\r",9);
  digits = my_itoa(numer,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)"\n\r\n\r",4);

  UART_send_n((uint8_t *)"Punctuation\n\r",13);
  digits = my_itoa(punc,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)"\n\r\n\r",4);

  UART_send_n((uint8_t *)"Miscellaneous\n\r",15);
  digits = my_itoa(misc,send,10);
  UART_send_n(send,digits-1);
  UART_send_n((uint8_t *)"\n\r\n\r",4);
  free(send);
#endif
#ifdef HOST
  PRINTF("Statistics\n");
  PRINTF("----------\n");

  PRINTF("Alphabetic\n%d\n",alph);

  PRINTF("Numeric\n%d\n",numer);

  PRINTF("Punctuation\n%d\n",punc);

  PRINTF("Miscellaneous\n%d\n",misc);
#endif

}
