/**
 * @file memory.h
 * @brief Memory header defining all memory function prototypes
 *
 * Memory function definitions that manipulate memory across all
 * systems. Functions are implemented in .c file.
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__
#include <stdint.h>
#include <stdlib.h>
#ifdef KL25Z
#include "MKL25Z4.h"
#endif

extern uint8_t dma_done;

/**
 * @brief This function takes two byte pointers to be moved from src to dst in memory
 *
 * @param src is a byte pointer to the source of the memory move
 * @param dst is a byte pointer to the destination of the memory move
 * @param length is an integer of bytes to be copied in move
 * @return is a byte pointer to the destination of move
 */
uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length);



/**
 * @brief This function takes two byte pointers to be copied from src to dst in memory
 *
 * @param src is a byte pointer to the source of the memory copy
 * @param dst is a byte pointer to the destination of the memory copy
 * @param length is an integer of bytes to be copied in copy
 * @return is a byte pointer to the destination of copy
 */
uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length);



/**
 * @brief Sets memory of length specified from src pointer to value
 *
 * @param src is a byte pointer to the source of the memory set
 * @param length is an integer of bytes to be set to value
 * @param value is the byte value to set the memory to
 * @return is a byte pointer to the source of memset
 */
uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value);



/**
 * @brief Sets memory starting from source pointer of size length to zero
 *
 * @param src is a byte pointer to the source of memzero
 * @param length is an integer of bytes to be set to zero
 * @return is a byte pointer to the source of memzero
 */
uint8_t * my_memzero(uint8_t * src, size_t length);



/**
 * @brief Reverses the order of memory at src pointer of size length
 *
 * @param src is a byte pointer to the source of the reverse
 * @param length is an integer of bytes to be reversed
 * @return is a byte pointer to the source of reverse
 */
uint8_t * my_reverse(uint8_t * src, size_t length);



/**
 * @brief Allocates a length of words in dynamic memory
 *
 * @param length is an integer of bytes to be allocated
 * @return is a pointer to memory if successful or NULL if not
 */
void * reserve_words(size_t length);



/**
 * @brief Frees dynamic memory allocation from src
 *
 * @param src is a pointer to the source of the memory free
 * @return is a 0 if successful and a 1 if not
 */
uint8_t free_words(void * src);



/**
  * @brief Performs a memory move with DMA
  *
  * @param src is a byte pointer to the source of the move
  * @param dst is a byte pointer to the destination of the move
  * @param length is the amount of bytes to move
  * @param burst is the byte size of the DMA transfer bursts, either 1, 2, or 4 bytes
  * @return is a byte pointer to the destination of the move
  */
uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length, uint8_t burst);



/**
  * @brief Performs a memory set with DMA
  *
  * @param src is a byte pointer to the source of the set
  * @param length is the amount of bytes to set
  * @param value is the value to set the bytes to
  * @param burst is the byte size of the DMA transfer bursts, either 1, 2, or 4 bytes
  * @return is a byte pointer to the destination of the move
  */
uint8_t * memset_dma(uint8_t * src, size_t length, uint8_t value, uint8_t burst);

#endif
