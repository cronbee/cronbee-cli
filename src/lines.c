//
// Created by Pierre on 8/30/19.
//

#include "../include/lines.h"

struct lines* init(int nbLines) {
    struct lines *lines = malloc(sizeof(struct lines));
    lines->index = 0;
    lines->max = nbLines;
    lines->data = calloc(nbLines, sizeof(char*));
    for(int i = 0; i < lines->max; i++){
        lines->data[i] = calloc(2, sizeof(char));
    }
    return lines;
}

void addLine(struct lines* lines, char* line) {
    int idx = lines->index%lines->max;
    lines->data[idx] = realloc(lines->data[idx], strlen(line) + 1);
    lines->data[idx] = calloc(strlen(line) + 1, sizeof(char));
    strcat(lines->data[idx], line);
    lines->index++;
    memset(line, 0, 2);
}

char* getLines(struct lines* lines) {
    char* result = calloc(lines->max + 1, sizeof(char));
    for(int i = 0; i < lines->max; i++) {
        char *line = lines->data[(lines->index + i)%lines->max];
        result = realloc(result, strlen(result) + strlen(line) + 1);
        strcat(result, line);
    }
    return result;
}
