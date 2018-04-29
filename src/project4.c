#include "project4.h"

LB_t * logBuff = NULL;

void project4()
{
#ifdef KL25Z
  GPIO_Configure();
  UART_configure();
#endif
#ifdef LOG
  log_init();
#endif
  log_s ret;
  LB_buffer_remove_item(logBuff,&ret);
  LOG_RAW_ITEM(&ret);
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
