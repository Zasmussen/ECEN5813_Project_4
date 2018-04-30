#include "project4.h"
#define RECEIVE_SIZE    128

LB_t * logBuff = NULL;
CB_t * receive_buffer = NULL;
uint32_t alph = 0;
uint32_t numer = 0;
uint32_t punc = 0;
uint32_t misc = 0;

void project4()
{
#ifdef LOG
  log_init();
#endif
#ifdef KL25Z
  GPIO_Configure();
  UART_configure();
#endif
#ifdef ANALYSIS
  CB_init(&receive_buffer,RECEIVE_SIZE);
  LOG_s pro_log = ((log_s){DATA_ANALYSIS_STARTED,MOD_PROJECT4,0,0,NULL,(DATA_ANALYSIS_STARTED^MOD_PROJECT4^0^0)});
  LOG_ITEM(&pro_log,sizeof(pro_log));
#endif
  log_s ret;
  uint8_t error;
  while(1)
  {
#ifdef LOG
    error = LB_buffer_remove_item(logBuff,&ret);
    if(!error)
    {
      LOG_RAW_ITEM(&ret);
    }
#endif
    uint8_t character;
    error = CB_buffer_remove_item(receive_buffer,&character);
    if(!error)
    {
      if(character == 0x1b)
      {
        dump_statistics();
        //return;
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



  // uint8_t * ptr = (uint8_t *)malloc(10);
  // *ptr = 1;
  // *(ptr+1) = 2;
  // *(ptr+2) = '\0';
  // log_init();
  // log_s test;
  // test.log_id = LOGGER_INITIALIZED;
  // test.module_id = MOD_LOGGER;
  // test.timestamp = 50;
  // test.length = 2;
  // test.payload = ptr;
  // test.checksum = 50;
  // LOG_RAW_ITEM(&test);
  //LOG_RAW_INT(3);
  //log_s ret;
  //LB_buffer_remove_item(logBuff,&ret);
  //log_string((uint8_t*)"hello\0");
  //printf("%d\n",ret.log_id);
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
