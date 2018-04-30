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
  log_s pro_log = ((log_s){DATA_ANALYSIS_STARTED,MOD_PROJECT4,0,0,NULL,(DATA_ANALYSIS_STARTED^MOD_PROJECT4^0^0)});
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
#ifdef ANALYSIS
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
#endif
  }

}


void dump_statistics()
{
#ifdef KL25Z
#ifdef LOG
    uint8_t * payload = malloc(10);
    *payload = alph;
    log_s dump_alph_log = ((log_s){DATA_ALPHA_COUNT,MOD_PROJECT2,0,1,payload,(DATA_ALPHA_COUNT^MOD_PROJECT2^0^1)});
    LOG_ITEM(&dump_alph_log,sizeof(dump_alph_log));
    *payload = numer;
    log_s dump_numeric_log = ((log_s){DATA_NUMERIC_COUNT,MOD_PROJECT2,0,1,payload,(DATA_NUMERIC_COUNT^MOD_PROJECT2^0^1)});
    LOG_ITEM(&dump_numeric_log,sizeof(dump_numeric_log));
    *payload = punc;
    log_s dump_punctuation_log = ((log_s){DATA_PUNCTUATION_COUNT,MOD_PROJECT2,0,1,payload,(DATA_PUNCTUATION_COUNT^MOD_PROJECT2^0^1)});
    LOG_ITEM(&dump_punctuation_log,sizeof(dump_punctuation_log));
    *payload = misc;
    log_s dump_misc_log = ((log_s){DATA_MISC_COUNT,MOD_PROJECT2,0,1,payload,(DATA_MISC_COUNT^MOD_PROJECT2^0^1)});
    LOG_ITEM(&dump_misc_log,sizeof(dump_misc_log));
    free(payload);
#endif
	// uint8_t * send = (uint8_t *)reserve_words(10);;
  // uint8_t digits;
  // UART_send_n((uint8_t *)"Statistics\n\r",12);
  // UART_send_n((uint8_t *)"-----------\n\r",13);
  // UART_send_n((uint8_t *)"Alphabetic\n\r",12);
  // digits = my_itoa(alph,send,10);
  // UART_send_n(send,digits-1);
  // UART_send_n((uint8_t *)"\n\r\n\r",4);
  //
  // UART_send_n((uint8_t *)"Numeric\n\r",9);
  // digits = my_itoa(numer,send,10);
  // UART_send_n(send,digits-1);
  // UART_send_n((uint8_t *)"\n\r\n\r",4);
  //
  // UART_send_n((uint8_t *)"Punctuation\n\r",13);
  // digits = my_itoa(punc,send,10);
  // UART_send_n(send,digits-1);
  // UART_send_n((uint8_t *)"\n\r\n\r",4);
  //
  // UART_send_n((uint8_t *)"Miscellaneous\n\r",15);
  // digits = my_itoa(misc,send,10);
  // UART_send_n(send,digits-1);
  // UART_send_n((uint8_t *)"\n\r\n\r",4);
  // free(send);
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
