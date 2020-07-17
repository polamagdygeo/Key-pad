/*
 * dio.h
 *
 *  Created on: Jul 7, 2020
 *      Author: pola
 */

#ifndef DIO_H_
#define DIO_H_

#include "main.h"

typedef enum{
	DIO_PORTA,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD,
	DIO_PORT_NO
}tDIO_Port;

typedef enum{
	DIO_RESET,
	DIO_SET
}tDIO_Level;

typedef enum{
	DIO_INPUT,
	DIO_OUTPUT
}tDIO_Direction;

void DIO_ConfigPin(tDIO_Port port,uint8_t pin,tDIO_Direction dir);
void DIO_ConfigPort(tDIO_Port port,uint8_t mask,tDIO_Direction dir);
void DIO_WritePin(tDIO_Port port,uint8_t pin,tDIO_Level level);
tDIO_Level DIO_ReadPin(tDIO_Port port,uint8_t pin);
void DIO_WritePort(tDIO_Port port,uint8_t mask,uint8_t value);
uint8_t DIO_ReadPort(tDIO_Port port,uint8_t mask);

#endif /* DIO_H_ */
