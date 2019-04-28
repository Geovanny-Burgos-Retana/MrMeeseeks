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

void Menu();
void Petition_Option();
void Expression_Option();
void Program_Option();
bool executeFile();

#endif