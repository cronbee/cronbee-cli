//
// Created by Pierre on 8/27/19.
//

#ifndef CRONBEE_MAIN_H
#define CRONBEE_MAIN_H
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define _DEFAULT_LINE_COUNT_ 200
#define _MIN_ARGS_COUNT_ 2

struct options {
    bool verbose;
    bool ping;
    char *uuid;
    char *event;
    int lines;
    char* token;
};
void printUsage(char**);
void printError(const char*);
void printInfo(const char*, struct options*);
void setEnvVar(char*, char*);

#endif //CRONBEE_MAIN_H
