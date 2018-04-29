/**
 * @file conversion.h
 * @brief conversion header defining conversion function prototypes
 *
 * converion.h contains two functions; my_itoa and my_atoi. Both provided
 * a layer to allow users to convert either from integer to ascii strings
 * or vice versa.
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */
 #ifndef __CONVERSION_H__
 #define __CONVERSION_H__

#include <stdint.h>
#include <stdlib.h>

/**
  * Base macros used in project1.c
  */
#define BASE_16 16
#define BASE_10 10
#define WORD_SIZE_IN_BYTES 4
 /**
  * @brief Integer-to-ascii turns the 32-bit data into an ASCII string
  *
  * Taking a 32-bit number saved in data parameter and turns this into
  * an ascii string with a null terminator at the end. Providing base will
  * allow user to determine what base the string will be in.
  *
  * @param data represents the integer value to be converted
  * @param ptr is a byte pointer to the ASCII string
  * @param base is a base from 2 to 16 for conversion
  * @return is the size of the string located at ptr
  */
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);



/**
 * @brief Ascii-to-integer turns ascii strings into integer values
 *
 * Turns an ascii null terminated string saved in ptr parameter
 * and converts it into a 32-bit number. Must give base that the
 * string is in to allow correct conversion.
 *
 * @param ptr is the ascii string to be converted
 * @param digits is the converted integer number
 * @param base is the converted number's base
 * @return is the digits converted number
 */
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);

#endif
