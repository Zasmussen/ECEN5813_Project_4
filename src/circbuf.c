/**
 * @file circbuf.c
 * @brief Circular buffer function implementations
 *
 * This file contains a complete circular buffer implementation
 * implementing all functions defined in circbuf.h
 *
 * @author Zachary Asmussen
 * @date February 21st, 2018
 *
 */
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"
#include <stdio.h>
CB_e CB_init(CB_t ** buffPtr, uint32_t length)
{
  if(length <= 0)
  {
    return NO_LENGTH;
  }
  // Dynamically allocate CB struct

  (*buffPtr) = (CB_t *)malloc(sizeof(CB_t));

  if(buffPtr == NULL)
  {
    return CB_NULL;
  }
  // Dynamically allocate CB array space
  (*buffPtr)->basePtr = (uint8_t *) malloc(length);
  if((*buffPtr)->basePtr == NULL)
  {
    return CB_NULL;
  }
  // Initialize values in structure
  (*buffPtr)->head = (*buffPtr)->basePtr;
  (*buffPtr)->tail = (*buffPtr)->basePtr;
  (*buffPtr)->length = length;
  (*buffPtr)->count = 0;
  return SUCCESS;
}


CB_e CB_destroy(CB_t * buffPtr)
{
  if(buffPtr == NULL || buffPtr->basePtr == NULL)
  {
    return CB_NULL;
  }
  free(buffPtr->basePtr);
  buffPtr->basePtr = NULL;
  buffPtr->head = NULL;
  buffPtr->tail = NULL;
  free(buffPtr);
  buffPtr = NULL;
  return SUCCESS;
}


CB_e CB_buffer_add_item(CB_t * buffPtr, uint8_t data)
{
  if(buffPtr->basePtr == NULL || buffPtr->head == NULL || buffPtr->tail == NULL || buffPtr == NULL)
  {
    return CB_NULL;
  }
  if(buffPtr->count == buffPtr->length)
  {
    return CB_FULL;
  }

  // Check if first item added, should only happen once
  if((buffPtr->head == buffPtr->tail) && !(buffPtr->count))
  {
    *(buffPtr)->head = data;
    buffPtr->count++;
  }
  else  // Not first item
  {
    if(buffPtr->head == (buffPtr->basePtr + buffPtr->length - 1)) // Check if circular
    {
      buffPtr->head = buffPtr->basePtr;
    }
    else
    {

      buffPtr->head++;
    }

    *(buffPtr)->head = data;
    buffPtr->count++;
  }
  return SUCCESS;
}


CB_e CB_buffer_remove_item(CB_t * buffPtr, uint8_t * value)
{
  if(buffPtr->basePtr == NULL || buffPtr->head == NULL || buffPtr->tail == NULL || buffPtr == NULL)
  {
    return CB_NULL;
  }

  if(!(buffPtr->count))
  {
    return CB_EMPTY;
  }

  *(value) = *(buffPtr)->tail;
  *(buffPtr)->tail = 0;
  // Check for circular
  if(buffPtr->count == 1)
  {

  }
  else if(buffPtr->tail == (buffPtr->basePtr + buffPtr->length -1))
  {
    buffPtr->tail = buffPtr->basePtr;
  }
  else
  {
    buffPtr->tail++;
  }

  buffPtr->count--;
  return SUCCESS;
}


__attribute__((always_inline))inline CB_e CB_is_full(CB_t * buffPtr)
{
  if(buffPtr->basePtr == NULL || buffPtr->head == NULL || buffPtr->tail == NULL || buffPtr == NULL)
  {
    return CB_NULL;
  }
  return (buffPtr->count == buffPtr->length);
}


__attribute__((always_inline))inline CB_e CB_is_empty(CB_t * buffPtr)
{
  if(buffPtr->basePtr == NULL || buffPtr->head == NULL || buffPtr->tail == NULL || buffPtr == NULL)
  {
    return CB_NULL;
  }
  return (buffPtr->count == 0);
}
