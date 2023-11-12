#ifndef CircularBuffer_H
#define CircularBuffer_H

/**********Include Headers************/
#include <stdint.h>
#include "Config.h"

/**********Add to config.h************/
/*
enum CircularBuffer_ObjectList
{
	CIRCULAR_BUFFER_,
	NUMBER_OF_CIRCULAR_BUFFERS
};

	//CircularBuffers Library
	#define FEATURE_CIRCULAR_BUFFER
	#define CIRCULAR_BUFFER_MAJOR	0
	#define CIRCULAR_BUFFER_MINOR	0
	#define CIRCULAR_BUFFER_PATCH	0
*/

/**********Add to config.c************/
/*
#ifndef CIRCULAR_BUFFER_LIBRARY
	#error "CircularBuffers library was not found"
#endif
*/

/********Semantic Versioning**********/
#define CIRCULAR_BUFFER_LIBRARY

/***********Magic Numbers*************/
/************Enumeration**************/
/*********Object Definition***********/
#ifdef FEATURE_CIRCULAR_BUFFER
typedef struct CircularBuffer_t CircularBuffer_t;
#else
typedef void CircularBuffer_t;
#endif

/****Module Function Prototypes*******/
uint8_t CB_Aquire_CircularBuffer_Object(CircularBuffer_t **self, enum CircularBuffer_ObjectList Index);
uint8_t CB_Return_CircularBuffer_Object(CircularBuffer_t **self);

uint8_t CB_Set_Buffer(CircularBuffer_t *self, uint8_t *buffer, uint8_t Length);
uint8_t CB_Reset_CircularBuffer(CircularBuffer_t *self);

uint8_t CB_Write(CircularBuffer_t *self, uint8_t *newData);
uint8_t CB_Read(CircularBuffer_t *self, uint8_t **data);

#endif//CircularBuffer_H
