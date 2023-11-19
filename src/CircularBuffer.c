/******************************************************************************
Version History:
v0.0.0	YYYY-MM-DD	Craig Comberbach	Compiler: [Compiler] [Version]
* First version
 *****************************************************************************/
/************Header Files*************/
#include "CircularBuffer.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/********Semantic Versioning**********/
#ifdef FEATURE_CIRCULAR_BUFFER
	#if CIRCULAR_BUFFER_MAJOR != 0
		#error "CircularBuffer library major revision update is available"
	#elif CIRCULAR_BUFFER_MINOR != 0
		#error "CircularBuffer library minor revision update is available"
	#elif CIRCULAR_BUFFER_PATCH != 0
		#error "CircularBuffer library patch revision update is available"
	#endif

/***********Magic Numbers*************/
/************Enumeration**************/
/*********Object Definition***********/
struct CircularBuffer_t
{
	uint8_t HeadIndex;
	uint8_t TailIndex;
	uint8_t *Buffer;
	uint8_t SizeOfBuffer;

	bool isOwned;
} Selves[NUMBER_OF_CIRCULAR_BUFFERS] = {[0 ... NUMBER_OF_CIRCULAR_BUFFERS - 1] =
	{
		.HeadIndex = 0,
		.TailIndex = 0,
		.Buffer = NULL,
		.SizeOfBuffer = 0,
	}};

/**********Global Variables***********/
/*****Local Function Prototypes*******/
uint8_t Advance_Index(uint8_t index, uint8_t MaxIndex);
uint8_t Buffer_Is_Full(CircularBuffer_t *self);
uint8_t Buffer_Is_Empty(CircularBuffer_t *self);

/*********Main Body Of Code***********/
uint8_t CB_Aquire_CircularBuffer_Object(CircularBuffer_t **self, enum CircularBuffer_ObjectList ID)
{
	uint8_t ReturnCode = 0;

	if(ID < NUMBER_OF_CIRCULAR_BUFFERS)
	{
		*self = &Selves[ID];

		ReturnCode = 1;
	}

	return ReturnCode;
}

uint8_t CB_Return_CircularBuffer_Object(CircularBuffer_t **self)
{
	uint8_t ReturnCode = 0;

	*self = NULL;

	return 1;
}

uint8_t CB_Set_Buffer(CircularBuffer_t *self, uint8_t *NewBuffer, uint8_t Length)
{
	uint8_t ReturnCode = 0;

	if((self != NULL) && (NewBuffer != NULL))
	{
		self->Buffer = NewBuffer;
		self->SizeOfBuffer = Length;

		ReturnCode = 1;
	}

	return ReturnCode;
}

uint8_t CB_Reset_CircularBuffer(CircularBuffer_t *self)
{
	uint8_t ReturnCode = 0;

	if(self != NULL)
	{
		self->HeadIndex = 0,
		self->TailIndex = 0,
		self->Buffer = NULL,
		self->SizeOfBuffer = 0,

		ReturnCode = 1;
	}

	return ReturnCode;
}

uint8_t CB_Write(CircularBuffer_t *self, uint8_t *newData)
{
	uint8_t ReturnCode = 0;

	if((self != NULL) && (self->Buffer != NULL))
	{
		if(!Buffer_Is_Full(self))
		{
			self->Buffer[self->TailIndex] = *newData;
			self->TailIndex = Advance_Index(self->TailIndex, self->SizeOfBuffer);
			ReturnCode = 1; //Success
		}
	}

	return ReturnCode;
}

uint8_t CB_Read(CircularBuffer_t *self, uint8_t **data)
{
	uint8_t ReturnCode = 0;

	if((self != NULL) && (self->Buffer != NULL))
	{
		if(!Buffer_Is_Empty(self))
		{
			*data = &(self->Buffer[self->HeadIndex]);
			self->HeadIndex = Advance_Index(self->HeadIndex, self->SizeOfBuffer);

			ReturnCode = 1;
		}
	}

	return ReturnCode;
}

uint8_t Advance_Index(uint8_t index, uint8_t MaxIndex)
{
    if(index == (MaxIndex-1))
    {
        index = 0;
    }
    else
    {
        index++;
    }
    
    return index;
}

uint8_t Buffer_Is_Full(CircularBuffer_t *self)
{
    uint8_t TailPlusOne = 0;
    
    TailPlusOne = Advance_Index(self->TailIndex, self->SizeOfBuffer);

    if(self->HeadIndex == TailPlusOne)
    {
        return 1; //Full
    }
    else
    {
        return 0; //Not full
    }
}

uint8_t Buffer_Is_Empty(CircularBuffer_t *self)
{
    if(self->HeadIndex == self->TailIndex)
    {
        return 1; //Empty
    }
    else
    {
        return 0; //Not empty
    }
}

#endif//FEATURE_CIRCULAR_BUFFER

#if 0
uint8_t Read_Circular_Buffer(intptr_t *data)
{
    if(Buffer_Is_Empty())
    {
        return 0;  //Failure, buffer is empty
    }

    *data = CB.Buffer[CB.HeadIndex];
    CB.HeadIndex = Advance_Index(CB.HeadIndex);
    
    return 1; //Success, value was read
}


#endif
