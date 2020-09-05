
#ifndef CLUSTER_IMPROVING_ALGORITHM2_H
#define CLUSTER_IMPROVING_ALGORITHM2_H

#include "Common.h"
#include "B.h"
#include "SparseMatrix.h"
#include "vector.h"

Status algorithm2_modified(const struct _spmat *A, const int *k, int M, double *s,
                           double *f, double l1_norm, int *number_of_1, double *normalized_eig_vec,
                           double *random_normalized_vector) ;

#endif //CLUSTER_IMPROVING_ALGORITHM2_H
