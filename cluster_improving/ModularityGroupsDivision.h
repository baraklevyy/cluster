//
// Created by barak on 26/08/2020.
//

#ifndef CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H
#define CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H
#include "Stack.h"


Stack* initiate_P(int size);
Stack* algorithm3(const struct _spmat *A, const int *k, int M, int size);
void modularity_division_rec(struct _spmat *A, int *k, int M, double *s, double *f, double L1_NORM, int number_of_1,
                             double *normalized_eig_vec, double *random_normalized_vec, int *rows_helper,
                             int *onces_helper, node **outer_array_helper, int *number_of_groups, int *number_of_written_elements, FILE *write_ptr, int * output_array, int L1_calculation);

#endif //CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H
