#include <stdio.h>
#include <stdlib.h>
#include "B.h"
#include "Algorithm2.h"

void modularity_division_rec(struct _spmat *A, int *k, int M, double *s, double *f, double L1_NORM, int number_of_1,
                             double *normalized_eig_vec, double *random_normalized_vec, int *rows_helper,
                             int *onces_helper, node **outer_array_helper, int *number_of_groups, int *number_of_written_elements, FILE *write_ptr, int *output_array, int L1_calculation){
    Status status = INVALID_STATUS_CODE;
    int i, n;
    n = A->n;
    node *node_pointer,**outer_array_pointer ;
    f_array(A, k, M, f);
    /*we have to calculate L1_NORM just on the first time*/
    L1_NORM = L1_calculation == 0 ? L1_NORM : L1_norm(A, k, M, f);
    status = algorithm2_modified(A, k, M, s, f, L1_NORM, &number_of_1, normalized_eig_vec, random_normalized_vec);

    if(status == NEGATIVE_EIGEN_VALUE || status == GROUP_NOT_DIVISIBLE_CODE){/*set this group to output file*/
        *(number_of_groups) += 1;
        /*inset group size first*/
        *(output_array + *(number_of_written_elements)) = n;
        *(number_of_written_elements) += 1;
        /*first element of the group*/
        outer_array_pointer = A->private;
        if(n > 1){
            node_pointer = *(outer_array_pointer + 1);
            *(output_array + *(number_of_written_elements)) = node_pointer->original;
            *(number_of_written_elements) += 1;
        }
        /*pushing the rest of the nodes*/
        node_pointer = *(outer_array_pointer);
        for(i = 0; i < n - 1; i++){
            *(output_array + *(number_of_written_elements)) = node_pointer->original;
            *(number_of_written_elements) += 1;
            node_pointer = node_pointer->next;

        }
    }

    /*here should comes modularity maximization*/

    else if(status == GROUP_NOT_DIVISIBLE_CODE){ /*stopping condition*/
        *(number_of_groups) += 1;


        free(A);
    }
    else{
        spmat *A1 = (spmat*)malloc(sizeof(spmat));
        if (NULL == A1) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            exit(status);
        }
        spmat *A2 = (spmat*)malloc(sizeof(spmat));
        if (NULL == A2) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            exit(status);
        }
        split_mat(A, A1, A2, &k, s, number_of_1, &rows_helper, onces_helper, &outer_array_helper);

        modularity_division_rec(A1, k, M, s, f, L1_NORM,number_of_1,normalized_eig_vec, random_normalized_vec, rows_helper,
                                onces_helper, outer_array_helper, number_of_groups, number_of_written_elements, write_ptr, output_array, 0);
        modularity_division_rec(A2, k + number_of_1, M, s, f, L1_NORM,number_of_1,normalized_eig_vec, random_normalized_vec,
                                rows_helper, onces_helper, outer_array_helper, number_of_groups, number_of_written_elements, write_ptr, output_array, 0);



        }
}
















