#include <stdio.h>
#include <stdlib.h>
#include "B.h"
#include "Algorithm2.h"
#include "ModularityMaximization.h"

void modularity_division_rec(struct _spmat *A, int *k, int M, double *s, double *f, double L1_NORM, int number_of_1,
                             double *normalized_eig_vec, double *random_normalized_vec, int *rows_helper,
                             int *onces_helper, node **outer_array_helper, int *number_of_groups,
                             int *number_of_written_elements, FILE *write_ptr, int *output_array, int *relevant_indices_helper){
    Status status = INVALID_STATUS_CODE;
    int i, n;
    n = A->n;
    /* f has to be changes from step to another*/
    f_array(A, k, M, f);
    /*we have to calculate L1_NORM just on the first iteration, L1_NORM set to -1.0 in main just for the first time*/
    L1_NORM = L1_NORM == -1.0 ? L1_norm(A, k, M, f) : L1_NORM ;

    status = algorithm2_modified(A, k, M, s, f, L1_NORM, &number_of_1, normalized_eig_vec, random_normalized_vec);
    if(status == NEGATIVE_EIGEN_VALUE || n == number_of_1){
        *(number_of_groups) += 1;
        /*inset group size first*/
        *(output_array + *(number_of_written_elements)) = n;
        *(number_of_written_elements) += 1;
        for(i = 0; i < n; i++){
            *(output_array + *(number_of_written_elements)) = *(A->relevant_indices + i);
            *(number_of_written_elements) += 1;
        }
        free(A);
    }
    else {
        modularity_max(A, k, M, s, rows_helper, onces_helper, &number_of_1);
        /*temporary number_of_1 counting*/
        number_of_1 = 0;
        for (i = 0; i < n; i++) {
            if (*(s + i) == 1.0)
                number_of_1++;
        }
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
        split_mat(A, A1, A2, &k, s, number_of_1, &rows_helper, onces_helper, &outer_array_helper,
                  relevant_indices_helper);
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
        modularity_division_rec(A1, k, M, s, f, L1_NORM, number_of_1, normalized_eig_vec, random_normalized_vec,
                                rows_helper,onces_helper, outer_array_helper, number_of_groups,
                                number_of_written_elements, write_ptr, output_array, relevant_indices_helper);

        modularity_division_rec(A2, k + number_of_1, M, s, f, L1_NORM, number_of_1, normalized_eig_vec,
                                random_normalized_vec, rows_helper, onces_helper, outer_array_helper,
                                number_of_groups, number_of_written_elements, write_ptr, output_array,
                                relevant_indices_helper);
        }
    }
















