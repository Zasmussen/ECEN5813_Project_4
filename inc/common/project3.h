#ifndef __PROJECT3_H__
#define __PROJECT3_H__

#include <stdint.h>
#include "memory.h"
#include "nordic.h"
#include "debug.h"
#include "platform.h"
#include "string.h"
#include "conversion.h"
#ifdef KL25Z
#include "spi.h"
#include "GPIO.h"
#include "UART.h"
#include "core_cm0plus.h"
#endif
#ifdef BBB
#include "stdio.h"
#include "time.h"
#endif

void project3();
void spi_test();
void profiling();
void reset_memory(uint8_t * src, uint8_t * dst);
uint8_t dma_done;

#endif
