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

int data_processed;
int file_pipes[2];
char some_data[BUFSIZ + 1];
char buffer[BUFSIZ + 1];

void Menu();
void Petition_Option();
void Expression_Option();
void Program_Option();
bool executeFile();
void normal_distribution();
int find_range(float number);

#endif