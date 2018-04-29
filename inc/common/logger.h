
/**
 * @file logger.h
 * @brief Functionality of logger
 *
 * This file contains a binary logger to log
 * important events on the system
 *
 * @author Zachary Asmussen
 * @date April 21st, 2018
 *
 */
#ifndef __LOGGER_H__
#define __LOGGER_H__


#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "conversion.h"
#include "UART.h"
#include "MKL25Z4.h"
#if defined(BBB) || defined(HOST)
#include <stdio.h>
#endif

#define LOG_RAW_DATA(x,y) (log_data(x,y))
#define LOG_RAW_STRING(x) (log_string(x))
#define LOG_RAW_INT(x)    (log_integer(x))
#define LOG_FLUSH()       (log_flush())
#define LOG_RAW_ITEM(x)   (log_item(x,0))
#define LOG_ITEM(x,y)     (log_item(x,y))
#define LOGGER_SIZE       256

typedef enum
{
  MOD_CIRCBUF = 1,
  MOD_CONVERSION,
  MOD_DATA,
  MOD_DEBUG,
  MOD_GPIO,
  MOD_LOGGER_QUEUE,
  MOD_LOGGER,
  MOD_MAIN,
  MOD_MEMORY,
  MOD_NORDIC,
  MOD_PROJECT1,
  MOD_PROJECT2,
  MOD_PROJECT3,
  MOD_PROJECT4,
  MOD_SPI,
  MOD_TESTS,
  MOD_UART
} module_e;


typedef enum
{
  SYSTEM_ID = 1,
  SYSTEM_VERSION,
  LOGGER_INITIALIZED,
  GPIO_INITIALIZED,
  SYSTEM_INITIALIZED,
  SYSTEM_HALTED,
  INFO,
  WARNING,
  ERROR,
  PROFILING_STARTED,
  PROFILING_RESULT,
  PROFILING_COMPLETED,
  DATA_RECEIVED,
  DATA_ANALYSIS_STARTED,
  DATA_ALPHA_COUNT,
  DATA_NUMERIC_COUNT,
  DATA_PUNCTUATION_COUNT,
  DATA_MISC_COUNT,
  DATA_ANALYSIS_COMPLETED,
  HEARTBEAT,
  CORE_DUMP
} log_e;

typedef struct
{
  log_e log_id;
  module_e module_id;
  uint32_t timestamp;
  uint32_t length;
  uint8_t * payload;
  uint32_t checksum;
} log_s;

#include "logger_queue.h"

void log_init();

uint8_t log_data(uint8_t * src, uint32_t length);

uint8_t log_string(uint8_t * src);

uint8_t log_integer(uint32_t number);

void log_flush();

uint8_t log_item(log_s * log, uint32_t size);


#endif
