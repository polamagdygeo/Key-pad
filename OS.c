/**
 ******************************************************************************
 * @file           : OS
 * @brief          :
 ******************************************************************************
 */

#include "OS.h"

typedef struct{
	pTask task_function;
	tTask_State Task_State;
	uint32_t period_counter;
	uint32_t period;
	uint32_t delay_counter;
	uint32_t delay;
	uint8_t TaskId;	/*For Debug*/
	uint8_t isPreemptive;
}tTask_ControlBlock;

static tTask_ControlBlock TCBs_Array[MAX_TASKS_NUM] = {0};
static uint8_t TCBs_Counter = {0};

typedef enum{
	OS_State_Stopped,
	OS_State_Running
}tOS_State;

TIMER1_REGIST_INT_CB(OS_SchedulerUpdate);

static tOS_State OS_State = OS_State_Stopped;

/**
    *@brief OS Init
    *@param void
    *@retval void
*/
void OS_Init(void)
{
	TIMER1_SET_CTC_MODE();

	TIMER1_SET_RELOAD_VAL(1000);

	OS_Start();
}

/**
    *@brief OS Stop
    *@param void
    *@retval void
*/
void OS_Stop(void)
{
	OS_State = OS_State_Stopped;

	TIMER1_DISABLE_INT();
	TIMER1_DISABLE();
}

/**
    *@brief OS Start
    *@param void
    *@retval void
*/
void OS_Start(void)
{
	OS_State = OS_State_Running;


	TIMER1_ENABLE(TIMER1_PRESCALER_8);
	TIMER1_ENABLE_INT();
	INT_ENABLE();
}

/**
    *@brief Suspend Task
    *@param void
    *@retval void
*/
void OS_SuspendTask(uint8_t task_id)
{
	if(task_id < MAX_TASKS_NUM)
	{
		INT_DISABLE();
		TCBs_Array[task_id].Task_State = TASK_STATE_DORMANT;
		INT_ENABLE();
	}
}

/**
    *@brief Restart task , it will start being called at its periodicity after its delay
    *@param void
    *@retval void
*/
void OS_RestartTask(uint8_t task_id)
{
	if(task_id < MAX_TASKS_NUM)
	{
		INT_DISABLE();
		TCBs_Array[task_id].Task_State = TASK_STATE_NOT_READY;
		TCBs_Array[task_id].delay_counter = 0;
		TCBs_Array[task_id].period_counter = 0;
		INT_ENABLE();
	}
}

/**
    *@brief Activate task , it will start being called at its periodicity starting next scheduling
    *@param void
    *@retval void
*/
void OS_ActivateTask(uint8_t task_id)
{
	if(task_id < MAX_TASKS_NUM)
	{
		INT_DISABLE();
		TCBs_Array[task_id].Task_State = TASK_STATE_NOT_READY;
		TCBs_Array[task_id].delay_counter = TCBs_Array[task_id].delay;
		TCBs_Array[task_id].period_counter = 0;
		INT_ENABLE();
	}
}

/**
    *@brief Delay task , it will start being called at its periodicity after input delay
    *@param void
    *@retval void
*/
void OS_DelayTask(uint8_t task_id,uint32_t delay)
{
	if(task_id < MAX_TASKS_NUM)
	{
		INT_DISABLE();
		TCBs_Array[task_id].Task_State = TASK_STATE_NOT_READY;
		TCBs_Array[task_id].delay  = delay;
		TCBs_Array[task_id].delay_counter = 0;
		TCBs_Array[task_id].period_counter = 0;
		INT_ENABLE();
	}
}

/**
    *@brief Add Task
    *@param void
    *@retval void
*/
void OS_AddTask(uint8_t task_id,pTask task_function,uint32_t period,uint32_t delay,uint8_t isPreemptive,tTask_State init_state)
{
	if(task_function != 0 &&
			task_id < MAX_TASKS_NUM &&
			TCBs_Counter < MAX_TASKS_NUM)
	{
		TCBs_Array[task_id].TaskId = task_id;
		TCBs_Array[task_id].task_function = task_function;
		TCBs_Array[task_id].period = period;
		TCBs_Array[task_id].delay = delay;
		TCBs_Array[task_id].isPreemptive = isPreemptive;
		TCBs_Array[task_id].Task_State = init_state;

		TCBs_Counter++;
	}
}

/**
    *@brief Scheduler Update
    *@param void
    *@retval void
*/
void OS_SchedulerUpdate(void)
{
	uint8_t itr;

	if(OS_State == OS_State_Running)
	{
		for(itr = 0 ; itr < MAX_TASKS_NUM ; itr++)
		{
			if(TCBs_Array[itr].task_function != 0 &&
					TCBs_Array[itr].Task_State == TASK_STATE_NOT_READY)
			{
				if(TCBs_Array[itr].delay_counter <= TCBs_Array[itr].delay)
				{
					if(TCBs_Array[itr].delay_counter == TCBs_Array[itr].delay)
					{
						TCBs_Array[itr].Task_State = TASK_STATE_READY;
					}

					TCBs_Array[itr].delay_counter++;
				}
				else
				{
					if(TCBs_Array[itr].period != 0)
					{
						TCBs_Array[itr].period_counter++;
					}

					if(TCBs_Array[itr].period_counter == TCBs_Array[itr].period)
					{
						TCBs_Array[itr].period_counter = 0;

						TCBs_Array[itr].Task_State = TASK_STATE_READY;
					}
				}

				if(TCBs_Array[itr].Task_State == TASK_STATE_READY)
				{
					if(TCBs_Array[itr].isPreemptive == 1)
					{
						TCBs_Array[itr].Task_State = TASK_STATE_NOT_READY;
						TCBs_Array[itr].task_function();
					}
				}
			}
		}
	}
}

/**
    *@brief OS Dispatch
    *@param void
    *@retval void
*/
void OS_DispatchTasks(void)
{
	uint8_t itr;

	for(itr = 0 ; itr < MAX_TASKS_NUM ; itr++)
	{
		if(TCBs_Array[itr].task_function != 0 &&
				TCBs_Array[itr].Task_State == TASK_STATE_READY)
		{
			TCBs_Array[itr].task_function();

			INT_DISABLE();
			if(TCBs_Array[itr].Task_State != TASK_STATE_DORMANT)
			{
				TCBs_Array[itr].Task_State = TASK_STATE_NOT_READY;
			}
			INT_ENABLE();
		}
	}
}
