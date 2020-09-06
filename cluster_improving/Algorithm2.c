#include <stdlib.h>
#include "Algorithm2.h"

Status algorithm2_modified(const struct _spmat *A, const int *k, int M, allocations *alloc, double l1_norm, int *number_of_1) {
    Status status = INVALID_STATUS_CODE;
    int n = A->n;
    *(number_of_1) = 0;

    double eig_val;
    int i;
    /*get eigen_vector*/
    power_iteration_modified(A, k, M, alloc, l1_norm);
    /* get corresponding eigenvalue */

    power_iteration_eigval_modified(A, k, M, alloc, l1_norm, &eig_val);
    /*
    printf("eigen value is %f\n", eig_val);
    fflush(stdout);

     */
    if (!IS_POSITIVE(eig_val)) {
        status = NEGATIVE_EIGEN_VALUE;
        goto l_cleanup;
    }

    for (i = 0; i < n; i++) {
        if (IS_POSITIVE(*(alloc->s + i))){
            *(alloc->s + i) = 1.0;
            *(number_of_1) += 1;
        }
        else
            *(alloc->s + i) = -1.0;
    }

    // we now use random_normalized_vector to store the result of B_gag[g] * s ;
    b_mult(A, k, M, alloc->s, alloc->random_normalized_vector , alloc->f, 0);
    /*here we compute deltaQ - Modularity change*/
    if (!IS_POSITIVE(vec_dot(alloc->s, alloc->random_normalized_vector, n))) {
        status = GROUP_NOT_DIVISIBLE_CODE;
        goto l_cleanup;
    }
    /*
    for(i=0;i<n;i++) {
        printf("s[%d] = %f \n", i, *(alloc->s + i));
        fflush(stdout);
    }
     */
    status = SUCCESS_STATUS_CODE;
    return status;

    l_cleanup:
    for (i = 0; i < n; i++) *(alloc->s + i) = 1.0;
    return status;
}


