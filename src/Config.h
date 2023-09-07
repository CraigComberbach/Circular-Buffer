#ifndef CONFIG_H
#define	CONFIG_H

//Hardware specific include file
#include <p24F16KA101.h>

//Frequency Definitions
enum FREQUENCY_UNITS
{
	Hz,
	kHz,
	MHz,
};

struct TIME
{
	uint16_t time;
	enum TIME_UNITS
	{
		YEAR,
		WEEK,
		DAY,
		HOUR,
		MINUTE,
		SECOND,
		MILLISECOND,
		MICROSECOND
	} units;
};

//Helpful redefinitions
#define FOSC_Hz			8000000
#define FOSC_kHz		FOSC_Hz/1000
#define FOSC_MHz		FOSC_kHz/1000
#define FCY_Hz			FOSC_Hz/2
#define FCY_kHz			FCY_Hz/1000
#define FCY_MHz			FCY_kHz/1000
#define FCY_PERIOD_nS	1000000000/FCY_Hz
#define FCY_PERIOD_pS	1000000000/FCY_kHz

//Pins
enum PIN_DEFINITIONS
{
	PIN_RA0_PGC2,
	PIN_RA1_PGD2,
	PIN_RA2,
	PIN_RA3,
	PIN_RA4_PGC3,
	PIN_RA5_MCLR,
	PIN_RA6,
	PIN_RB0_PGD1,
	PIN_RB1_PGC1,
	PIN_RB2,
	PIN_RB4_PGD3,
	PIN_RB7,
	PIN_RB8,
	PIN_RB9,
	PIN_RB12,
	PIN_RB13,
	PIN_RB14,
	PIN_RB15,
	NUMBER_OF_PINS
};

//Scheduler
enum SCHEDULER_DEFINITIONS
{
	TASK_,
	NUMBER_OF_TASKS
};

//Expected Library Versions
	//Pins Library
	#define PINS_MAJOR	2
	#define PINS_MINOR	0
	#define PINS_PATCH	0

	//Scheduler Library
	#define SCHEDULER_MAJOR	1
	#define SCHEDULER_MINOR	0
	#define SCHEDULER_PATCH	0

void Configure_MCU(void);

#endif	/* CONFIG_H */
