#include "Menu.h"

void Menu()
{    
    if (pipe(file_pipes) != 0)
        printf("Failed creating pipe!!");

    memset(buffer, '\0', sizeof(buffer));

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
	printf ("Ingrese una petición: ");
	scanf("%s", &peticion );
    printf("Ingrese dificultad entre 0 y 100 o ingrese -1 para que sea calculado: ");
    scanf("%f", &dificultad);
    printf("Dificultad: %f\n", dificultad);

    int range;

    if(dificultad == -1){
        range = normal_distribution();
    }else{
        range = find_range(dificultad); 
    }
    
    if (range == 1) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), 1, 1);

            clock_t begin = clock();

            float tiempo = ((float)rand()/(float)(RAND_MAX)*5.0);
            if (tiempo < 0.5)
                tiempo++;

            sleep(tiempo);

            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

            snprintf(some_data, BUFSIZ + 1, "%f", time_spent + tiempo);

            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            printf("Wrote %d bytes\n", data_processed);

            exit(EXIT_SUCCESS);
        } else {
            data_processed = read(file_pipes[0], buffer, BUFSIZ);
            printf("Read %d bytes. Time spend: %s\n", data_processed, buffer);
        }
        

    } else {
        Solve_Petition(range);
    }

}

int *count = 0;
int *solved = 0;
sem_t *semaphore;

void Solve_Petition(int range) {
    count = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    solved = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    semaphore = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(semaphore, 1, 1);//Initialice sempahore

    pid_t pid_1, pid_2, pid_3, box;
    int level = 1; // Level 2 o 3
    int id;
    float tiempo = ((float)rand()/(float)(RAND_MAX)*5.0);
    if (tiempo < 0.5)
        tiempo++;
    
    while(level < range) {

        box = getpid();
        pid_1 = fork();


        if (pid_1 != 0) {
            
            pid_2 = fork();

            if (pid_2 != 0) {
                
                pid_3 = fork();                

                if (pid_3 == 0) {                    
                    (*count)+= 1;
                    id = (*count);
                    printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *count, 3);
                    //printf("[son] pid %d from [parent] pid %d [count] sons, grandsons ... #%d [instance] son #%d\n", getpid(), getppid(), *count, 3);
                    level += 1;
                    // SOLVE THIRD CHILD
                    long prob_success = Get_Prob_Success(level, range, 3, id);

                    if (Solve(prob_success)) {
                        printf("All done!! Mr Meeseeks (%d, %d, %d, %d). Solved time: %f\n", getpid(), getppid(), *count, 2, tiempo);                        exit(EXIT_SUCCESS);
                    }
                }
            }
            if (pid_2 == 0) {
                (*count)+= 1;
                id = (*count);
                printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *count, 2);
                //printf("[son] pid %d from [parent] pid %d [count] sons, grandsons ... #%d [instance] son #%d\n", getpid(), getppid(), *count, 2);
                level += 1;
                // SOLVE SECOND CHILD
                long prob_success = Get_Prob_Success(level, range, 2, id);
                
                if (Solve(prob_success)) {
                    printf("All done!! Mr Meeseeks (%d, %d, %d, %d). Solved time: %f\n", getpid(), getppid(), *count, 2, tiempo);
                    exit(EXIT_SUCCESS);
                }

            }
        }
        if (pid_1 != 0 && pid_2 != 0 && pid_3 != 0) {
            break;
        }
        if (pid_1 == 0) {
            (*count)+= 1;
            id = (*count);
            printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *count, 1);
            //printf("[son] pid %d from [parent] pid %d [count] sons, grandsons ... #%d [instance] son #%d\n", getpid(), getppid(), *count, 1);
            level += 1;
            // SOLVE FIRST CHILD            

            long prob_success = Get_Prob_Success(level, range, 1, id);
            
            if (Solve(prob_success)) {
                printf("All done!! Mr Meeseeks (%d, %d, %d, %d). Solved time: %f\n", getpid(), getppid(), *count, 2, tiempo);
                exit(EXIT_SUCCESS);
            }
            
        }
    }
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2, NULL, 0);
    waitpid(pid_3, NULL, 0);
    
        kill(pid_1, SIGKILL);
        kill(pid_2, SIGKILL);
        kill(pid_3, SIGKILL);
    
}

