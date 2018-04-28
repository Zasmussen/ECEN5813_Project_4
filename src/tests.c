
#include "memory.h"
#include "conversion.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

void memory_test()
{
  size_t length = 100;
  uint8_t * src = (uint8_t *)reserve_words(length);
  uint8_t * dst = (uint8_t *)reserve_words(length);
  uint8_t * ret;
  ret = my_memmove(NULL,dst,length);
  assert_null(ret);

  ret = my_memmove(src,NULL,length);
  assert_null(ret);

  ret = my_memmove(NULL,NULL,length);
  assert_null(ret);

  uint32_t i;
  for(i=0;i<length;i++)
  {
    *(src+i) = i*2;
    *(dst+i) = i*3;
  }

  ret = my_memmove(src,dst,length);
  assert_non_null(ret);

  for(i=0;i<length;i++)
  {
    assert_int_equal(*(src+i),*(dst+i));
  }

  for(i=0;i<length;i++)
  {
    *(dst+i) = 100;
  }
  ret = my_memmove(dst,dst,length);
  assert_non_null(ret);
  for(i=0;i<length;i++)
  {
    assert_int_equal(*(dst+i),100);
  }

}

void conversion_test()
{
  uint8_t * ascii = reserve_words(1);
  uint8_t retuns;
  int32_t retsign;

  retsign = my_atoi(NULL,2,10);
  assert_int_equal(retsign,0xDEADBEEF);

  uint8_t zero[] = "0";
  retsign = my_atoi(zero,1,10);
  assert_int_equal(retsign,0);

  uint8_t max[] = "2147483648";
  retsign = my_atoi(max,10,10);
  assert_int_equal(retsign,2147483648);


  retuns = my_itoa(1,NULL,10);
  assert_int_equal(retuns,-1);

  retuns = my_itoa(0,ascii,10);
  assert_int_equal(*ascii,48);

  retuns = my_itoa(2147483648,ascii,10);
  assert_int_equal(retuns,10);

  free(ascii);
}
