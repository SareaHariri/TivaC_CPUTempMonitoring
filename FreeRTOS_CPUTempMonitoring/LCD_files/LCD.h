/*
 *  LCD.h
 *
 *  LCD 16x2 driver.
 *  runs on tm4c123gh6pm using CODECOMPOSERSTUDIO
 *  ****************************************************
 *  WIRING:                                            *
 *                                                     *
 *  LCD         TIVA C                                 *
 *  ****************************************************
 *  D0-D7       PB0-PB7                                *
 *  E           PA7                                    *
 *  RW          PA6                                    *
 *  RS          PA5                                    *
 *                                                     *
 *******************************************************
 *  Created on: 26 NOV 2017                            *
 *  Sarea Al Hariri                                    *
 *  ****************************************************
 */

#ifndef LCD_H_
#define LCD_H_

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <Delay.h>

/********************************#define for the LCD pins*************************************/
#define LCD_DATA GPIO_PORTB_DATA_R
#define LCD_CTRL GPIO_PORTA_DATA_R
#define RS 0x20 /* PORTA BIT5 mask */
#define RW 0x40 /* PORTA BIT6 mask */
#define EN 0x80 /* PORTA BIT7 mask */
/********************************************************************************************/



/********************************** common commands  *****************************************/

#define SET_8BIT_DATA_2LINES 0X38
#define CLEAR_SCREEN 0X01
#define CURSOR_ON_2ND_LINE 0XC0
#define CURSOR_ON_HOME 0X02
#define CURSOR_INCREMENTING 0X04
#define CURSOR_DECREMENTING 0X06
#define CURSOR_POSITION_SH_LEFT 0X10
#define CURSOR_POSITION_SH_RIGHT 0X014
#define DISPLAY_SH_LEFT 0X18
#define DISPLAY_SH_RIGHT 0X1C
/********************************************************************************************/


/********************************** function prototypes *************************************/

/* Sending command to the LCD
 * input: uint8_t represent command number
 * output: non
 * return: void
 *
 */
void LCD_command(uint8_t command) ;
/********************************************************************************************/
/* Sending data to the LCD
 * input: uint8_t represent one character to diplay
 * output: non
 * return: void
 *
 */
void LCD_data(uint8_t data) ;
/********************************************************************************************/

/* this is the initialization function use PORTA,
 * PORTB for command and data respectivly.
 * the init function should be re-implement
 * if the the ports used is being changed.
 *
 * input: void
 * output: non
 * return: void
 *
 */
void LCD_init(void) ;
/********************************************************************************************/

/*
 * this is a simple function for testing
 * purposes. this will test the LCD_data()
 * LCD_command() and LCD_data_string() function
 * and display testing text on the LCD.
 *
 * input: void
 * output: void
 * return: void
 */
void LCD_test(void) ;
/********************************************************************************************/

#endif /* LCD_H_ */
