#ifndef MENU_H
#define MENU_H

#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "calculator.h"
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

int data_processed;
int file_pipes[2];
char some_data[BUFSIZ + 1];
char buffer[BUFSIZ + 1];

void Menu();
void Petition_Option();
void Expression_Option();
void Program_Option();
bool executeFile();
int normal_distribution();
int find_range(float number);
void Solve_Petition(int range);
int Solve(long prob_success);
long random_at_most(long max);
long Get_Prob_Success(int level, int range, int instance, int count_p);
unsigned int rand_interval(unsigned int min, unsigned int max);

#endif