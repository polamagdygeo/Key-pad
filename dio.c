/*
 * dio.c
 *
 *  Created on: Jul 7, 2020
 *      Author: pola
 */

#include "main.h"
#include "dio.h"

static volatile uint8_t *dir_reg_arr[DIO_PORT_NO] = {&DDRA,&DDRB,&DDRC,&DDRD};
static volatile uint8_t *port_reg_arr[DIO_PORT_NO] = {&PORTA,&PORTB,&PORTC,&PORTD};
static volatile uint8_t *pin_reg_arr[DIO_PORT_NO] = {&PINA,&PINB,&PINC,&PIND};

void DIO_ConfigPin(tDIO_Port port,uint8_t pin,tDIO_Direction dir)
{
	SET_VAR_VAL(*dir_reg_arr[port],1 << pin,dir << pin);
}
void DIO_ConfigPort(tDIO_Port port,uint8_t mask,tDIO_Direction dir)
{
	SET_VAR_VAL(*dir_reg_arr[port],mask,dir == DIO_OUTPUT ? 0xff : 0);
}

void DIO_WritePin(tDIO_Port port,uint8_t pin,tDIO_Level level)
{
	SET_VAR_VAL(*port_reg_arr[port],1 << pin,level << pin);
}
tDIO_Level DIO_ReadPin(tDIO_Port port,uint8_t pin)
{
	return GET_BIT(*pin_reg_arr[port],pin);
}
void DIO_WritePort(tDIO_Port port,uint8_t mask,uint8_t value)
{
	*port_reg_arr[port] = value;
}
uint8_t DIO_ReadPort(tDIO_Port port,uint8_t mask)
{
	return (*pin_reg_arr[port] & mask);
}
