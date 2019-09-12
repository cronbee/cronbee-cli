#include "../include/main.h"
#include "../include/command.h"
#include "../include/cronbee.h"

int main(int argc, char **argv) {
    int c;
    struct options options = {false, false, NULL, NULL, _DEFAULT_LINE_COUNT_, NULL};

    if(argc < _MIN_ARGS_COUNT_) {
        printUsage(argv);
        exit(EXIT_FAILURE);
    }

    while ((c = getopt(argc, argv, "+vpt:n:u:e:h?")) != -1) {
        switch (c) {
            case 'v':
                options.verbose = true;
                break;
            case 'p':
                options.ping = true;
                break;
            case 't':
                options.token = optarg;
                break;
            case 'u':
                options.uuid = optarg;
                break;
            case 'e':
                options.event = optarg;
                break;
            case 'n':
                options.lines = atoi(optarg);
                if(options.lines < 1) {
                    printError("-n should be greater than 0.");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
            case '?':
                printUsage(argv);
                exit(EXIT_FAILURE);
            default:
                abort();

        }
    }

    if(options.uuid == NULL) {
        printError("No uuid specified.\n");
        return EXIT_FAILURE;
    }

    if(options.ping == true && options.token != NULL) {
        printError("The -p option is not compatible with the -t option.\n");
        return EXIT_FAILURE;
    }

    if(options.ping == true && options.event != NULL) {
        printError("The -p option is not compatible with the -e option.\n");
        return EXIT_FAILURE;
    }

    if(options.ping == true) {
        cronbee_ping(options.uuid, &options);
        return EXIT_SUCCESS;
    }

    if(options.event != NULL && options.token == NULL) {
        if(strncmp(options.event, "start", 5) == 0) {
            cronbee_start(&options);
            fprintf(stdout, "%s", options.token);
            return EXIT_SUCCESS;
        }
    }

    if(options.token != NULL) {
        if(options.event != NULL) {
            cronbee_event(&options, options.event);
            executeCommand(argv, optind, &options);
            return EXIT_SUCCESS;
        }
        cronbee_stop(&options);
        return EXIT_SUCCESS;
    }
    else if(options.event != NULL) {
        printError("The -e option can't be used without the -t option.\n");
        return EXIT_FAILURE;
    }

    cronbee_start(&options);
    executeCommand(argv, optind, &options);
    cronbee_stop(&options);
    return 0;
}

void printUsage(char **argv) {
    fprintf(stderr, "Usage:\t%s -u [monitor_id] [command] [args]\n"
                    "\t-e set the event name to send\n"
                    "\t-h display this message\n"
                    "\t-n set the number of lines to display (default 200)\n"
                    "\t-p send a ping\n"
                    "\t-t specify token\n"
                    "\t-u specifies monitor id\n"
                    "\t-v display messages\n\n"
                    , argv[0]);
}

void printError(const char* error) {
    fprintf(stderr, "\x1b[31m[error]: %s\x1b[0m", error);
}

void printInfo(const char* info, struct options *options) {
    if(options->verbose == false)
        return;
    fprintf(stdout, "\x1b[32m[info]: %s\x1b[0m\n", info);
}