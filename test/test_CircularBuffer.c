
#ifdef TEST

#include "unity.h"
#include <stddef.h>
#include <stdint.h>
#include "CircularBuffer.h"

#define GLOBAL_BUFFER_SIZE  8
CircularBuffer_t *GlobalHandle = NULL;
uint8_t GlobalBuffer[GLOBAL_BUFFER_SIZE];

void setUp(void)
{
    CB_Aquire_CircularBuffer_Object(&GlobalHandle, CB_GLOBAL_TEST);
    CB_Reset_CircularBuffer(GlobalHandle);
    CB_Set_Buffer(GlobalHandle, &GlobalBuffer[0], GLOBAL_BUFFER_SIZE);
    
    return;
}

void tearDown(void)
{
    CB_Return_CircularBuffer_Object(&GlobalHandle);
}

void test_CircularBuffer_Aquire_And_Release_Handle(void)
{
    CircularBuffer_t *LocalHandle = NULL;
    uint8_t ReturnCode;

    ReturnCode = CB_Aquire_CircularBuffer_Object(&LocalHandle, CB_LOCAL_TEST);
    TEST_ASSERT_EQUAL_INT (1, ReturnCode);
    TEST_ASSERT_NOT_NULL(LocalHandle);

    ReturnCode = CB_Return_CircularBuffer_Object(&LocalHandle);
    TEST_ASSERT_EQUAL_INT (1, ReturnCode);
    TEST_ASSERT_NULL(LocalHandle);
    
    return;
}

void test_CircularBuffer_Write_From_Empty_To_Full(void)
{
    uint8_t Data[] = {1,2,3};
    uint8_t ReturnCode;
    uint8_t Loop;

    for(Loop = 0; Loop < (GLOBAL_BUFFER_SIZE-1); Loop++)
    {
        ReturnCode = CB_Write(GlobalHandle, &Data[0]);
        TEST_ASSERT_EQUAL_INT (1, ReturnCode);
    }

    ReturnCode = CB_Write(GlobalHandle, &Data[0]);
    TEST_ASSERT_EQUAL_INT (0, ReturnCode);

    return;
}

void test_CircularBuffer_Read_From_Full_To_Empty(void)
{
    uint8_t Data[] = {1,2,3};
    uint8_t ReturnCode;
    uint8_t Loop;

    for(Loop = 0; Loop < (GLOBAL_BUFFER_SIZE-1); Loop++)
    {
        ReturnCode = CB_Write(GlobalHandle, &Data[0]);
    }

    for(Loop = 0; Loop < (GLOBAL_BUFFER_SIZE-1); Loop++)
    {
        ReturnCode = CB_Read(GlobalHandle, &Data);
        TEST_ASSERT_EQUAL_INT (1, ReturnCode);
    }

    ReturnCode = CB_Read(GlobalHandle, &Data);
    TEST_ASSERT_EQUAL_INT (0, ReturnCode);

    return;
}

void test_CircularBuffer_Write_Read_Validity(void)
{
    uint8_t Data[] = {1,2,3};
    uint8_t *ReturnedData;
    uint8_t ReturnCode;

    TEST_IGNORE();
    ReturnCode = CB_Write(GlobalHandle, &Data[0]);
    TEST_ASSERT_EQUAL_INT (1, ReturnCode);
    
    ReturnCode = CB_Read(GlobalHandle, &ReturnedData);
    TEST_ASSERT_EQUAL_INT (1, ReturnCode);
    TEST_ASSERT_EQUAL_PTR(Data, *ReturnedData);

    return;
}

#endif // TEST
