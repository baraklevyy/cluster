#include <stdio.h>
#include <stdlib.h>
#include "B.h"
#include "Algorithm2.h"
#include "ModularityMaximization.h"


void modularity_division_rec(struct _spmat *A, int *k, struct _allocations *alloc, int M, double L1_NORM, int number_of_1,
                             int *number_of_groups, int *number_of_written_elements){
    Status status;
    spmat *A1, *A2;
    int i, n;
    double reuse_sum;
    status = INVALID_STATUS_CODE;
    n = A->n;

    /* f has to be changes from step to another*/
    f_array(A, k, M, alloc->f, &reuse_sum);
    /*we have to calculate L1_NORM just on the first iteration, L1_NORM set to -1.0 in main just for the first time*/
    /*L1_NORM = L1_NORM == -1.0 ? L1_norm(A, k, M, alloc->f) : L1_NORM ;*/
    L1_NORM =L1_norm(A, k, M, alloc->f, reuse_sum);
    /*matrix with a single element doesnt have to enter clustering Algorithms*/
    if(n != 1){
        status = algorithm2(A, k, M, alloc, L1_NORM);
        modularity_max1(A, k, M, alloc->s, alloc->rows_helper, alloc->onces_helper, &number_of_1);
    }

    /*inserting relevant group into the output array*/
    if(n == number_of_1 || number_of_1 == 0 || n == 1){
        *(number_of_groups) += 1;
        /*inset group size first*/
        *(alloc->output_array + *(number_of_written_elements)) = n;
        *(number_of_written_elements) += 1;
        for(i = 0; i < n; i++){
            *(alloc->output_array + *(number_of_written_elements)) = *(A->relevant_indices + i);
            *(number_of_written_elements) += 1;
        }
        outer_array_free(A->private, n);
    }
    /*enter to recursion*/
    else {
        A1 = (spmat *) malloc(sizeof(spmat));
        if (NULL == A1) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            exit(status);
        }
        A2 = (spmat *) malloc(sizeof(spmat));
        if (NULL == A2) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            exit(status);
        }
        /*splitting into two sparse matrices with corresponding elements*/
        split_mat(A, A1, A2, k, alloc->s, number_of_1, alloc->rows_helper, alloc->onces_helper, alloc->outer_array_helper,alloc->relevant_indices_helper);
        /*recursion calls*/
        modularity_division_rec(A1, k, alloc, M, L1_NORM, number_of_1, number_of_groups, number_of_written_elements);
        modularity_division_rec(A2, k + number_of_1 , alloc, M, L1_NORM, number_of_1, number_of_groups, number_of_written_elements);
    }
    free(A);
}
















