//
// Created by Pierre on 8/27/19.
//

#ifndef CRONBEE_COMMAND_H
#define CRONBEE_COMMAND_H

#include <zconf.h>
#include <sys/wait.h>
#include <sys/time.h>
#include "main.h"
#include "lines.h"

int executeCommand(char**, int, struct options*);
void childProcess(int[], int[], char**, int);
void parentProcess(int, int[], int[], struct options*);
#endif //CRONBEE_COMMAND_H
