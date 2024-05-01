//error_handling.c
#include <stdio.h>
#include "error_handling.h"

void print_error(ErrorCode error_code) {
    switch (error_code) {
        case NO_ERROR:
            printf("No error.\n");
            break;
        case INVALID_COMMAND:
            printf("Error: Invalid command.\n");
            break;
        case READ_ERROR:
            printf("Error: Read error or EOF.\n");
            break;
        case CD_FAILED:
            printf("Error: Error in 'CD' command.\n");
            break;
        case EXEC_FAILED:
            printf("Error: Error in fork 'LS'.\n");
            break;
        case BATCH_FAILED:
            printf("Error: Error in batch file.\n");
            break;
        case PATH_FAILED:
            printf("Error: Error in current path to prompt.\n");
            break;
        case DIRECTORY_FAILED:
            printf("Error: Error Error opening directory.\n");
            break;
        case MAX_PATHS_LIMIT:
            printf("Error: Maximum path limit reached.\n");
            break;
        case MALLOC_FAILED:
            printf("Error: Malloc failed.\n");
            break;
        case FORK_FAILED:
            printf("Error: Fork failed.\n");
            break;
        default:
            printf("Unknown error.\n");
            break;
    }
}
