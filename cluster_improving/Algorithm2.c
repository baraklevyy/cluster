#include <stdlib.h>
#include "Algorithm2.h"

Status algorithm2(const struct _spmat *A, const int *k, int M, allocations *alloc, double l1_norm) {
    Status status;
    int n;
    double eig_val, *s_ptr, *for_limit;

    status = INVALID_STATUS_CODE;
    n = A->n;
    for_limit = (alloc->s + n);
    /*get eigen_vector*/
    power_iteration(A, k, M, alloc, l1_norm);
    /* get corresponding eigenvalue */
    power_iteration_eigval(A, k, M, alloc, l1_norm, &eig_val);

    if (!IS_POSITIVE(eig_val)) {
        status = NEGATIVE_EIGEN_VALUE;
        goto l_cleanup;
    }

    for(s_ptr = alloc->s; s_ptr < for_limit; s_ptr++){
        if (IS_POSITIVE(*(s_ptr)))
            *(s_ptr) = 1.0;
        else
            *(s_ptr) = -1.0;
    }

    /* we now use random_normalized_vector to store the result of B_gag[g]*s */
    b_mult(A, k, M, alloc->s, alloc->random_normalized_vector , alloc->f, 0);
    /*here we compute deltaQ - Modularity change*/
    if (!IS_POSITIVE(vec_dot(alloc->s, alloc->random_normalized_vector, n))) {
        status = GROUP_NOT_DIVISIBLE_CODE;
        goto l_cleanup;
    }

    status = SUCCESS_STATUS_CODE;
    return status;

    l_cleanup:
    for(s_ptr = alloc->s; s_ptr < for_limit; s_ptr++) *(s_ptr) = 1.0;
    return status;
}


