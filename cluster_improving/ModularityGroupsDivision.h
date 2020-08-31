//
// Created by barak on 26/08/2020.
//

#ifndef CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H
#define CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H
#include "Stack.h"


void modularity_division_rec(struct _spmat *A, int *k, int M, double *s, double *f, double L1_NORM, int number_of_1, double *random_vector, double *normalized_eig_vec,
                             int *rows_helper, int *onces_helper, node **outer_array_helper);

#endif //CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H
