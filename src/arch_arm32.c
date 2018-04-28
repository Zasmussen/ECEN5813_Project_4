/**
 * @file arch_arm32.c
 * @brief Implementation of Arm specific register functions
 *
 * Register maniupulation functions specific to an ARM system.
 * Currently extracts the ARM register which represents the
 * endianness of the processor.
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */
#include "arch_arm32.h"
#include <stdint.h>

__attribute__((always_inline)) inline uint32_t ARM32_AIRCR_get_endianness_setting()
{
    return ((__AIRCR & __AIRCR_ENDIANNESS_MASK) >> __AIRCR_ENDIANNESS_OFFSET);
}


__attribute__((always_inline)) inline uint32_t ARM32_CCR_get_stack_alignment()
{
  return 0;
}


__attribute__((always_inline)) inline uint32_t ARM32_CPUID_get_part_number()
{
  return 0;
}


__attribute__((always_inline)) inline uint32_t ARM32_CCR_enable_divide_by_zero_trap()
{
  return 0;
}


__attribute__((always_inline)) inline uint32_t ARM32_CCR_enable_unaligned_access_trap()
{
  return 0;
}


void ARM32_create_divide_by_zero_trap()
{
  return;
}


void ARM32_create_unaligned_access_trap()
{
  return;
}
