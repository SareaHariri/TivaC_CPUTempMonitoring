/*
 * Tasks.h
 *
 * Author: Sarea Al Hariri
 */

#ifndef APPTASKS_H_
#define APPTASKS_H_

#pragma diag_push
#pragma CHECK_MISRA("none")
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/adc.h"
#include "inc/hw_memmap.h"
#include "uartstdio.h"
#include <delay.h>
#include <FreeRtos_files/FreeRTOS.h>
#include <FreeRtos_files/task.h>
#include <LCD_files/LCD.h>
#include <FreeRtos_files/queue.h>
#include <Nokia5110.h>



#pragma diag_pop

void GetTemp(void* PtoVoid);
void LCDWrite(void* PtoVoid) ;
static char* itoa(int num, char* str, int base) ;
static void reverse(char str[], int length) ;
static void swap(char *s1, char *s2);

#endif /* APPTASKS_H_ */
