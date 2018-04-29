#ifndef __PROJECT4_H__
#define __PROJECT4_H__

#include <stdint.h>
#include "memory.h"
#include "nordic.h"
#include "debug.h"
#include "platform.h"
#include "string.h"
#include "conversion.h"
#include "logger_queue.h"
#include "logger.h"


#ifdef KL25Z
#include "spi.h"
#include "GPIO.h"
#include "UART.h"
#include "core_cm0plus.h"
#endif

#if defined(BBB) || defined(HOST)
#include "stdio.h"
#include "time.h"
#endif

void project4();


#endif
