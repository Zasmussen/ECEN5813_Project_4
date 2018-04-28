#include "project4.h"

LB_t * logBuff = NULL;

void project4()
{
  uint8_t * ptr = (uint8_t *)malloc(10);
  *ptr = 1;
  LB_init(&logBuff,256);
  log_s test;
  test.log_id = LOGGER_INITIALIZED;
  test.module_id = TEST;
  test.timestamp = 50;
  test.length = 50;
  test.payload = ptr;
  test.checksum = 50;
  log_item(&test,sizeof(test));
  log_s ret;
  LB_buffer_remove_item(logBuff,&ret);
  log_string((uint8_t*)"hello\0");
  printf("%d\n",ret.log_id);
}
