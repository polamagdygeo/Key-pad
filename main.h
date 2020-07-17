#ifndef __MAIN_H
#define __MAIN_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#define F_OSC								8000000ul
#define INT_DISABLE()   					cli()
#define INT_ENABLE()   						sei()

#define GET_BIT(VAR,BIT)					(((VAR) & (1<<(BIT))) >> (BIT))
#define	GET_VAL(VAR,MASK)					((VAR) & (MASK))
#define SET_VAR_VAL(VAR,MASK,VAL)			((VAR) = ((VAR) & (~(MASK))) | (((VAL) & (MASK))))

#define TIMER1_CTRLA_REG					TCCR1A
#define TIMER1_CTRLB_REG					TCCR1B
#define TIMER1_PRESCALER_1					1
#define TIMER1_PRESCALER_8					2
#define TIMER1_PRESCALER_32					3
#define TIMER1_PRESCALER_64					4
#define TIMER1_PRESCALER_256				5
#define TIMER1_PRESCALER_1024				6

#define TIMER1_COUNTER_REG					TCNT1
#define TIMER1_RELOAD_REG					OCR1A
#define TIMER1_INT_MASK_REG					TIMSK
#define TIMER1_STATUS_REG					TIFR

#define TIMER1_SET_CTC_MODE()				SET_VAR_VAL(TIMER1_CTRLB_REG,0x18,8); \
											SET_VAR_VAL(TIMER1_CTRLA_REG,3,0)
#define TIMER1_ENABLE(PRE)					SET_VAR_VAL(TIMER1_CTRLB_REG,0x07,PRE)
#define TIMER1_DISABLE()					SET_VAR_VAL(TIMER1_CTRLB_REG,0x07,0)
#define TIMER1_GET_COUNTER()				GET_VAL(TIMER1_COUNTER_REG,0xffff)
#define TIMER1_HAS_TIMEOUT()				GET_BIT(TIMER1_STATUS_REG,4)
#define TIMER1_ENABLE_INT()					SET_VAR_VAL(TIMER1_INT_MASK_REG,1 << 4,1 << 4)
#define TIMER1_DISABLE_INT()				SET_VAR_VAL(TIMER1_INT_MASK_REG,1 << 4,0 << 4)
#define TIMER1_SET_RELOAD_VAL(VAL)			((TIMER1_RELOAD_REG) = (VAL))

#define TIMER1_REGIST_INT_CB(FUNC)										\
	ISR(TIMER1_COMPA_vect)												\
	{																	\
		FUNC();															\
	}

#endif
