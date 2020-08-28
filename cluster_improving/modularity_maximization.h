//
// Created by barak on 26/08/2020.
//

#ifndef CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
#define CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
#include "B.h"
#include "Common.h"
#include "Algorithm2.h"
/* add handle of infinity loops */
Status compute_modularity(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int *s, double *res);
Status find_vertex(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int *s, double prim_mod,int *moved, int *index_to_move, double *score);
Status find_improved_partition(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int *s, int *moved, int *improve_index,double *improve, int *indicies);

Status modularity_max(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int *s);

#endif //CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
