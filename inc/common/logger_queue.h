
/**
 * @file logger_queue.h
 * @brief Circular buffer implementation for logger
 *
 * This file contains a complete circular buffer implementation
 * from creation to deleting for the logger
 *
 * @author Zachary Asmussen
 * @date April 21st, 2018
 *
 */
#ifndef __LOGGERQUEUE_H__
#define __LOGGERQUEUE_H__

#include <stdint.h>
#include <stdlib.h>
#include "logger.h"

typedef struct {
   log_s * basePtr;
   log_s * head;
   log_s * tail;
   size_t length;
   size_t count;
} LB_t;

typedef enum {
  LB_SUCCESS,
  LB_NULL,
  LB_NO_LENGTH,
  LB_FULL,
  LB_EMPTY,
} LB_e;




/**
 * @brief Initializes the circular buffer
 *
 * This function creates our circular buffer by dynamically allocating
 * the LB structure, dynamically creates buffer array, and Initializes
 * the structure members
 *
 * @param buffPtr is the pointer to the circular buffer
 * @param length is the length of the buffer
 * @return is of enumeration type LB_e for certain error codes
 */
LB_e LB_init(LB_t ** buffPtr, uint32_t length);


/**
 * @brief Destroys a circular buffer
 *
 * This function frees all of the memory allocated at the circular buffer
 * initialization and sets any necessary pointers to NULL
 *
 * @param buffPtr is the pointer to the circular buffer
 * @return is of enumeration type LB_e for certain error codes
 */
LB_e LB_destroy(LB_t * buffPtr);


/**
 * @brief Adds an item to a circular buffer
 *
 * This function adds an item to our circular buffer from a pointer to that
 * buffer and data to be added
 *
 * @param buffPtr is the pointer to the circular buffer
 * @param data holds the value to be added into the buffer
 * @return is of enumeration type LB_e for certain error codes
 */
 LB_e LB_buffer_add_item(LB_t * buffPtr, log_s data);


/**
 * @brief Removes an item from a circular buffer
 *
 * This function removes an item from our circular buffer and saves this
 * value into a variable put into the function
 *
 * @param buffPtr is the pointer to the circular buffer
 * @param value is where we store the variable that we removed
 * @return is of enumeration type LB_e for certain error codes
 */
LB_e LB_buffer_remove_item(LB_t * buffPtr, log_s * value);


/**
 * @brief Checks if a buffer is full
 *
 * This function takes in a circular buffer and checks whether or not
 * the buffer is full
 *
 * @param buffPtr is the pointer to the circular buffer
 * @return is of enumeration type LB_e for certain error codes
 */
__attribute__((always_inline))inline LB_e LB_is_full(LB_t * buffPtr);

/**
 * @brief Checks if a buffer is empty
 *
 * This function takes in a circular buffer and checks whether or not
 * the buffer is empty
 *
 * @param buffPtr is the pointer to the circular buffer
 * @return is of enumeration type LB_e for certain error codes
 */
__attribute__((always_inline))inline LB_e LB_is_empty(LB_t * buffPtr);

#endif
