
#ifndef CLUSTER_IMPROVING_ALGORITHM2_H
#define CLUSTER_IMPROVING_ALGORITHM2_H

#include "Common.h"
#include "B.h"
#include "SparseMatrix.h"
#include "vector.h"

Status algorithm2_modified(const struct _spmat *A, const int *k, int M, double *s, double *f, double l1_norm, int *number_of_1) ;
void extract_vectors(int *g, int g_size, int *s, int *v1, int *v2);
void extract_vectors_sizes(int g_size, int *s, int *g1_size, int *g2_size);


#endif //CLUSTER_IMPROVING_ALGORITHM2_H
