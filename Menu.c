#include "Menu.h"

void Menu()
{
    int option;
    while (1)
    {
        printf("1. Petición de restaurante\n2. Resolución de expresión\n3. Ejecución de programa\nIngrese la opción: ");
        scanf("%d", &option);
        switch (option)
        {
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

void Petition_Option()
{
}

void Expression_Option()
{

    int data_processed;
    int file_pipes[2];
    char some_data[BUFSIZ + 1];
    char buffer[BUFSIZ + 1];
    /*fork and child process*/
    pid_t pid;

    memset(buffer, '\0', sizeof(buffer));

    if (pipe(file_pipes) == 0)
    {
        pid = fork();
        if (pid == 0)
        { /* code child process*/
            int option, result;

            printf("---------------\n1. Expresquiión Aritmética\n2. Expresión Lógica\nIngrese la opción: ");
            scanf("%d", &option);

            clock_t begin = clock();

            switch (option)
            {
            case 1:
                arithmetic_expression();
                result = 20;
                sleep(10);
                break;
            case 2:
                // code for logical expression 
                result = 1;
                sleep(100);
                break;
            default:
                break;
            }

            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

            snprintf(some_data, BUFSIZ + 1, "%f", time_spent);

            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            printf("Wrote %d bytes\n", data_processed);

            exit(EXIT_SUCCESS);
        }
        else
        { /* code parent process*/
            data_processed = read(file_pipes[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", data_processed, buffer);
        }
    }
}

void Program_Option()
{
    int data_processed;
    int file_pipes[2];
    char some_data[BUFSIZ + 1];
    char buffer[BUFSIZ + 1];
    pid_t fork_result;

    memset(buffer, '\0', sizeof(buffer));

    if (pipe(file_pipes) == 0)
    {

        fork_result = fork();

        if (fork_result == -1)
        {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == 0)
        { // Child process

            clock_t begin = clock();

            system("./estres2");

            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

            snprintf(some_data, BUFSIZ + 1, "%f", time_spent);

            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            printf("Wrote %d bytes\n", data_processed);

            exit(EXIT_SUCCESS);
        }
        else
        { // Parent process
            data_processed = read(file_pipes[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", data_processed, buffer);
        }
    }
    //exit(EXIT_SUCCESS);
}