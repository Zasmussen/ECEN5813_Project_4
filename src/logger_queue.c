/**
 * @file logger_queue.c
 * @brief Circular buffer for logger
 *
 * This file contains a complete circular buffer implementation
 * for the logger
 *
 * @author Zachary Asmussen
 * @date April 21st, 2018
 *
 */

#include "logger_queue.h"

LB_e LB_init(LB_t ** buffPtr, uint32_t length)
{
  if(length <= 0)
  {
    return NO_LENGTH;
  }
  // Dynamically allocate LB struct

  (*buffPtr) = (LB_t *)malloc(sizeof(LB_t));

  if(buffPtr == NULL)
  {
    return LB_NULL;
  }
  // Dynamically allocate LB array space
  (*buffPtr)->basePtr = (log_s *) malloc(length*sizeof(log_s));
  if((*buffPtr)->basePtr == NULL)
  {
    return LB_NULL;
  }
  // Initialize values in structure
  (*buffPtr)->head = (*buffPtr)->basePtr;
  (*buffPtr)->tail = (*buffPtr)->basePtr;
  (*buffPtr)->length = length;
  (*buffPtr)->count = 0;
  return SUCCESS;
}


LB_e LB_destroy(LB_t * buffPtr)
{
  if(buffPtr == NULL || buffPtr->basePtr == NULL)
  {
    return LB_NULL;
  }
  free(buffPtr->basePtr);
  buffPtr->basePtr = NULL;
  buffPtr->head = NULL;
  buffPtr->tail = NULL;
  free(buffPtr);
  buffPtr = NULL;
  return SUCCESS;
}


LB_e LB_buffer_add_item(LB_t * buffPtr, log_s data)
{
  if(buffPtr->basePtr == NULL || buffPtr->head == NULL || buffPtr->tail == NULL || buffPtr == NULL)
  {
    return LB_NULL;
  }
  if(buffPtr->count == buffPtr->length)
  {
    return LB_FULL;
  }

  // Check if first item added, should only happen once
  if((buffPtr->head == buffPtr->tail) && !(buffPtr->count))
  {
    (*(buffPtr)->head).log_id = data.log_id;
    (*(buffPtr)->head).module_id = data.module_id;
    (*(buffPtr)->head).timestamp = data.timestamp;
    (*(buffPtr)->head).length = data.length;
    (*(buffPtr)->head).payload = data.payload;
    (*(buffPtr)->head).checksum = data.checksum;
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

    (*(buffPtr)->head).log_id = data.log_id;
    (*(buffPtr)->head).module_id = data.module_id;
    (*(buffPtr)->head).timestamp = data.timestamp;
    (*(buffPtr)->head).length = data.length;
    (*(buffPtr)->head).payload = data.payload;
    (*(buffPtr)->head).checksum = data.checksum;
    buffPtr->count++;
  }
  return SUCCESS;
}


LB_e LB_buffer_remove_item(LB_t * buffPtr, log_s * value)
{
  if(buffPtr->basePtr == NULL || buffPtr->head == NULL || buffPtr->tail == NULL || buffPtr == NULL)
  {
    return LB_NULL;
  }

  if(!(buffPtr->count))
  {
    return LB_EMPTY;
  }

  value->log_id = (*(buffPtr)->tail).log_id;
  value->module_id = (*(buffPtr)->tail).module_id;
  value->timestamp = (*(buffPtr)->tail).timestamp;
  value->length = (*(buffPtr)->tail).length;
  value->payload = (*(buffPtr)->tail).payload;
  value->checksum = (*(buffPtr)->tail).checksum;
  (*(buffPtr)->tail).log_id = 0;
  (*(buffPtr)->tail).module_id = 0;
  (*(buffPtr)->tail).timestamp = 0;
  (*(buffPtr)->tail).length = 0;
  (*(buffPtr)->tail).payload = NULL;
  (*(buffPtr)->tail).checksum = 0;
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


__attribute__((always_inline))inline LB_e LB_is_full(LB_t * buffPtr)
{
  if(buffPtr->basePtr == NULL || buffPtr->head == NULL || buffPtr->tail == NULL || buffPtr == NULL)
  {
    return LB_NULL;
  }
  return (buffPtr->count == buffPtr->length);
}


__attribute__((always_inline))inline LB_e LB_is_empty(LB_t * buffPtr)
{
  if(buffPtr->basePtr == NULL || buffPtr->head == NULL || buffPtr->tail == NULL || buffPtr == NULL)
  {
    return LB_NULL;
  }
  return (buffPtr->count == 0);
}
