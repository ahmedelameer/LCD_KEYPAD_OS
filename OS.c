
#include"OS.h"
#include"avr/sleep.h"


static volatile uint8_t task_index=0;
static uint16_t first_empty=0;
uint8_t flag=0;


static str_Creat_Task_t task_buffer[MAX_SIZE_OF_TASK]={{0},{0},{0}};


void OS_Init(const OS_ConfigType * ConfigPtr)
{
	timer_setup( ConfigPtr->type );

	timer_resolution( ConfigPtr->type , 2 , 1 );

	set_interrupt_call_back(OS_system_tick);
}


/*put the task by its priority in the buffer*/

void OS_Creat_Task(	uint16_t time_period, ptrToFunc_t task, uint8_t periorty)
{
	/* check if os init or not */
	/*check if buffer is full or not*/

	str_Creat_Task_t temp1,temp2;
	uint8_t loop_index = 0, first_swap_flag = 1, swap_state = 0;

	/*first func to put in the buffer*/

	if (first_empty < MAX_SIZE_OF_TASK+1)
	{
		if (first_empty == 0)
		{
			task_buffer[first_empty].time_period = time_period;
			task_buffer[first_empty].task = task;
			task_buffer[first_empty].periorty = periorty;
			first_empty++;
		}
		/*put priority is equal to func at the last put it at the end*/
		else if (periorty >= task_buffer[first_empty-1].periorty)
		{
			//task_buffer[first_empty] = *task;
			task_buffer[first_empty].time_period = time_period;
			task_buffer[first_empty].task = task;
			task_buffer[first_empty].periorty = periorty;
			first_empty++;
		}
		else
		{    /* inserting element that has a higher  priority  in the buffer shift all the element*/
			for (loop_index = 0; loop_index < first_empty; loop_index++ )
			{
				if(periorty < task_buffer[loop_index].periorty && first_swap_flag == 1)
				{
					temp1 = task_buffer[loop_index];
					task_buffer[loop_index].time_period = time_period;
					task_buffer[loop_index].task = task;
					task_buffer[loop_index].periorty = periorty;
					first_empty++;
					first_swap_flag = 0;
					swap_state = 1;
				}
				else if (swap_state == 1)
				{
					temp2 = task_buffer[loop_index];
					task_buffer[loop_index] = temp1;
					swap_state = 2;
				}
				else if(swap_state == 2)
				{
					temp1 = task_buffer[loop_index];
					task_buffer[loop_index] = temp2;
					swap_state = 1;

				}

			}

		}
	}
	else
	{
		/*buffer is full*/
	}
}


void OS_Run(void)
{
	uint8_t task;
	while(1)
	{

		if(flag==1)  /* to guard the run_os not to work unless within the system tick */
		{

		for(task=0;task<first_empty;task++)
		{   /*check if the time of the functions comes */
			if( task_buffer[task].time_period == task_buffer[task].task_counter )
			{
				task_buffer[task].task();
				/*if you call the func reset its counter to start from the begining*/
				task_buffer[task].task_counter=0;
			}
		}

	     flag=0;
		}

		sleep_mode();


	}
}



void OS_Delete_Task(ptrToFunc_t task)
{
	uint8_t task_detected_flag = 0,loop_index;

	if (first_empty != 0) /* check if the buffer is empty or not*/
	{
		if (task == task_buffer[first_empty-1].task) /*if you deleted task at the end make the counter point */
		{
			                                         /* at the previous position*/
			first_empty--;
		}
		else
		{
			for (loop_index = 0; loop_index < first_empty; loop_index++ )
			{
				if(task == task_buffer[loop_index].task)
				{
					task_buffer[loop_index] = task_buffer[loop_index+1];
					first_empty--;
					task_detected_flag = 1;
				}
				else if (task_detected_flag == 1)
				{
					task_buffer[loop_index] = task_buffer[loop_index+1];
				}


			}

		}
	}
	else
	{
		/*Buffer empty already */
		task_detected_flag = 1;
	}

	if (task_detected_flag == 0)
	{
		/*retvalue = no_task_in_buffer_with_this_name*/

	}
}



void OS_system_tick(void)
{


    flag =1;  /* to guard the run_os not to work unless within the system tick */

    /*increment all counter of the functions when system tick happens*/
	for(task_index=0;task_index<first_empty;task_index++)
	{
		task_buffer[task_index].task_counter++;
	}



}
