/*
 * keypad.c
 *
 *  Created on: Jul 7, 2020
 *      Author: pola
 */

#include "OS.h"
#include "Queue.h"
#include "keypad.h"
#include "stdlib.h"
#include "dio.h"
#include "port.h"

#define KEYPAD_ASSERTION_LEVEL	DIO_RESET

typedef enum{
	KEYPAD_ROW_NO_0 = KEYPAD_ROW_0,
	KEYPAD_ROW_NO_1,
	KEYPAD_ROW_NO_2,
	KEYPAD_ROW_NO_3,
	KEYPAD_ROW_NO
}tKeypad_Rows;

typedef enum{
	KEYPAD_COL_NO_0,
	KEYPAD_COL_NO_1,
	KEYPAD_COL_NO_2,
	KEYPAD_COL_NO
}tKeypad_Cols;

typedef enum{
	KEYPAD_BUTTON_RELEASED,
	KEYPAD_BUTTON_MAY_BE_PRESSED,
	KEYPAD_BUTTON_PRESSED,
	KEYPAD_BUTTON_MAY_BE_RELEASED,
}tKeypad_ButtonState;

static ptQueue keypad_ring_buffer;
static const char keypad_char_map[KEYPAD_ROW_NO][KEYPAD_COL_NO] = {{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}
};

void Keypad_Init(void)
{
	DIO_ConfigPort(KEYPAD_PORT,0x0f,DIO_OUTPUT);
	DIO_WritePort(KEYPAD_PORT,0x0f,0x0f);
	DIO_ConfigPort(KEYPAD_PORT,0x70,DIO_INPUT);
	DIO_WritePort(KEYPAD_PORT,0x70,0x70);

	keypad_ring_buffer = Queue_Create(QUEUE_TYPE_CHAR_PTR);

	if(keypad_ring_buffer == 0)
		while(1);

	OS_AddTask(0,Keypad_Update,5,0,0,TASK_STATE_NOT_READY);
}
void Keypad_Update(void)
{
	char key = 0;
	char *char_ptr = 0;
	tKeypad_Cols col_itr;

	static tKeypad_Rows current_row = KEYPAD_ROW_NO_0;
	static char button_state[KEYPAD_ROW_NO][KEYPAD_COL_NO] = {0};
	static uint8_t previous_sample[KEYPAD_ROW_NO][KEYPAD_COL_NO] = {0};

	for(col_itr = KEYPAD_COL_NO_0; col_itr < KEYPAD_COL_NO ; col_itr++)
	{
		uint8_t current_sample = DIO_ReadPin(KEYPAD_PORT,col_itr + KEYPAD_ROW_NO);

		switch(button_state[current_row][col_itr])
		{
		case KEYPAD_BUTTON_RELEASED:
			if(previous_sample[current_row][col_itr] != KEYPAD_ASSERTION_LEVEL &&
					current_sample == KEYPAD_ASSERTION_LEVEL)
			{
				button_state[current_row][col_itr] = KEYPAD_BUTTON_MAY_BE_PRESSED;
			}
			break;
		case KEYPAD_BUTTON_MAY_BE_PRESSED:
			if(current_sample == KEYPAD_ASSERTION_LEVEL)
			{
				button_state[current_row][col_itr] = KEYPAD_BUTTON_PRESSED;
				key = keypad_char_map[current_row][col_itr];
				col_itr = KEYPAD_COL_NO; /*break outer loop*/
			}
			else
			{
				button_state[current_row][col_itr] = KEYPAD_BUTTON_RELEASED;
			}
			break;
		case KEYPAD_BUTTON_PRESSED:
			if(previous_sample[current_row][col_itr] == KEYPAD_ASSERTION_LEVEL &&
					current_sample != KEYPAD_ASSERTION_LEVEL)
			{
				button_state[current_row][col_itr] = KEYPAD_BUTTON_MAY_BE_RELEASED;
			}
			break;
		case KEYPAD_BUTTON_MAY_BE_RELEASED:
			if(current_sample != KEYPAD_ASSERTION_LEVEL)
			{
				button_state[current_row][col_itr] = KEYPAD_BUTTON_RELEASED;
			}
			else
			{
				button_state[current_row][col_itr] = KEYPAD_BUTTON_PRESSED;
			}
			break;
		}

		previous_sample[current_row][col_itr] = current_sample;
	}

	DIO_WritePin(KEYPAD_PORT,current_row,(KEYPAD_ASSERTION_LEVEL ^ 0x01));

	current_row++;

	current_row %= KEYPAD_ROW_NO;

	/*become next_row*/
	DIO_WritePin(KEYPAD_PORT,current_row,KEYPAD_ASSERTION_LEVEL);

	/*Allocate space for pressed key and queue it*/
	if(key != 0)
	{
		char_ptr = malloc(sizeof(char));
		if(char_ptr != 0)
		{
			*char_ptr = key;

			if(!Queue_Enqueue(keypad_ring_buffer,char_ptr))
			{
				/*failed to enqueue*/
			}
		}
	}
}
char Keypad_GetChar(void)
{
	char ret_char = 0;
	void *ret_char_ptr = 0;

	if(Queue_Dequeue(keypad_ring_buffer,&ret_char_ptr))
	{
		ret_char = *((char*)ret_char_ptr);
		free(ret_char_ptr);
	}

	return ret_char;
}
