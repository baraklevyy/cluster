#include <stdio.h>
#include <stdlib.h>
#include "B.h"
#include "Algorithm2.h"
#include "ModularityMaximization.h"

void modularity_division_rec(struct _spmat *A, int *k, struct _allocations *alloc, int M, double L1_NORM, int number_of_1,
                             int *number_of_groups, int *number_of_written_elements){
    Status status = INVALID_STATUS_CODE;
    int i, n;
    n = A->n;


    /* f has to be changes from step to another*/
    f_array(A, alloc->k, M, alloc->f);
    /*we have to calculate L1_NORM just on the first iteration, L1_NORM set to -1.0 in main just for the first time*/
    L1_NORM = L1_NORM == -1.0 ? L1_norm(A, alloc->k, M, alloc->f) : L1_NORM ;

    status = algorithm2_modified(A, alloc->k, M, alloc, L1_NORM, &number_of_1);

    modularity_max(A, alloc->k, M, alloc->s, alloc->rows_helper, alloc->onces_helper, &number_of_1);
/*
    for(i=0;i<n;i++){
        printf("\ns[%d]=%f",i,*(alloc->s + i));
        fflush(stdout);
    }
*/
    /*temporary number_of_1 counting*/
    /*no isolated nodes*/
    if(n == number_of_1 || number_of_1 == 0){
        *(number_of_groups) += 1;
        /*inset group size first*/
        *(alloc->output_array + *(number_of_written_elements)) = n;
        *(number_of_written_elements) += 1;
        for(i = 0; i < n; i++){
            *(alloc->output_array + *(number_of_written_elements)) = *(A->relevant_indices + i);
            *(number_of_written_elements) += 1;
        }
        free(A);
    }
    else {

        spmat *A1 = (spmat *) malloc(sizeof(spmat));
        if (NULL == A1) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            exit(status);
        }
        spmat *A2 = (spmat *) malloc(sizeof(spmat));
        if (NULL == A2) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            exit(status);
        }
        split_mat(A, A1, A2, &(alloc->k), alloc->s, number_of_1, &(alloc->rows_helper), &(alloc->onces_helper), &(alloc->outer_array_helper),
                  &(alloc->relevant_indices_helper));

        /*
        nnouterarry = A->private;
        for (i = 0; i < A->n; ++i) {
            nnpointer = ((node*)A->private + i);
            nnpointer = nnouterarry[i];
            v_elem_num = *(A->onces_num + i);
            index = 0;
            printf("\n%s ","|->");
            fflush(stdout);
            for (index= 0; index < v_elem_num; index++) {
                printf("%d ->",nnpointer->original);
                fflush(stdout);
                nnpointer = nnpointer->next;
            }
        }
         */
            /*
        for(i=0;i<A1->n;i++){
            printf("A1.relevant[%d] = %d \n", i, *(A1->relevant_indices + i));
            fflush(stdout);
        }
        for(i=0;i<A2->n;i++){
            printf("A1.relevant[%d] = %d \n", i, *(A2->relevant_indices + i));
            fflush(stdout);
        }
             */

            modularity_division_rec(A1, alloc->k, alloc, M, L1_NORM, number_of_1, number_of_groups, number_of_written_elements);
            k = alloc->k + number_of_1;
            modularity_division_rec(A2, k , alloc, M, L1_NORM, number_of_1, number_of_groups, number_of_written_elements);
        }
    }
















