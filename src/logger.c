#include "logger.h"

extern LB_t * logBuff;

void log_init()
{
  LB_init(&logBuff,LOGGER_SIZE);
#ifdef KL25Z
  SIM_SCGC6 |= SIM_SCGC6_RTC(1);
  RTC_CR = RTC_CR_OSCE(1)| RTC_CR_UM(0)|RTC_CR_SUP(1)| RTC_CR_WPE(0)|RTC_CR_SWR(0);
  //UART_receive_n((uint8_t*)(&currenttime), 4);
  RTC_TSR = 1234;
  RTC_IER = RTC_IER_TSIE(1) | RTC_IER_TAIE(0) |RTC_IER_TOIE(0) | RTC_IER_TIIE(0);
  RTC_SR = RTC_SR_TCE(1);
#endif
  log_s log_log = ((log_s){LOGGER_INITIALIZED,MOD_LOGGER,0,0,NULL,(LOGGER_INITIALIZED^MOD_LOGGER^0^0)});
  LOG_ITEM(&log_log,sizeof(log_log));
}



uint8_t log_data(uint8_t * src, uint32_t length)
{
  if((length = 0) || !src)
  {
    return 1;
  }
#if defined(HOST) || defined(BBB)
  uint32_t i;
  for(i=0;i<length-1;i++)
  {
    printf("%d.",*(src+i));
    fflush(stdout);
  }
  printf("%d",*(src+i));
//  printf("\n");
#endif

#ifdef KL25Z
  uint32_t i;
  for(i=0;i<length-1;i++)
  {
    log_integer(*(src+i));
    UART_send('.');
  }
  log_integer(*(src+i));
#endif
  return 0;
}

uint8_t log_string(uint8_t * src)
{
#if defined(HOST) || defined(BBB)
  uint32_t i = 0;
  while(*(src+i))
  {
    printf("%c",*(src+i));
    i++;
  }
  printf("\n");
#endif

#ifdef KL25Z

#endif
  return 0;
}

uint8_t log_integer(uint32_t number)
{
#if defined(HOST) || defined(BBB)
  printf("%d",number);
#endif

#ifdef KL25Z
  uint8_t * ptr = (uint8_t *)reserve_words(10);
  uint32_t digits = my_itoa(number,ptr,10);
  UART_send_n(ptr,digits-1);
  free_words(ptr);
#endif
  return 0;
}

void log_flush()
{

}

uint8_t log_item(log_s * log, uint32_t size)
{
  if(size > 0)
  {
    log_s * log_item = (log_s *)malloc(size);
    log_item->log_id = log->log_id;
    log_item->module_id = log->module_id;
    log_item->timestamp = log->timestamp;
    log_item->length = log->length;
    log_item->payload = log->payload;
    log_item->checksum = log->checksum;
    LB_buffer_add_item(logBuff,*log_item);
  }
  else
  {
#if defined(HOST) || defined(BBB)
  printf("%d,%d,%d,",log->log_id,log->module_id,log->timestamp);
  log_data(log->payload,log->length);
  printf(",%d\n",log->checksum);
#endif

#ifdef KL25Z
  log_integer(log->log_id);
  UART_send(',');
  log_integer(log->module_id);
  UART_send(',');
  log_integer(log->timestamp);
  UART_send(',');
  log_data(log->payload,log->length);
  UART_send(',');
  log_integer(log->checksum);
  UART_send_n((uint8_t *)"\r\n",2);


#endif
  }
  return 0;
}
