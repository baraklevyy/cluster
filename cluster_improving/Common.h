//
// Created by barak on 26/08/2020.
//

#ifndef CLUSTER_IMPROVING_COMMON_H
#define CLUSTER_IMPROVING_COMMON_H

#define IS_POSITIVE(X) ((X) > 0.00001)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#include "SparseMatrix.h"

/*Creating Linked-list. Each cell contain the column index, data and next reference*/


typedef enum _Status {
    INVALID_STATUS_CODE = -1,
    SUCCESS_STATUS_CODE = 0,
    MALLOC_FAILED_CODE,
    NULL_ARGUMENT_CODE,
    FOPEN_FAILED_CODE,
    FREAD_FAILED_CODE,
    FWRITE_FAILED_CODE,
    INVALID_ARGUMENTS_CODE,
    ZERO_DIVISION_CODE,
    GROUP_NOT_DIVISIBLE_CODE,
    REACHED_MAX_NUMBER_OF_ITERATION,
    NEGATIVE_EIGEN_VALUE,
    ZERO_NUMBER_OF_EDGES,
    //COUNTER FOR ERRORS
    STATUS_CODE_COUNT
}Status;
void get_error_message(Status result);

typedef struct _allocations {
    int *k;
    double *s;
    double *f;
    double *random_normalized_vector;
    int *onces_helper;
    int *rows_helper;
    int *relevant_indices_helper;
    int *output_array;
    node **outer_array_helper;
} allocations;
typedef struct _pointers {
    int *k;
    double *s;
    double *f;
    double *random_normalized_vector;
    int *onces_helper;
    int *rows_helper;
    int *relevant_indices_helper;
    int *output_array;
    node **outer_array_helper;

    int *A_onces_num;
    int *A_relevant_indices;
    node **A_outer_array_helper;
    spmat *A;


} pointers;
pointers* initizlized(allocations *alloc, spmat *A);
allocations* alloc_allocations(int n);
void free_allocations(pointers *main_pointer);
void outer_array_free(node** outer_array, int size);


#endif //CLUSTER_IMPROVING_COMMON_H
