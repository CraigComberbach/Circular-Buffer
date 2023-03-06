/*************    Header Files    ***************/
#include "Config.h"
#include "scheduler.h"

/************* Library Definition ***************/
/************* Semantic Versioning***************/
/************Arbitrary Functionality*************/
/*************   Magic  Numbers   ***************/
/*************    Enumeration     ***************/
/***********  Structure Definitions  ************/
/***********State Machine Definitions************/
/*************  Global Variables  ***************/
/*************Function  Prototypes***************/
/************* Device Definitions ***************/
/************* Module Definitions ***************/
/************* Other  Definitions ***************/

int main()
{
    Initialize_Scheduler(SCHEDULER_PERIOD, SCHEDULER_UNITS);
	Configure_MCU();

	while(1)
	{
		while(Waiting_To_Run_Tasks())
		{
			asm("ClrWdt");
			Task_Master();
		}
	}

	return 1;
}