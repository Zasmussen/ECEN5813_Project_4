/**
 * @file memory.c
 * @brief Memory source implementing header functions
 *
 * Various implementations of memory manipulation functions.
 * Moves memory, copies memory, sets memory values, reverses
 * bytes, reserves heap space, and frees space.
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */
#include "memory.h"
#include <stdint.h>
#include <stdlib.h>
#define WORD_SIZE_IN_BYTES 4

uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length)
{
  if(src == NULL || length <= 0 || dst == NULL)
  {
    return NULL;
  }
  uint32_t i;
  if((src >= dst && src <= (dst+length))||(src >= dst && src <= (dst+length)))
  {
    uint8_t * tmp = (uint8_t*) malloc(length);
    for(i=0;i<length;i++)
    {
      *(tmp+i) = *(src+i);
    }
    for(i=0;i<length;i++)
    {
      *(dst+i) = *(tmp+i);
    }
    free(tmp);
  }
  else
  {
    for(i=0;i<length;i++)
    {
      *(dst+i) = *(src+i);
    }
  }

  return dst;
}

uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length)
{
  if(src == NULL || length <= 0)
  {
    return NULL;
  }

  uint32_t i;
  for(i=0;i<length;i++)
  {
    *(dst+i) = *(src+i);
  }
  return dst;
}

uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value)
{
  if(src == NULL || length <= 0)
  {
    return NULL;
  }

  uint32_t i;
  for(i=0;i<length;i++)
  {
    *(src+i) = value;
  }
  return src;
}

uint8_t * my_memzero(uint8_t * src, size_t length)
{
  if(src == NULL || length <= 0)
  {
    return NULL;
  }

  uint32_t i;
  for(i=0;i<length;i++)
  {
    *(src+i) = 0;
  }
  return src;
}

uint8_t * my_reverse(uint8_t * src, size_t length)
{
  if(src == NULL || length <= 0)
  {
    return NULL;
  }

  uint32_t i;
  for(i=0;i<(length/2);i++)
  {
    uint8_t tmp = *(src+i);
    *(src+i) = *(src+length-1-i);
    *(src+length-1-i) = tmp;
  }
  return src;
}

void * reserve_words(size_t length)
{
  if(length > 0)
  {
    return (void *) malloc(length*WORD_SIZE_IN_BYTES);
  }
  else
  {
    return NULL;
  }
}

uint8_t free_words(void * src)
{
  if(src == NULL)
  {
    return 1;
  }
  free(src);
  return 0;
}



uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length, uint8_t burst)
{
  #ifdef KL25Z
  if(src==NULL || dst==NULL || length==0 || !(burst==1||burst==2||burst==4))
  {
    return NULL;
  }
  DMA_SAR0 = DMA_SAR_SAR(src);
  DMA_DAR0 = DMA_DAR_DAR(dst);
  DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
  DMA_DCR0 = DMA_DCR_LCH2(1)         // Channel linked to channel 1
            |DMA_DCR_LCH1(2)         // Channel linked to channel 2
            |DMA_DCR_LINKCC(0)       // Channel linking disabled
            |DMA_DCR_D_REQ(1)        // ERQ bit cleared when BCR reaches 0
            |DMA_DCR_DMOD(0)         // Destination buffer disabled
            |DMA_DCR_SMOD(0)         // Source buffer disabled
            |DMA_DCR_START(0)        // Start disabled
            |DMA_DCR_DINC(1)         // Destination address increments
            |DMA_DCR_SINC(1)         // Source address increments
            |DMA_DCR_EADREQ(0)       // Asynchronous disabled
            |DMA_DCR_AA(0)           // No auto align
            |DMA_DCR_CS(0)           // Set to continuous until BCR = 0
            |DMA_DCR_ERQ(0)          // Peripheral ignored
            |DMA_DCR_EINT(1);        // Interrupts disabled
  NVIC_EnableIRQ(DMA0_IRQn);
  NVIC_ClearPendingIRQ(DMA0_IRQn);
  __enable_irq();

  switch(burst)
  {
    case 1:
      DMA_DCR0 |= DMA_DCR_SSIZE(1) | DMA_DCR_SSIZE(1);
      DMA_DCR0 |= DMA_DCR_DSIZE(1) | DMA_DCR_DSIZE(1);
    break;

    case 2:
      DMA_DCR0 |= DMA_DCR_SSIZE(2) | DMA_DCR_SSIZE(2);
      DMA_DCR0 |= DMA_DCR_DSIZE(2) | DMA_DCR_DSIZE(2);
    break;

    case 4:
      DMA_DCR0 |= DMA_DCR_SSIZE(0) | DMA_DCR_SSIZE(0);
      DMA_DCR0 |= DMA_DCR_DSIZE(0) | DMA_DCR_DSIZE(0);
    break;

    default:
      DMA_DCR0 |= DMA_DCR_SSIZE(1) | DMA_DCR_SSIZE(1);
      DMA_DCR0 |= DMA_DCR_DSIZE(1) | DMA_DCR_DSIZE(1);
  }
  DMA_DCR0 |= DMA_DCR_START(1);
  #endif
  return dst;
}



