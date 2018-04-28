/**
 * @file data.c
 * @brief data source file implementing data header functions
 *
 * Functions defined in debug.h are implemented here. They provided
 * information on the size of various data types and endianness of
 * the current system
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "memory.h"
#include "data.h"
#include "platform.h"

void print_cstd_type_sizes()
{
  size_t tmp;
  tmp = sizeof(char);
  PRINTF("sizeof(char) = %zu\n", tmp);
  tmp = sizeof(short);
  PRINTF("sizeof(short) = %zu\n", tmp);
  tmp = sizeof(long);
  PRINTF("sizeof(long) = %zu\n", tmp);
  tmp = sizeof(double);
  PRINTF("sizeof(double) = %zu\n", tmp);
  tmp = sizeof(float);
  PRINTF("sizeof(float) = %zu\n", tmp);
  tmp = sizeof(unsigned char);
  PRINTF("sizeof(unsigned char) = %zu\n", tmp);
  tmp = sizeof(unsigned int);
  PRINTF("sizeof(unsigned int) = %zu\n", tmp);
  tmp = sizeof(unsigned long);
  PRINTF("sizeof(unsigned long) = %zu\n", tmp);
  tmp = sizeof(signed char);
  PRINTF("sizeof(signed char) = %zu\n", tmp);
  tmp = sizeof(signed int);
  PRINTF("sizeof(signed int) = %zu\n", tmp);
  tmp = sizeof(signed long);
  PRINTF("sizeof(signed long) = %zu\n", tmp);
}

void print_stdint_type_sizes()
{
  size_t tmp;
  tmp = sizeof(int8_t);
  PRINTF("sizeof(int8_t) = %zu\n", tmp);
  tmp = sizeof(uint8_t);
  PRINTF("sizeof(uint8_t) = %zu\n", tmp);
  tmp = sizeof(int16_t);
  PRINTF("sizeof(int16_t) = %zu\n", tmp);
  tmp = sizeof(uint16_t);
  PRINTF("sizeof(uint16_t) = %zu\n", tmp);
  tmp = sizeof(int32_t);
  PRINTF("sizeof(int32_t) = %zu\n", tmp);
  tmp = sizeof(uint_fast8_t);
  PRINTF("sizeof(uint_fast8_t) = %zu\n", tmp);
  tmp = sizeof(uint_fast16_t);
  PRINTF("sizeof(uint_fast16_t) = %zu\n", tmp);
  tmp = sizeof(uint_fast32_t);
  PRINTF("sizeof(uint_fast32_t) = %zu\n", tmp);
  tmp = sizeof(uint_least8_t);
  PRINTF("sizeof(uint_least8_t) = %zu\n", tmp);
  tmp = sizeof(uint_least16_t);
  PRINTF("sizeof(uint_least16_t) = %zu\n", tmp);
  tmp = sizeof(uint_least32_t);
  PRINTF("sizeof(uint_least32_t) = %zu\n", tmp);
  tmp = sizeof(size_t);
  PRINTF("sizeof(size_t) = %zu\n", tmp);
  tmp = sizeof(ptrdiff_t);
  PRINTF("sizeof(ptrdiff_t) = %zu\n", tmp);

}

void print_pointer_sizes()
{
  size_t tmp;
  tmp = sizeof(char *);
  PRINTF("sizeof(char *) = %zu\n", tmp);
  tmp = sizeof(short *);
  PRINTF("sizeof(short *) = %zu\n", tmp);
  tmp = sizeof(int *);
  PRINTF("sizeof(int *) = %zu\n", tmp);
  tmp = sizeof(long *);
  PRINTF("sizeof(long *) = %zu\n", tmp);
  tmp = sizeof(double *);
  PRINTF("sizeof(double *) = %zu\n", tmp);
  tmp = sizeof(float *);
  PRINTF("sizeof(float *) = %zu\n", tmp);
  tmp = sizeof(void *);
  PRINTF("sizeof(void *) = %zu\n", tmp);
  tmp = sizeof(int8_t *);
  PRINTF("sizeof(int8_t *) = %zu\n", tmp);
  tmp = sizeof(int16_t*);
  PRINTF("sizeof(int16_t *) = %zu\n", tmp);
  tmp = sizeof(int32_t *);
  PRINTF("sizeof(int32_t *) = %zu\n", tmp);
  tmp = sizeof(char **);
  PRINTF("sizeof(char **) = %zu\n", tmp);
  tmp = sizeof(int **);
  PRINTF("sizeof(int **) = %zu\n", tmp);
  tmp = sizeof(void **);
  PRINTF("sizeof(void **) = %zu\n", tmp);

}

int32_t swap_data_endianness(uint8_t * data, size_t type_length)
{
  if(data==NULL || type_length <= 0)        //Protection against NULL pointer or malformed array length
  {
    return SWAP_ERROR;
  }

  uint32_t i;
  for(i=0;i<(type_length/2);i++)
  {
    uint8_t tmp = *(data+i);
    *(data+i) = *(data+type_length-1-i);
    *(data+type_length-1-i) = tmp;
  }
  return SWAP_NO_ERROR;
}

uint32_t determine_endianness()
{
  uint32_t data = 0x12345678;
  uint8_t * ptr = (uint8_t *)&data;
  if(*ptr == 0x78)
  {
    return LITTLE_ENDIAN;
  }
  else if(*ptr == 0x12)
  {
    return BIG_ENDIAN;
  }
  else
  {
    return -1;
  }
}
