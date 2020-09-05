//
// Created by barak on 26/08/2020.
//

#include "Common.h"
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>
#include "SparseMatrix.h"

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
        case REACHED_MAX_NUMBER_OF_ITERATION:
            message = "REACHED_MAX_NUMBER_OF_ITERATION";
            printf("%s", message);
            break;
        case NEGATIVE_EIGEN_VALUE:
            message = "THE GROUP IS NOT PARTITIONALIZED - negative eigen value";
            printf("%s", message);
            break;
        case ZERO_NUMBER_OF_EDGES:
            message = "ZERO_NUMBER_OF_EDGES";
            printf("%s", message);
            break;


        default:
            message = "UNKNOWN ERROR";
            printf("%s", message);
            break;
    }

}
/*
void alloc_allocations(int n){
    Status status = INVALID_STATUS_CODE;
    int *k = (int *) malloc(n * sizeof(int));
    if (NULL == k) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    int *onces_helper = (int *) malloc(n * sizeof(int));
    if (NULL == onces_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    double *f = (double *) malloc(n * sizeof(double));
    if (NULL == f) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    double *random_normalized_vector = (double *) malloc(n * sizeof(double));
    if (NULL == random_normalized_vector) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    double *normalized_eig_vec = malloc(n * sizeof(double));
    if (NULL == normalized_eig_vec) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    double *s = malloc(n * sizeof(double));
    if (NULL == s) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    int *rows_helper = (int*)malloc(sizeof(int) * n);
    if (NULL == rows_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    int *relevant_indices_helper = (int*)malloc(sizeof(int) * n);
    if (NULL == rows_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    node **outer_array_helper = (node **) calloc(n, sizeof(node *));
    if (NULL == outer_array_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
}

void free_allocations(allocations *alloc){
    free
}
*/