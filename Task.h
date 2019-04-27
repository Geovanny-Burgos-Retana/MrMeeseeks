#ifndef TASK_H
#define TASK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Task Task;

struct Task
{
    float execution_time;
    int quality_mrs;
    bool complete;
    Task *next;
};

Task Get_Task(float, int, int);
char* To_String_Task(Task);

#endif