#include "Task.h"

Task Get_Task(float execution_time, int quality_mrs, int complete) {
    Task task;
    task.execution_time = execution_time;
    task.quality_mrs = quality_mrs;
    task.complete = complete;
    return task;
};

/* https://github.com/TheAlgorithms/C/blob/master/data_structures/Array/CArray.c */
char* To_String_Task(Task task) {
    /* get lenght of string required to hold struct values */
    size_t len = 0;
    len = snprintf (NULL, len, "Task: { Tiempo de ejecución: %f, Cantidad de MrMeeseeks: %d, Completada: %d }\n", 
                    task.execution_time, task.quality_mrs, task.complete);

    /* allocate/validate string to hold all values (+1 to null-terminate) */
    char *apstr = calloc (1, sizeof *apstr * len + 1);
    if (!apstr) {
        fprintf (stderr, "%s() error: virtual memory allocation failed.\n", __func__);
    }

    /* write/validate struct values to apstr */
    if (snprintf (apstr, len + 1, "Task: { Tiempo de ejecución: %f, Cantidad de MrMeeseeks: %d, Completada: %d }\n", 
                    task.execution_time, task.quality_mrs, task.complete) > len + 1)
    {
        fprintf (stderr, "%s() error: snprintf returned truncated result.\n", __func__);
        return NULL;
    }

    return apstr;
}