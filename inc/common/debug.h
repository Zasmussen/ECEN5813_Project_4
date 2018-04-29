/**
 * @file debug.h
 * @brief debug header defining debug function prototypes
 *
 * Function declarations of debug functions for HOST or BBB
 * platforms. VERBOSE definition determines if functions output
 * prints.
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */
 #ifndef __DEBUG_H__
 #define __DEBUG_H__

#include <stdint.h>
#include <stdlib.h>
 /**
  * @brief print_array prints the hex values pointed in memory of size length
  *
  * @param start is a byte pointer to the start of print pointing to a memory location
  * @param length is the size of bytes to print
  */
void print_array(uint8_t * start, uint32_t length);


/**
 * @brief print_string prints the string that start points to
 *
 * Added in a print_string function for debugging strings on the HOST machine
 * or BBB. This function prints characters for each byte and not integers.
 *
 * @param start is a byte pointer to the start of print pointing to a memory location
 * @param length is the size of bytes to print
 */
void print_string(uint8_t * start, uint32_t length);
#endif