long Get_Prob_Success(int level, int range, int instance, int count_p) {
    long result;
    if (level == 2 && range == 2) {
        result = 33*instance;
    } else if (level == 2 && range == 3) {
        result = 33*instance/level/3/range;
    } else {
        result = 8*count_p;
    }
    //printf("Result = %d\n", result);
    return result;
}

// https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range
long random_at_most(long max) {
    unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

    long x;
    do {
    x = random();
    }
    // This is carefully written not to overflow
    while (num_rand - defect <= (unsigned long)x);

    // Truncated division is intentional
    return x/bin_size;
}

int Solve(long prob_success) {
    sem_wait(semaphore);
    //printf("Hola soy el proceso. (%d, %d, %d, %d)\n", getpid(), getppid(), *count);
    if ((*solved) == 1) {
        sem_post(semaphore);
        exit(EXIT_SUCCESS);
    } else {
        srand(getpid()); 
        long cost = random_at_most(100);
        printf("Cost %d < %d\n", cost, prob_success);
        if (cost < prob_success) {
            (*solved) = 1;
            sem_post(semaphore);
            return 1;
        } else {
            sem_post(semaphore);
            return 0;
        }
    }
}

/*
Input: No parameters
Output: Random float number that follows a normal distribtion
Restrictions: Random numbers are generated from 1 to 100
Recuperado de: https://www.quora.com/How-do-I-write-a-program-in-C-to-generate-random-numbers-that-follow-a-normal-distribution-How-is-the-algorithm-solved
Notes: Its an aproximation of a normal distribution it dives the result/10 to obtain a score near de mue value
*/

int normal_distribution(){
    float count_nd, sum, rand_number;
    for (count_nd = 0, sum = 0; count_nd < 10; ++count_nd)
    {
        rand_number = rand() % 100 + 1;
        sum += rand_number;
    }
    sum = sum / 10 + 1;
    return (find_range(sum));
}

/*
Input: Random number generated by func normal_distribution
Outpu: 1 or 0 if the fork can't be create
Restrictions: Generate only  one fork
*/
int find_range(float number){
    //printf("parametro find:%f\n", number);

    int range = 0;
    if( number == 0){
        range =-1;
    }else{
        if(0<number && number<45){
            range = 3;
            //printf("entro rango3:%f\n", range);

        }else{
            if(45.01<number && number<85){
                range = 2;
                //printf("entro rango2:%f\n", range);

            }else{
                if(85.01<number && number<100){
                    range = 1;
                    //printf("entro rango1:%f\n", range);

                }
            }
        }
    }
    //printf("number:%f\n", number);
    //printf("range:%d\n", range);
    return range;
}


void Expression_Option()
{

    /*int data_processed;
    int file_pipes[2];
    char some_data[BUFSIZ + 1];
    char buffer[BUFSIZ + 1];*/
    /*fork and child process*/
    pid_t pid;

    //memset(buffer, '\0', sizeof(buffer));

    if (pipe(file_pipes) == 0)
    {
        pid = fork();

        if (pid == 0)
        { /* code child process*/
            printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), 1, 1);

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
    /*int data_processed;
    int file_pipes[2];
    char some_data[BUFSIZ + 1];
    char buffer[BUFSIZ + 1];*/
    pid_t fork_result;

    //memset(buffer, '\0', sizeof(buffer));

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

            printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), 1, 1);

            clock_t begin = clock();
            //system("x-terminal-emulator -e \"/home/salman/find_location/start_yarp.sh\"");
            //system("./estres2");
            printf("Ingrese la ruta de un ejecutable: \n");
            printf("/home/tanzanita/Documents/holaMundo \n");
            printf("Hola Mundo \n");
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