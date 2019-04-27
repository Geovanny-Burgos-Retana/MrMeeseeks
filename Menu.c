#include "Menu.h"

void Menu() {
    int option;
    while(1) {
        printf("1. Petición de restaurante\n2. Resolución de expresión\n3. Ejecución de programa\nIngrese la opción: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                Petition_Option();
                break;
            case 2:
                Expression_Option();
                break;
            case 3:                
                Program_Option();
                break;
            default:
                return;
        }
    }
}

void Petition_Option() {

}


void Expression_Option() {

    /*fork and child process*/
    pid_t pid = fork();

    if (pid < 0) { /*error occurred*/
        fprintf(stderr, "ForkFiled");
    } else if (pid > 0) { /* code parent process*/
        wait(NULL);
        kill(pid, SIGKILL);
    } else if (pid == 0) { /* code child process*/
        int option, result;
        char expression[50];
        
        printf("---------------\n1. Expresión Aritmética\n2.Expresión Lógica\nIngrese la opción: ");        
        scanf("%d", &option);
        printf("Ingrese la expresión: ");
        scanf("%s", expression);

        clock_t begin = clock();

        switch (option)
        {
            case 1:
                /* code for arithmetic expression */
                result = 20;
                sleep(10);
                break;
            case 2:            
                /* code for logical expression */
                result = 1;
                sleep(100);
                break;
            default:
                break;
        }
        
        /* here, do your time-consuming job and solve of expression*/

        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    }
}

Program_Option() {
    int data_processed;
    int pipefd[2]; // pipefd[0] is for read end of the pipe and pipe fd[1] is for write end of the pipe
    char* some_data;
    char buffer[BUFSIZ + 1];
    pid_t pid;

    memset(buffer, '\0', sizeof(buffer));

    if (pipe(pipefd) == 0) {
        
        pid = fork();
        
        if (pid == 0) { /* code child process */
            printf("Child...");
            clock_t begin = clock();            

            /* here, do your time-consuming job and solve of execution program */

            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

            close(pipefd[0]); // Close reading end of pipe
            snprintf(some_data, 50, "%f", time_spent);
            printf("Que paso: %s", some_data);

            data_processed = write(pipefd[1], some_data, strlen(some_data));
            close(pipefd[1]);

        } else if (pid > 0) { /* code parent process*/
            printf("Program ...");
            wait(pid);
            kill(pid, SIGKILL);
            printf("Program ...");
            close(pipefd[1]);

            data_processed = (pipefd[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", data_processed, buffer);
            close(pipefd[0]);
        }
    } else {
        
    }
}