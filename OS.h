/**
 ******************************************************************************
 * @file           : OS
 * @brief          :
 ******************************************************************************
 */

#ifndef OS_H_
#define OS_H_

#include "main.h"

#define MAX_TASKS_NUM	2U
#define TICK_MS			1U

typedef enum{
	TASK_STATE_NOT_READY,
	TASK_STATE_READY,
	TASK_STATE_DORMANT
}tTask_State;

typedef void (*pTask)(void);

void OS_Init(void);
void OS_Stop(void);
void OS_Start(void);
void OS_SuspendTask(uint8_t task_id);
void OS_RestartTask(uint8_t task_id);
void OS_ActivateTask(uint8_t task_id);
void OS_DelayTask(uint8_t task_id,uint32_t delay);
void OS_AddTask(uint8_t task_id,pTask task_function,uint32_t period,uint32_t delay,uint8_t isPreemptive,tTask_State init_state);
void OS_SchedulerUpdate(void);
void OS_DispatchTasks(void);



#endif /* SCHEDULER_H_ */
