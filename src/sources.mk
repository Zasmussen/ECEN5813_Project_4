# @file sources.mk
# @brief Additional make include to house source files
#
# This file is included in makefile to provide an abstraction
# to add in more source files elsewhere
#
# @author Zachary Asmussen
# @date January 30th, 2018
#
SRCS = main.c  conversion.c data.c debug.c project4.c memory.c  circbuf.c nordic.c logger.c logger_queue.c

# Add in KL25Z files if platform is set to it
ifeq ($(PLATFORM),KL25Z)
	SRCS += system_MKL25Z4.c startup_MKL25Z4.S arch_arm32.c GPIO.c UART.c spi.c project1.c
endif
ifeq ($(PLATFORM),HOST)
	SRCS += #tests.c
endif
