#include <stdio.h>
#include "Common.h"
#include "SparseMatrix.h"
#include <stdlib.h>
#include "OptimizationMaximization.h"
#include <stdlib.h>

#ifndef CLUSTER_IMPROVING_MODMAX_H
#define CLUSTER_IMPROVING_MODMAX_H
void find_improved_partition1(const struct _spmat *A, const int *k, int M, double *s,int *moved,
                              int *improve_index, double *max_improve, int *indicies, int *number_of_1, int flag_first_iter, double *reuse_sum);
void find_vertex1(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *index_to_move, double *score, double *reuse_sum);
double compute_score1(const struct _spmat *A, const int *k, int M, double *s, int row_number, double reuse_sum);
void modularity_max1(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *indicies,int *number_of_1);

#endif /*CLUSTER_IMPROVING_MODMAX_H*/
