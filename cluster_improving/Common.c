
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>

void get_error_message(Status result) {
    char * message = NULL;
    switch (result) {
        case SUCCESS_STATUS_CODE:
            message = "\nSUCCESS";
            printf("%s", message);
            break;
        case MALLOC_FAILED_CODE:
            message = "\nMemory-Allocation(malloc) FAILED";
            printf("%s", message);
            break;
        case NULL_ARGUMENT_CODE:
            message = "\nNULL_ARGUMENT";
            printf("%s", message);
            break;
        case FOPEN_FAILED_CODE:
            message = "\nFAILED TO OPEN FILE";
            printf("%s", message);
            break;
        case FREAD_FAILED_CODE:
            message = "\nFAILED TO READ FILE";
            printf("%s", message);
            break;
        case FWRITE_FAILED_CODE:
            message = "\nFAILED TO WRITE INTO FILE";
            printf("%s", message);
            break;
        case INVALID_ARGUMENTS_CODE:
            message = "\nINVALID ARGUMENTS";
            printf("%s", message);
            break;
        case ZERO_DIVISION_CODE:
            message = "\nDIVISION BY ZERO";
            printf("%s", message);
            break;
        case GROUP_NOT_DIVISIBLE_CODE:
            message = "\nTHE GROUP IS NOT DIVISIBLE";
            printf("%s", message);
            break;
        case REACHED_MAX_NUMBER_OF_ITERATION:
            message = "\nREACHED_MAX_NUMBER_OF_ITERATION";
            printf("%s", message);
            break;
        case NEGATIVE_EIGEN_VALUE:
            message = "\nTHE GROUP IS NOT PARTITIONALIZED";
            printf("%s", message);
            break;
        case ZERO_NUMBER_OF_EDGES:
            message = "\nZERO_NUMBER_OF_EDGES";
            printf("%s", message);
            break;
        default:
            message = "\nUNKNOWN ERROR";
            printf("%s", message);
            break;
    }

}
allocations* alloc_allocations(int n) {
    Status status = INVALID_STATUS_CODE;
    int *k, *onces_helper, *output_array, *rows_helper, *relevant_indices_helper;
    double *f, *random_normalized_vector, *s;
    node **outer_array_helper;
    allocations *alloc = (allocations *) malloc(sizeof(allocations));
    if (NULL == alloc) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    k = (int *) malloc(n * sizeof(int));
    if (NULL == k) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    onces_helper = (int *) malloc(n * sizeof(int));
    if (NULL == onces_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    output_array = (int *) malloc(((2*n)+1) * sizeof(int));
    if (NULL == output_array) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    f = (double *) malloc(n * sizeof(double));
    if (NULL == f) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    random_normalized_vector = (double *) malloc(n * sizeof(double));
    if (NULL == random_normalized_vector) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    s = malloc(n * sizeof(double));
    if (NULL == s) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    rows_helper = (int*)malloc(sizeof(int) * n);
    if (NULL == rows_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    relevant_indices_helper = (int*)malloc(sizeof(int) * n);
    if (NULL == rows_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    outer_array_helper = (node **) malloc(n * sizeof(node *));
    if (NULL == outer_array_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    alloc->relevant_indices_helper = relevant_indices_helper;
    alloc->onces_helper = onces_helper;
    alloc->rows_helper = rows_helper;
    alloc->outer_array_helper = outer_array_helper;
    alloc->random_normalized_vector = random_normalized_vector;
    alloc->s = s;
    alloc->k = k;
    alloc->f = f;
    alloc->output_array = output_array;
    return alloc;
}
pointers* initialized_pointer(allocations *alloc, spmat *A){
    Status status = INVALID_STATUS_CODE;
    pointers * const main_pointer = (pointers*) malloc(sizeof(pointers));
    if (NULL == main_pointer) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    main_pointer->random_normalized_vector = alloc->random_normalized_vector;
    main_pointer->output_array = alloc->output_array;
    main_pointer->outer_array_helper = alloc->outer_array_helper;
    main_pointer->rows_helper = alloc->rows_helper;
    main_pointer->relevant_indices_helper = alloc->relevant_indices_helper;
    main_pointer->onces_helper = alloc->onces_helper;
    main_pointer->s = alloc->s;
    main_pointer->k = alloc->k;
    main_pointer->f = alloc->f;
    main_pointer->A_onces_num = A->onces_num;
    main_pointer->A_outer_array_helper = A->private;
    main_pointer->A_relevant_indices = A->relevant_indices;
    main_pointer->A = A;
    return main_pointer;

}
void outer_array_free(node** outer_array, int size) {
    node* next_node, *current_node;
    int  i;
    for (i = 0; i < size; ++i) {
        next_node = *(outer_array +i);
        current_node = next_node;
        while (current_node != NULL) {/*set currentNode to head, stop when empty*/
            next_node = next_node->next;
            free(current_node);
            current_node = next_node;
        }
        *(outer_array +i) = NULL;
    }

}


void free_allocations(pointers *main_pointer){
    free(main_pointer->random_normalized_vector);
    free(main_pointer->f);
    free(main_pointer->relevant_indices_helper);
    free(main_pointer->onces_helper);
    free(main_pointer->rows_helper);
    free(main_pointer->s);
    free(main_pointer->k);
    free(main_pointer->output_array);
    free(main_pointer->A_relevant_indices);
    free(main_pointer->A_onces_num);
    /*free(main_pointer->A);*/
    free(main_pointer->outer_array_helper);
    free(main_pointer->A_outer_array_helper);
    free(main_pointer);
}

