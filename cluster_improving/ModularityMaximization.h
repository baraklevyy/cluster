#include <stdio.h>
#include "Common.h"
#include "SparseMatrix.h"
#include <stdlib.h>
#include <stdlib.h>

#ifndef CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
#define CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
void modularity_max1(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *indicies,int *number_of_1);
double compute_score1(const struct _spmat *A, const int *k, int M, double *s, int row_number, double reuse_sum);

#endif /*CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H*/
