/**
 * @file conversion.c
 * @brief conversion source file implementing conversion header functions
 *
 * Conversion functions including ATOI and ITOA user implemented versions
 * Used to convert integers to ascii or vice versa
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */
#include "conversion.h"
#include <stdint.h>
#include <stdlib.h>
#include "debug.h"
#include "memory.h"


uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
  if(base <= 1 || base > 16 || ptr == NULL)
  {
    return -1;
  }
  if(data == 0)
  {
    *ptr = data+48;
    *(ptr+1) = '\0';
    return 2;
  }
  uint32_t i = 0;
  uint8_t neg = 0;
  if(data < 0)
  {
    *(ptr) = '-';
    ptr++;
    data = -data;
    neg++;
  }
  while(data)
  {
    *(ptr+i) = data%base;
    data = data/base;
    i++;
  }
  my_reverse(ptr, i);
  uint32_t j;
  for(j=0;j<i;j++)
  {
    if(*(ptr+j)<10)
    {
      *(ptr+j) = *(ptr+j)+48;
    }
    else
    {
      *(ptr+j) = *(ptr+j)+55;
    }
  }
  *(ptr+j) = '\0';
  return j+neg+1;
}

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base)
{
  if(base <= 1 || base > 16 || ptr == NULL)
  {
    return 0xDEADBEEF;
  }
  uint32_t i;
  uint8_t neg = 0;
  digits--;
  if(*ptr == '-')
  {
    ptr++;
    neg++;
    digits--;
  }
  uint8_t * arr = (uint8_t*)reserve_words(digits/*WORD_SIZE_IN_BYTES*/);
  for(i=0;i<digits;i++)
  {
    if(*(ptr+i) < 58)
    {
      *(arr+i) = *(ptr+i)-48;
    }
    else
    {
      *(arr+i) = *(ptr+i)-55;
    }
  }
  print_array(arr, i);
  uint32_t expo = 1;
  uint32_t value = 0;
  uint32_t j,jj;
  uint32_t ii = i-1;
  for(j=0;j<i;j++)
  {
    for(jj=0;jj<ii;jj++)
    {
      expo *= base;
    }
    ii--;
    value += expo*(*(arr+j));

    expo = 1;
  }
  free(arr);
  if(neg)
  {
    value = -value;
  }
  return value;
}
