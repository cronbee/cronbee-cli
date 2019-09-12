//
// Created by Pierre on 8/30/19.
//

#ifndef CRONBEE_LINES_H
#define CRONBEE_LINES_H

#include <stdlib.h>
#include <string.h>
struct lines {
    int index;
    int max;
    char** data;
};

struct lines* init(int nbLines);

void addLine(struct lines*, char* line);

char* getLines(struct lines*);

#endif //CRONBEE_LINES_H
