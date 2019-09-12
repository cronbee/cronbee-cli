//
// Created by Pierre on 8/27/19.
//

#include "../include/command.h"
#include "../include/cronbee.h"

int executeCommand(char **argv, int startValue, struct options* options){
    int stdOut[2], stdErr[2];

    if(pipe(stdOut) || pipe(stdErr))
        return EXIT_FAILURE;

    pid_t pid = fork();

    if(pid > 0) {
        parentProcess(pid, stdOut, stdErr, options);
    }
    else if(pid == 0){
        childProcess(stdOut, stdErr, argv, startValue);
    }

    return EXIT_SUCCESS;
}

void childProcess(int stdOut[], int stdErr[], char** argv, int startValue) {
    dup2(stdOut[1], STDOUT_FILENO);
    dup2(stdErr[1], STDERR_FILENO);

    execvp(argv[startValue], &argv[startValue]);
    perror("Can't load process.");
}

void parentProcess(int pid, int stdOut[], int stdErr[], struct options* options) {
    char buffer[2] = {0};
    int childStatus = -1;
    char *line = calloc(2, sizeof(char));
    struct timeval val = {3, 0};
    struct lines *lines = init(options->lines);

    do{
        fd_set fdOut, fdErr;
        FD_ZERO(&fdOut);
        FD_SET(stdOut[0], &fdOut);
        FD_ZERO(&fdErr);
        FD_SET(stdOut[0], &fdErr);

        int outStatus = select(4, &fdOut, NULL, NULL, &val);
        int errStatus = select(4, &fdErr, NULL, NULL, &val);

        if(outStatus == 1) {
            while(outStatus > 0) {
                outStatus = select(4, &fdOut, NULL, NULL, &val);
                if(outStatus > 0) {
                    read(stdOut[0], buffer, 1);
                    line = realloc(line, strlen(line) + 2);
                    strcat(line, buffer);

                    if(buffer[0] == '\n') {
                        addLine(lines, line);
                    }
                }
            }
            fprintf(stdout, "%s", getLines(lines));
        }

        if(errStatus == 1) {
            while(errStatus > 0) {
                errStatus = select(4, &fdErr, NULL, NULL, &val);
                if(errStatus > 0) {
                    read(stdErr[0], buffer, 1);
                    line = realloc(line, strlen(line) + 2);
                    strcat(line, buffer);

                    if(buffer[0] == '\n') {
                        addLine(lines, line);
                    }
                }
            }
            fprintf(stderr, "%s", getLines(lines));
        }
    }
    while (waitpid(pid, &childStatus, WNOHANG) == 0);

    free(line);
    for(int i = 0; i < lines->max; i++)
        free(lines->data[i]);
    free(lines->data);
    free(lines);
}
