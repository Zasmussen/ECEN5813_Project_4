/**
 * @file data.h
 * @brief Functions and macros to define data info on system
 *
 * Since multiple systems are run all in this same project, data.h
 * functions allow user to see sizes of different data types.
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */


#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>
#include <stdlib.h>

// Endianness macro definitions
#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1
#define SWAP_NO_ERROR 0
#define SWAP_ERROR -1

// Protection against unused variable
#if defined (__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif


/**
 * @brief Prints the architecture specific sizes of all C standard data types
 *
 * Prints various C standard types which are specific to which system is run.
 * If the system has printf functionality it will be printed there. Otherwise,
 * (such as in an embedded system) the variable tmp can be debugged to determine
 * size of type
 *
 */
void print_cstd_type_sizes();



/**
 * @brief Prints the sizes of all standard integer types

 * Prints various standard integer types which ideally are not different across systems.
 * If the system has printf functionality it will be printed there. Otherwise,
 * (such as in an embedded system) the variable tmp can be debugged to determine
 * size of type
 *
 */
void print_stdint_type_sizes();



/**
 * @brief Prints the sizes of various different pointer types
 *
 * Prints various C standard pointer sizes across any system using the function.
 * If the system has printf functionality it will be printed there. Otherwise,
 * (such as in an embedded system) the variable tmp can be debugged to determine
 * size of type
 *
 */
void print_pointer_sizes();



/**
 * @brief Swaps the endianness of data provided a pointer to its start
 *
 * Given a byte controlled data pointer, this function swaps how the print_array
 * of bytes are stored in memory to flip the endianness of the data.
 *
 * @param data is a byte pointer to the start of data
 * @param type_length is the size of the data to be swapped
 * @return is a 0 if successful and a -1 if not
 */
int32_t swap_data_endianness(uint8_t * data, size_t type_length);



/**
 * @brief Determines the endianness of the system
 *
 * This function creates its own variable of 32 bits and determines how
 * the running architecture has saved it in memory to determine the
 * endianness of the system.
 *
 * @return is a 1 if big endian, 0 if little endian, and -1 if there is an error
 */
uint32_t determine_endianness();

#endif
