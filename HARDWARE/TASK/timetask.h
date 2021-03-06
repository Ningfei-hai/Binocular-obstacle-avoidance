#ifndef __TIMETASK_H
#define __TIMETASK_H

#include "sys.h"

void task1(void);
void task2(void);
void task3(void);

void Task_DisableCallback(uint8_t task_number);
void Task_EnableCallback(uint8_t task_number);
void Task_OutCallback(uint8_t task_number);
void Task_InCallback(uint8_t task_number);

#endif