uint8_t * memset_dma(uint8_t * src, size_t length, uint8_t value, uint8_t burst)
{
  #ifdef KL25Z
  if(src==NULL || length==0 || !(burst==1||burst==2||burst==4))
  {
    return NULL;
  }
  DMA_SAR0 = DMA_SAR_SAR(&value);
  DMA_DAR0 = DMA_DAR_DAR(src);
  DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);
  DMA_DCR0 = DMA_DCR_LCH2(1)         // Channel linked to channel 1
            |DMA_DCR_LCH1(2)         // Channel linked to channel 2
            |DMA_DCR_LINKCC(0)       // Channel linking disabled
            |DMA_DCR_D_REQ(1)        // ERQ bit cleared when BCR reaches 0
            |DMA_DCR_DMOD(0)         // Destination buffer disabled
            |DMA_DCR_SMOD(0)         // Source buffer disabled
            |DMA_DCR_START(0)        // Start disabled
            |DMA_DCR_DINC(1)         // Destination address increments
            |DMA_DCR_SINC(0)         // Source address doesn't increment
            |DMA_DCR_EADREQ(0)       // Asynchronous disabled
            |DMA_DCR_AA(0)           // No auto align
            |DMA_DCR_CS(0)           // Set to continuous until BCR = 0
            |DMA_DCR_ERQ(0)          // Peripheral ignored
            |DMA_DCR_EINT(1);        // Interrupts disabled
  NVIC_EnableIRQ(DMA0_IRQn);
  NVIC_ClearPendingIRQ(DMA0_IRQn);
  __enable_irq();
  switch(burst)
  {
    case 1:
      DMA_DCR0 |= DMA_DCR_SSIZE(1) | DMA_DCR_SSIZE(1);
      DMA_DCR0 |= DMA_DCR_DSIZE(1) | DMA_DCR_DSIZE(1);
    break;

    case 2:
      DMA_DCR0 |= DMA_DCR_SSIZE(2) | DMA_DCR_SSIZE(2);
      DMA_DCR0 |= DMA_DCR_DSIZE(2) | DMA_DCR_DSIZE(2);
    break;

    case 4:
      DMA_DCR0 |= DMA_DCR_SSIZE(0) | DMA_DCR_SSIZE(0);
      DMA_DCR0 |= DMA_DCR_DSIZE(0) | DMA_DCR_DSIZE(0);
    break;

    default:
      DMA_DCR0 |= DMA_DCR_SSIZE(1) | DMA_DCR_SSIZE(1);
      DMA_DCR0 |= DMA_DCR_DSIZE(1) | DMA_DCR_DSIZE(1);
  }
  DMA_DCR0 |= DMA_DCR_START(1);
  #endif
  return src;
}
#ifdef KL25Z
void DMA0_IRQHandler()
{
  if(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK)
  {
    dma_done = 1;
    DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
  }
}
#endif
