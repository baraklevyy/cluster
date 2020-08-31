//
// Created by barak on 26/08/2020.
//

#ifndef CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
#define CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
#include "B.h"
#include "Common.h"
#include "Algorithm2.h"
/* add handle of infinity loops */
double compute_modularity(const struct _spmat *A, const int *k, int M, int *s);
void find_vertex(const struct _spmat *A, const int *k, int M, int *s, int *moved, int *index_to_move, double *score);
void find_improved_partition(const struct _spmat *A, const int *k, int M, int *s, int *moved, int *improve_index,double *improve, int *indicies);
double compute_score(const struct _spmat *A, const int *k, int M, int *s, int row_number);
void modularity_max(const struct _spmat *A, const int *k, int M, int *s, int *moved, int *indicies);

#endif //CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
