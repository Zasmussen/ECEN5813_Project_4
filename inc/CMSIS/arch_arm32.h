/**
 * @file arch_arm32.h
 * @brief Arm specific register manipulation functions and macros
 *
 * Definition of ARM register address values and endianness extraction
 * function used to determine ARM processor endianness setting
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */


#ifndef __ARCH_ARM32_H__
#define __ARCH_ARM32_H__

#include <stdint.h>

#define __SCB_ADDRESS (0xE000ED00)
#define __AIRCR_ADDRESS_OFFSET (0x0C)
#define __AIRCR (__SCB_ADDRESS+__AIRCR_ADDRESS_OFFSET)
#define __AIRCR_ENDIANNESS_OFFSET (0xF)
#define __AIRCR_ENDIANNESS_MASK (0x8000)

#define __CPUID_ADDRESS_OFFSET             ()
#define __CPUID                            ()
#define __CPUID_PART_NO_OFFSET             ()
#define __CPUID_PART_NO_MASK               ()
#define __CCR_ADDRESS_OFFSET               ()
#define __CCR                              ()
#define __CCR_STK_ALIGNMENT_OFFSET         ()
#define __CCR_STK_ALIGNMENT_MASK           ()
#define __CCR_UNALIGNED_ACCESS_TRAP_OFFSET ()
#define __CCR_UNALIGNED_ACCESS_TRAP_MASK   ()
#define __CCR_DIVIDE_BY_ZERO_TRAP_OFFSET   ()
#define __CCR_DIVIDE_BY_ZERO_TRAP_MASK     ()



/**
 * @brief Reads the AIRCR register and returns endianness of this read
 *
 * Extracts the ARM AIRCR register bit which tells the user what endianness
 * that the processor is in.
 *
 * @return is the bit value of the endianness mode of the AIRCR register
 */
uint32_t ARM32_AIRCR_get_endianness_setting();



/**
 * @brief Read the ARM CCR register to determine stack alignment
 *
 * The CCR register in the ARM processor contains a bit which tells the user
 * the stack alignment of the processor. As a 1 it is 8-byte aligned as a 0
 * it is 4-byte aligned
 *
 * @return a 1 means the processor is 8-byte aligned a 0 means 4-byte aligned
 */
__attribute__((always_inline)) uint32_t ARM32_CCR_get_stack_alignment();



/**
 * @brief Read the ARM CPUID register to determine the CPU part number
 *
 * The CPUID register in the ARM processor contains information to tell the user
 * the part number of the processor.
 *
 * @return the ID of the processor, our Cortex-M4 will return 0xC24
 */
__attribute__((always_inline)) uint32_t ARM32_CPUID_get_part_number();



/**
 * @brief Writes to the CCR to enable divide by zero trap
 *
 * This takes the ARM Configuration and Control Register and writes a 1 to the
 * enable divide by zero trap bit to capture divide by zero actions
 *
 * @return a 0 if successful and a 1 if an error
 */
__attribute__((always_inline)) uint32_t ARM32_CCR_enable_divide_by_zero_trap();



/**
 * @brief Writes to the CCR to enable unaligned access trap
 *
 * This takes the ARM Configuration and Control Register and writes a 1 to the
 * enable unaligned access trap bit
 *
 * @return a 0 if successful and a 1 if an error
 */
__attribute__((always_inline)) uint32_t ARM32_CCR_enable_unaligned_access_trap();



/**
 * @brief Creates a divide by zero to test trap
 *
 * This function makes a scenario to divide by zero to test our ARM trap
 *
 */
void ARM32_create_divide_by_zero_trap();



/**
 * @brief Creates an unaligned access to test trap
 *
 * This function makes a scenario to unaligned access to test our ARM trap
 *
 */
void ARM32_create_unaligned_access_trap();


#endif
