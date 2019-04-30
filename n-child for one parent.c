#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>

int *count = 0;
int *solved = 0;
sem_t *semaphore;

long Get_Prob_Success(int level, int range, int instance, int count);

int main() {

    count = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    solved = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    semaphore = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(semaphore, 1, 1);//Initialice sempahore

    pid_t pid_1, pid_2, pid_3;
    int range = 3; // Range 2 o 3
    int level = 1; // Level 2 o 3
    int id;
    
    while(level < range) {

        pid_1 = fork();        

        if (pid_1 != 0) {
            
            pid_2 = fork();

            if (pid_2 != 0) {
                
                pid_3 = fork();                

                if (pid_3 == 0) {                    
                    (*count)+= 1;
                    id = (*count);
                    printf("[son] pid %d from [parent] pid %d [count] sons, grandsons ... #%d [instance] son #%d\n", getpid(), getppid(), *count, 3);
                    level += 1;
                    // SOLVE THIRD CHILD
                    long prob_success = Get_Prob_Success(level, range, 3, id);

                    if (Solve(prob_success)) {
                        printf("All done!! Mr Meeseeks (%d, %d, %d, %d)\n", getpid(), getppid(), *count, 1);
                        exit(EXIT_SUCCESS);
                    }
                }
            }
            if (pid_2 == 0) {
                (*count)+= 1;
                id = (*count);
                printf("[son] pid %d from [parent] pid %d [count] sons, grandsons ... #%d [instance] son #%d\n", getpid(), getppid(), *count, 2);
                level += 1;
                // SOLVE SECOND CHILD
                long prob_success = Get_Prob_Success(level, range, 2, id);
                
                if (Solve(prob_success)) {
                    printf("All done!! Mr Meeseeks (%d, %d, %d, %d)\n", getpid(), getppid(), *count, 2);
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
            printf("[son] pid %d from [parent] pid %d [count] sons, grandsons ... #%d [instance] son #%d\n", getpid(), getppid(), *count, 1);
            level += 1;
            // SOLVE FIRST CHILD            

            long prob_success = Get_Prob_Success(level, range, 1, id);
            
            if (Solve(prob_success)) {
                printf("All done!! Mr Meeseeks (%d, %d, %d, %d)\n", getpid(), getppid(), *count, 1);
                exit(EXIT_SUCCESS);
            }
            
        }
    }
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2, NULL, 0);
    waitpid(pid_3, NULL, 0);
    
    return 0;
    // Received the info of the child that solved the petition
}

long Get_Prob_Success(int level, int range, int instance, int count) {
    long result;
    if (level == 2 && range == 2) {
        result = 33*instance;
    } else if (level == 2 && range == 3) {
        result = 33*instance/level/3/range;
    } else {
        result = 8*count;
    }
    printf("Result = %d\n", result);
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
    printf("Hola soy el proceso. (%d, %d, %d, %d)\n", getpid(), getppid(), *count);
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



/*int main() {

    count = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < 3; i++) {
        sleep(i*150);
        if (fork() == 0){            
            (*count)+= 1;
            int level2 = 
            int instance = 1 + i;
            //printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *count, instance);
            printf("[son] pid %d from [parent] pid %d [count] sons, grandsons ... #%d [instance] son #%d\n", getpid(), getppid(), *count, instance);
            for (int i = 0; i < 3; i++) {
                if (fork() == 0) {
                    (*count)+= 1;
                    int instance2 = 1 + i;
                    //printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *count, instance2);
                    printf("[son] pid %d from [parent] pid %d [count] sons, grandsons ... #%d [instance] son #%d\n", getpid(), getppid(), *count, instance2);
                    
                    break;
                }
            }
            for (int i = 0; i < 3; i++)
                wait(NULL);            
            break;
        }
    }
    for (int i = 0; i < 3; i++)
        wait(NULL);
    
}*/