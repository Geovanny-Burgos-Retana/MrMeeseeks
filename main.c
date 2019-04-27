/*--------------------------------------------
|Instituto Tecnológico de Costa Rica         |
|Curso: Principios de Sistemas Operativos    |
|Profesor: Esteban Arias Mendez              |
|Tarea 02: Mr. Meeseeks                      |
|Elaborado por:                              |
|    Camila Víquez Alpizar 2014152891        |
|    Geovanny Burgos Retana 2015111963       |
|Fechas de creación: 11/04/2019              |
|Fecha de entrega: 26/04/2019                |
--------------------------------------------*/

/*---------------------------------------------
Libraries section
---------------------------------------------*/
#include "Task.h"
#include "Array_Tasks.h"
#include "Menu.h"

/*--------------------------------
    Function declarations
--------------------------------*/

int main() {
    /*Array_Tasks array_tasks = {NULL, NULL, 0};    
    Task task = Get_Task(1.2,3,false);
    Task task2 = Get_Task(1012.2,9,true);
    Task task3 = Get_Task(12.2,29,true);
    printf("Dir. memoria array_tasks: %d\n", &array_tasks);
    Add_Task(&array_tasks, &task);
    Add_Task(&array_tasks, &task2);
    Add_Task(&array_tasks, &task3);
    printf("Complete: %d\n", task.complete);
    //printf("%s", To_String_Task(task));
    printf("Dir. memoria a primer elemento de la lista: %d\n", array_tasks.first);
    printf("Dir. memoria array_tasks: %d\n", &array_tasks);
    printf("%s\n", To_String_Task(*array_tasks.first));
    To_String_ArrayTasks(array_tasks.first);*/
    Menu();
    return 1;
}