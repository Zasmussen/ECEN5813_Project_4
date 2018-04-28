/**
 * @file main.c
 * @brief Main project file set for project control
 *
 * Main file which will currently run project1() function
 * and project2() function
 *
 * @author Zachary Asmussen
 * @date January 30th, 2018
 *
 */
#include "project1.h"
#include "project2.h"
#include "project3.h"
#include "project4.h"
#include <stdio.h>
int main(void)
{
  uint32_t i;
  #ifdef PROJECT1
    project1();
  #endif

  #ifdef PROJECT2
    project2();
  #endif

  #ifdef PROJECT3
    project3();
  #endif

  #ifdef PROJECT4
    project4();
  #endif



  while(1)
  {
    i++;
  }
}
