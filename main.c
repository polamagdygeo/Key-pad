/*
 * main.c
 *
 * Created:
 *  Author: Pola Magdy
 */


#include "main.h"
#include "OS.h"
#include "LCD.h"
#include "keypad.h"
#include "dio.h"

void app(void)
{
	char pressed_key = Keypad_GetChar();

	if(pressed_key != 0)
	{
		LCD_ClearScreen();
		LCD_SetCursor(0,0);
		LCD_WriteChar(pressed_key);
		PORTD ^= 1 << 7;
	}
}

int main(void)
{
	DDRD |= 1 << 7;
	Keypad_Init();
	LCD_Init();
	OS_AddTask(1,app,5,0,0,TASK_STATE_NOT_READY);
	OS_Init();

    while(1)
    {
    	OS_DispatchTasks();
    }
}
