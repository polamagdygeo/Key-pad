/*
 * LCD.c
 *
 * Created: 9/2/2016 3:41:57 PM
 *  Author: Pola Magdy
 */ 

#include "dio.h"
#include "port.h"
#include "LCD.h"

#define LCD_SET_DATA_MODE() 	DIO_WritePin(LCD_CTRL_PORT,LCD_RS_PIN,DIO_SET)
#define LCD_SET_CMD_MODE() 		DIO_WritePin(LCD_CTRL_PORT,LCD_RS_PIN,DIO_RESET)

#define LCD_SET_READ_MODE() 	DIO_WritePin(LCD_CTRL_PORT,LCD_RW_PIN,DIO_SET)
#define LCD_SET_WRITE_MODE() 	DIO_WritePin(LCD_CTRL_PORT,LCD_RW_PIN,DIO_RESET)

static void LCD_SendCommand(uint8_t Command);
static void LCD_WriteData(uint8_t DataOrCommand);
static void LCD_ToggleEnablePin(void);

void LCD_Init(void)
{	
	DIO_ConfigPin(LCD_CTRL_PORT,LCD_RS_PIN,DIO_OUTPUT);
	DIO_ConfigPin(LCD_CTRL_PORT,LCD_RW_PIN,DIO_OUTPUT);
	DIO_ConfigPin(LCD_CTRL_PORT,LCD_EN_PIN,DIO_OUTPUT);
	DIO_ConfigPort(LCD_DATA_PORT,LCD_DATA_PORT_MASK,DIO_OUTPUT);

	LCD_SET_WRITE_MODE();
	LCD_SET_CMD_MODE();
	LCD_WriteData(0x20);
	LCD_ToggleEnablePin();
	LCD_SendCommand(0x28); //function set
	LCD_SendCommand(0x0C); //disp on off
}

static void LCD_WriteData(uint8_t data)
{
	DIO_WritePort(LCD_DATA_PORT,LCD_DATA_PORT_MASK,data);
}

static void LCD_ToggleEnablePin(void)
{
	DIO_WritePin(LCD_CTRL_PORT,LCD_EN_PIN,DIO_SET);
	_delay_ms(1);
	DIO_WritePin(LCD_CTRL_PORT,LCD_EN_PIN,DIO_RESET);
	_delay_ms(1);
}


void LCD_WriteChar(uint8_t Byte)
{ 
	LCD_SET_DATA_MODE();
	LCD_WriteData(Byte);
	LCD_ToggleEnablePin(); 
	LCD_WriteData(Byte<<4);
	LCD_ToggleEnablePin();
}

static void LCD_SendCommand(uint8_t Command)
{ 
	LCD_SET_CMD_MODE();
	LCD_WriteData(Command);
	LCD_ToggleEnablePin();
	LCD_WriteData(Command<<4);
	LCD_ToggleEnablePin();
}

void LCD_WriteString(uint8_t* str,uint8_t len)
{
	uint8_t index;
	for(index = 0 ; index < len ; index++)
	{
		LCD_WriteChar(str[index]);
	}
}

void LCD_SetCursor(uint8_t x,uint8_t y)
{
	if (x==0)
	{
		LCD_SendCommand(0x80+y);
	}
	else if (x==1)
	{
		LCD_SendCommand(0xC0+y);
	}
}

void LCD_ClearScreen(void)
{
	LCD_SendCommand(0x01);

	LCD_SendCommand(0x28); //function set

	LCD_SendCommand(0x0C); //disp on off
}
