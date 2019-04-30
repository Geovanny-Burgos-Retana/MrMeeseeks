#include "Array_Tasks.h"

/* Recuperado de: http://www.santiagoapostol.net/srca/cursoc/cursoc22.html */
void Add_Task(Array_Tasks *array, Task *task) {
    printf("\tDir. memoria array: %d\n", array);
    /* el campo siguiente va a ser NULL por ser el último elemento
        de la lista */
    task->next = NULL;
    /* ahora metemos el nuevo elemento en la lista. lo situamos
        al final de la lista */
    /* comprobamos si la lista está vacía. si primero==NULL es que no
        hay ningún elemento en la lista. también vale ultimo==NULL */
    if (array->first == NULL) {        
        printf("\tDir. memoria task: %d\n", task);
        array->first = task;
        array->last = task;
    } else {
        /* el que hasta ahora era el último tiene que apuntar al nuevo */
        array->last->next = task;
        /* hacemos que el nuevo sea ahora el último */
        array->last = task;
    }
    array->size = array->size + 1;
    printf("\tDir. memoria primera task: %d\n\tDir. memoria primera task: %d\n", array->first, task);
}

void To_String_ArrayTasks(Task *task) {
    if (task != NULL) {
        printf("%s", To_String_Task(*task));
        while(task->next != NULL){
            printf("%s", To_String_Task(*task->next));
            task = task->next;
        }
    } else {
        printf("Arreglo vacio");
    }    
}