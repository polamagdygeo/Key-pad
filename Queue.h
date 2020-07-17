/**
 ******************************************************************************
 * @file           : Queue
 * @brief          :
 ******************************************************************************
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "stdint.h"

#define QUEUE_MAX_LENGTH		10

typedef struct tQueue* ptQueue;

typedef enum{
	QUEUE_TYPE_CHAR_PTR
}tQueue_Type;

ptQueue Queue_Create(tQueue_Type Queue_Type);
uint8_t Queue_Enqueue(ptQueue pQ,void* element);
uint8_t Queue_Dequeue(ptQueue pQ,void** element);
uint8_t Queue_IsEmpty(ptQueue pQ);
uint8_t Queue_IsFull(ptQueue pQ);
uint8_t Queue_GetHead(ptQueue pQ,void** element);
void* Queue_DeleteHead(ptQueue pQ);
uint8_t Queue_Traverse(ptQueue pQ,uint8_t (*p)(void* element,void* parameter,uint16_t parameter_length),void* parameter,uint16_t parameter_length);
#endif /* QUEUE_H_ */
