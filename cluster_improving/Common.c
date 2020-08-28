//
// Created by barak on 26/08/2020.
//

#include "Common.h"
#include "Common.h"
#include <stdio.h>


void get_error_message(Status result) {

    char * message = NULL;

    switch (result) {
        case SUCCESS_STATUS_CODE:
            message = "SUCCESS";
            printf("%s", message);
            break;
        case MALLOC_FAILED_CODE:
            message = "Memory-Allocation(malloc) FAILED";
            printf("%s", message);
            break;
        case NULL_ARGUMENT_CODE:
            message = "NULL_ARGUMENT";
            printf("%s", message);
            break;
        case FOPEN_FAILED_CODE:
            message = "FAILED TO OPEN FILE";
            printf("%s", message);
            break;
        case FREAD_FAILED_CODE:
            message = "FAILED TO READ FILE";
            printf("%s", message);
            break;
        case FWRITE_FAILED_CODE:
            message = "FAILED TO WRITE INTO FILE";
            printf("%s", message);
            break;
        case INVALID_ARGUMENTS_CODE:
            message = "INVALID ARGUMENTS";
            printf("%s", message);
            break;
        case ZERO_DIVISION_CODE:
            message = "DIVISION BY ZERO";
            printf("%s", message);
            break;
        case GROUP_NOT_DIVISIBLE_CODE:
            message = "THE GROUP IS NOT DIVISIBLE";
            printf("%s", message);
            break;
        default:
            message = "UNKNOWN ERROR";
            printf("%s", message);
            break;
    }

}

