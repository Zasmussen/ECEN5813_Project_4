#include "logger.h"

extern LB_t * logBuff;

uint8_t log_data(uint8_t * src, uint32_t length)
{
#if defined(HOST) || defined(BBB)
  uint32_t i;
  for(i=0;i<length;i++)
  {
    printf("%d",*(src+i));
  }
  printf("\n");
#endif

#ifdef KL25Z

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
  printf("%d\n",number);
#endif

#ifdef KL25Z
  uint8_t * ptr = (uint8_t *)reserve_words(10);
  uint32_t digits = my_itoa(number,ptr,10);
  uint32_t i;
  UART_send_n(ptr,digits-1);
#endif
  return 0;
}

void log_flush()
{

}

uint8_t log_item(log_s * log, uint32_t size)
{
  log_s * log_item = (log_s *)malloc(size);
  log_item->log_id = log->log_id;
  log_item->module_id = log->module_id;
  log_item->timestamp = log->timestamp;
  log_item->length = log->length;
  log_item->payload = log->payload;
  log_item->checksum = log->checksum;
  LB_buffer_add_item(logBuff,*log_item);
#if defined(HOST) || defined(BBB)

#endif

#ifdef KL25Z

#endif
  return 0;
}
