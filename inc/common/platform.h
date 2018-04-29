/**
 * @file platform.h
 * @brief
 *
 * printf functionality needs to be changed depending on if
 * the running architecture has that functionality.
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */


#ifndef __PLATFORM_H__
#define __PLATFORM_H__

// If debug printing is enabled
#ifdef VERBOSE
#define PRINTF printf
#endif

// If not replace printf's with nothing
#ifndef VERBOSE
#define PRINTF(...)
#endif


#endif
