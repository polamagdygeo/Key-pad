/**
  ******************************************************************************
  * @file           : port.h
  * @version        :
  * @brief          :
  ******************************************************************************
  ******************************************************************************
*/

#ifndef PORT_H_
#define PORT_H_

#include "dio.h"

/***************************************
 * Button
 ***************************************/

#define KEYPAD_PORT 			DIO_PORTC
#define KEYPAD_ROW_0			0
#define KEYPAD_ROW_1			1
#define KEYPAD_ROW_2			2
#define KEYPAD_ROW_3			3
#define KEYPAD_COL_0			4
#define KEYPAD_COL_1			5
#define KEYPAD_COL_2			6

/***************************************
 * GLCD
 ***************************************/

#define LCD_RS_PIN 				1
#define LCD_RW_PIN 				2
#define LCD_EN_PIN 				3

#define LCD_DATA_PORT 			DIO_PORTA
#define LCD_CTRL_PORT 			DIO_PORTB
#define LCD_DATA_PORT_MASK 		0xf0

#endif /* PORT_H_ */
