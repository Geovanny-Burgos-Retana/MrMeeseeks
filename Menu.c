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
    char peticion[BUFSIZ +1];
    float dificultad;
	printf ("Ingrese una petición:\n2");
	scanf("%s", &peticion );
    printf("Ingrese el grado de dificultad entre 0 y 100 o ingrese -1 para que sea calculado: ");
    scanf("%f", &dificultad);
    printf("dificultada :%f\n", dificultad);

    if(dificultad == -1){
        normal_distribution();
    }else{
        find_range(dificultad); 
    }

}
/*
Input: No parameters
Output: Random float number that follows a normal distribtion
Restrictions: Random numbers are generated from 1 to 100
Recuperado de: https://www.quora.com/How-do-I-write-a-program-in-C-to-generate-random-numbers-that-follow-a-normal-distribution-How-is-the-algorithm-solved
Notes: Its an aproximation of a normal distribution it dives the result/10 to obtain a score near de mue value
*/

void normal_distribution(){
    float count, sum, rand_number;
    for (count = 0, sum = 0; count < 10; ++count)
    {
        rand_number = rand() % 100 + 1;
        sum += rand_number;
    }
    sum = sum / 10 + 1;
    find_range(sum);
}

/*
Input: Random number generated by func normal_distribution
Outpu: 1 or 0 if the fork can't be create
Restrictions: Generate only  one fork
*/
int find_range(float number){
    printf("parametro find:%f\n", number);

    int range = 0;
    if( number == 0){
        range =-1;
    }else{
        if(0<number && number<45){
            range = 3;
            printf("entro rango3:%f\n", range);

        }else{
            if(45.01<number && number<85){
                range = 2;
                printf("entro rango2:%f\n", range);

            }else{
                if(85.01<number && number<100){
                    range = 1;
                    printf("entro rango1:%f\n", range);

                }
            }
        }
    }
    printf("number:%f\n", number);
    printf("range:%d\n", range);
    return range;
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