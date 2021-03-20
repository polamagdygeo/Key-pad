/*
 * LCD.h
 *
 * Created: 9/2/2016 3:41:39 PM
 *  Author: Pola Magdy
 */ 

#ifndef LCD_H_
#define LCD_H_

#include "main.h"

void LCD_Init(void);
void LCD_WriteChar(uint8_t Byte);
void LCD_WriteString(uint8_t* str,uint8_t len);
void LCD_SetCursor(uint8_t row,uint8_t col);
void LCD_ClearScreen(void);

#endif /* LCD_H_ */
