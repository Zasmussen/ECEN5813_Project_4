
/**
 * @file circbuf.h
 * @brief Circular buffer implementation file
 *
 * This file contains a complete circular buffer implementation
 * from creation to deleting a uint8_t type circular buffer
 *
 * @author Zachary Asmussen
 * @date February 21st, 2018
 *
 */
#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__
#include <stdint.h>
#include <stdlib.h>

typedef struct {
   uint8_t * basePtr;
   uint8_t * head;
   uint8_t * tail;
   size_t length;
   size_t count;
} CB_t;

typedef enum {
  SUCCESS,
  CB_NULL,
  NO_LENGTH,
  CB_FULL,
  CB_EMPTY,
} CB_e;

/**
 * @brief Initializes the circular buffer
 *
 * This function creates our circular buffer by dynamically allocating
 * the CB structure, dynamically creates buffer array, and Initializes
 * the structure members
 *
 * @param buffPtr is the pointer to the circular buffer
 * @param length is the length of the buffer
 * @return is of enumeration type CB_e for certain error codes
 */
CB_e CB_init(CB_t ** buffPtr, uint32_t length);


/**
 * @brief Destroys a circular buffer
 *
 * This function frees all of the memory allocated at the circular buffer
 * initialization and sets any necessary pointers to NULL
 *
 * @param buffPtr is the pointer to the circular buffer
 * @return is of enumeration type CB_e for certain error codes
 */
CB_e CB_destroy(CB_t * buffPtr);


/**
 * @brief Adds an item to a circular buffer
 *
 * This function adds an item to our circular buffer from a pointer to that
 * buffer and data to be added
 *
 * @param buffPtr is the pointer to the circular buffer
 * @param data holds the value to be added into the buffer
 * @return is of enumeration type CB_e for certain error codes
 */
CB_e CB_buffer_add_item(CB_t * buffPtr, uint8_t data);


/**
 * @brief Removes an item from a circular buffer
 *
 * This function removes an item from our circular buffer and saves this
 * value into a variable put into the function
 *
 * @param buffPtr is the pointer to the circular buffer
 * @param value is where we store the variable that we removed
 * @return is of enumeration type CB_e for certain error codes
 */
CB_e CB_buffer_remove_item(CB_t * buffPtr, uint8_t * value);


/**
 * @brief Checks if a buffer is full
 *
 * This function takes in a circular buffer and checks whether or not
 * the buffer is full
 *
 * @param buffPtr is the pointer to the circular buffer
 * @return is of enumeration type CB_e for certain error codes
 */
__attribute__((always_inline))inline CB_e CB_is_full(CB_t * buffPtr);

/**
 * @brief Checks if a buffer is empty
 *
 * This function takes in a circular buffer and checks whether or not
 * the buffer is empty
 *
 * @param buffPtr is the pointer to the circular buffer
 * @return is of enumeration type CB_e for certain error codes
 */
__attribute__((always_inline))inline CB_e CB_is_empty(CB_t * buffPtr);

#endif
