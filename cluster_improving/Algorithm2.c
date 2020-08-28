#include <stdlib.h>
#include "Algorithm2.h"

Status algorithm2_modified(const struct _spmat *A, const int *k, int M, double *s, double *f, double l1_norm, int *number_of_1) {
    Status status = INVALID_STATUS_CODE;
    int n = A->n;


    double *normalized_eig_vec;
    double eig_val;
    int i;
    normalized_eig_vec = (double*)malloc(n * sizeof(double));
    if (NULL == normalized_eig_vec) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    // calculate eigenvector of maximal eigenvalue
   /* power_iteration(A, k, g, g_size, M, L1norm, normalized_eig_vec);*/

    power_iteration_modified(A, k, M, l1_norm, normalized_eig_vec, f);
    for(i=0;i<n;i++){
        printf("%f/n", normalized_eig_vec[i]);
        fflush(stdout);
    }

    // get corresponding eigenvalue
    power_iteration_eigval_modified(A, k, M, f, l1_norm, normalized_eig_vec, &eig_val);

    if (!IS_POSITIVE(eig_val)) {
        status = GROUP_NOT_DIVISIBLE_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    for (i = 0; i < n; i++) {
        if (IS_POSITIVE(*(normalized_eig_vec + i))){
            *(s + i) = 1.0;
            *(number_of_1) += 1;
        }
        else
            *(s + i) = -1.0;
    }
    // we now use normalized_eig_vec to store the result of B_gag[g] * s;
    b_mult(A, k, M, s, normalized_eig_vec , f, 0);

    if (!IS_POSITIVE(vec_dot(s, normalized_eig_vec, n))) {
        status = GROUP_NOT_DIVISIBLE_CODE;
        get_error_message(status);
        goto l_cleanup;
    }
    free(normalized_eig_vec);
    status = SUCCESS_STATUS_CODE;
    return status;

    l_cleanup:
    free(normalized_eig_vec);
    for (i = 0; i < n; i++) *(s + i) = 1.0;
    return status;
}

/*Extracting the 2 groups indices(from output of algorithm 2) */

void extract_vectors(int *g, int g_size, int *s, int *v1, int *v2) {
    int i;
    for  (i = 0; i < g_size; i++){
        if (*(s + i) == 1) {
            *(v1++) = *(g + i);
        }
        else {
            *(v2++) = *(g + i);
        }
    }
}


void extract_vectors_sizes(int g_size, int *s, int *g1_size, int *g2_size) {
    int i;
    for (i = 0; i < g_size; i++) {
        if (*(s + i) == 1) {
            *(g1_size) = *(g1_size)+1;
        }
        else {
            *(g2_size) = *(g2_size)+1;
        }
    }
}
