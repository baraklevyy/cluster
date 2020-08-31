#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "B.h"
#include "Common.h"
#include "vector.h"
#include "Stack.h"
#include "SparseMatrix.h"
#include "Algorithm2.h"


void modularity_division_rec(struct _spmat *A, int *k, int M, double *s, double *f, double L1_NORM, int *number_of_1, double *random_vector, double *normalized_eig_vec,
                             int *rows_helper, int *onces_helper, node **outer_array_helper){
    Status status = INVALID_STATUS_CODE;
    status = algorithm2_modified(A, k, M, s, f, L1_NORM, number_of_1, random_vector, normalized_eig_vec);


    if(status == GROUP_NOT_DIVISIBLE_CODE){ /*stopping condition*/

    }
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
    else{
        split_mat(A, A1, A2, k, s, *(number_of_1), rows_helper, onces_helper, outer_array_helper);
        /*
        modularity_division_rec(A1);
        modularity_division_rec(A2);
        */

    }




}
















