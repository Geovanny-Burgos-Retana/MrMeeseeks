#ifndef ARRAY_TASKS_H
#define ARRAY_TASKS_H

#include "Task.h"

typedef struct Array_Tasks Array_Tasks;

struct Array_Tasks
{
    Task* first;
    Task* last;
    int size;
};

void Add_Task(Array_Tasks*, Task*);
void To_String_ArrayTasks(Task*);

#endif