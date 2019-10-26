


#include"OS_config.h"
#include"Timers.h"


typedef void (*ptrToFunc_t)(void);

#define MAX_SIZE_OF_TASK   13

typedef uint8_t states_t;
#define READY      0
#define RUNNING    1
#define WAITING    2
#define DELETED    3



typedef struct
{
	uint16_t task_counter;
	uint16_t time_period;
	ptrToFunc_t task;
	uint8_t periorty;
    states_t  states;

}str_Creat_Task_t;


typedef struct{

	uint8_t resolution;
	timer_type type;

}OS_ConfigType;


void OS_Init(const OS_ConfigType * ConfigPtr);
void OS_DeInit(void);
void OS_Creat_Task(	uint16_t time_period, ptrToFunc_t task, uint8_t periorty);
void OS_Delete_Task(ptrToFunc_t task);

void OS_Run(void);
void OS_system_tick(void);
