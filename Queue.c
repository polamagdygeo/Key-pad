/**
 ******************************************************************************
 * @file           : Queue
 * @brief          :
 ******************************************************************************
 */

#include "Queue.h"
#include <stdlib.h>
#include "stdint.h"
#include "main.h"


struct tQueue{
	void* queue[QUEUE_MAX_LENGTH];
	uint8_t head_location;
	uint8_t tail_location;
	uint8_t elements_no;
	tQueue_Type Queue_Type;
};

/**
    *@brief Is Empty
    *@param void
    *@retval void
*/
uint8_t Queue_IsEmpty(ptQueue pQ)
{
	uint8_t ret = 0;

	if(pQ != 0)
	{
		if(pQ->elements_no == 0)
		{
			ret=1;
		}
	}

	return ret;
}

/**
    *@brief Is Full
    *@param void
    *@retval void
*/
uint8_t Queue_IsFull(ptQueue pQ)
{
	uint8_t ret = 0;
	if(pQ->elements_no >= QUEUE_MAX_LENGTH)
	{
		ret=1;
	}
	return ret;
}

/**
    *@brief Create and init queue
    *@param void
    *@retval void
*/
ptQueue Queue_Create(tQueue_Type Queue_Type)
{
	uint8_t itr ;
	ptQueue pQ = malloc(sizeof(struct tQueue));

	if(pQ != 0)
	{
		pQ->elements_no = 0;
		pQ->tail_location = 0;
		pQ->head_location = 0;
		pQ->Queue_Type = Queue_Type;

		for(itr = 0 ; itr < QUEUE_MAX_LENGTH ; itr++)
		{
			pQ->queue[itr] = 0;
		}
	}

	return pQ;
}

/**
    *@brief Enuque to a Queue
    *@param void
    *@retval void
*/
uint8_t Queue_Enqueue(ptQueue pQ,void* element)
{
	uint8_t ret = 0 ;
	INT_DISABLE();
	if(Queue_IsFull(pQ) == 0)
	{
		pQ->queue[pQ->head_location] = element;

		if(pQ->head_location == QUEUE_MAX_LENGTH-1)
		{
			pQ->head_location=0;
		}
		else
		{
			pQ->head_location++;
		}

		pQ->elements_no++;
		ret = 1;
	}
	INT_ENABLE();
	return ret;
}

/**
    *@brief Dequeue from Queue (without freeing)
    *@param void
    *@retval void
*/
uint8_t Queue_Dequeue(ptQueue pQ,void** element)
{
	uint8_t ret = 0;

	INT_DISABLE();
	if(Queue_IsEmpty(pQ) == 0)
	{
		*element = pQ->queue[pQ->tail_location];

		if(pQ->tail_location == QUEUE_MAX_LENGTH-1)
		{
			pQ->tail_location=0;
		}
		else
		{
			pQ->tail_location++;
		}

		pQ->elements_no--;
		ret = 1;
	}
	INT_ENABLE();

	return ret;
}

/**
    *@brief Fetch the Queue Head
    *@param void
    *@retval void
*/
uint8_t Queue_GetHead(ptQueue pQ,void** element)
{
	uint8_t ret = 0;

	INT_DISABLE();
	if(Queue_IsEmpty(pQ) == 0)
	{
		*element = pQ->queue[pQ->tail_location];

		ret = 1;
	}
	INT_ENABLE();
	return ret;
}

/**
    *@brief Dequeue from Queue (without freeing)
    *@param void
    *@retval void
*/
void* Queue_DeleteHead(ptQueue pQ)
{
	void* element = 0;

	INT_DISABLE();
	if(Queue_IsEmpty(pQ) == 0)
	{
		element = pQ->queue[pQ->tail_location];

		pQ->queue[pQ->tail_location] = 0;

		if(pQ->tail_location == QUEUE_MAX_LENGTH-1)
		{
			pQ->tail_location=0;
		}
		else
		{
			pQ->tail_location++;
		}

		pQ->elements_no--;
	}
	INT_ENABLE();

	return element;
}

/**
    *@brief Traverse on queue and pass each element to the passed function until a terminating point defined by passed function
    *@param void
    *@retval void
*/
uint8_t Queue_Traverse(ptQueue pQ,uint8_t (*p)(void* element,void* parameter,uint16_t parameter_length),void* parameter,uint16_t parameter_length)
{
	uint8_t terminating_flag = 0;
	uint8_t itr = pQ->tail_location;

	if(Queue_IsEmpty(pQ) != 1)
	{
		while(itr != pQ->head_location)
		{
			terminating_flag = p(pQ->queue[itr],parameter,parameter_length);

			if(terminating_flag == 1)
			{
				break;
			}

			if(itr == QUEUE_MAX_LENGTH-1)
			{
				itr = 0;
			}
			else
			{
				itr++;
			}
		}
	}

	return terminating_flag;
}
