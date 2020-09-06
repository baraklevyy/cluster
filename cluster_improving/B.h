//
// Created by barak on 26/08/2020.
//

#ifndef CLUSTER_IMPROVING_B_H
#define CLUSTER_IMPROVING_B_H
#include <stdio.h>
#include "Common.h"
#include "SparseMatrix.h"

double f_i_g(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int i);
double B_gag_i_j(int i, int j, const struct _spmat *A, const int *k, const int *g, int g_size, int M);
double B_gag_L1_norm(const struct _spmat *A, const int *k, int M, const int *g, int g_size);
Status power_iteration(const struct _spmat *A, const int *k, const int *g, int g_size, int M, double L1norm, double *res);
Status power_iteration_eigval(const struct _spmat *A, const int *k, const int *g, int g_size, int M,
                              double L1norm, const double *eig_vec, double *eig_val);
void B_gag_vec_mult_int(const struct _spmat *A, const int *k, const int *g, int g_size, int M, double L1norm,
                        const int *v, double *res);




void b_mult(const struct _spmat *A, const int *k, int M, double *v, double *res, const double *f, double l1_norm);
void f_array(const struct _spmat *A, const int *k, int M, double *f);
double L1_norm(const struct _spmat *A, const int *k, int M, double *f);
void power_iteration_modified(const struct _spmat *A, const int *k, int M,allocations *alloc,double L1norm);
void power_iteration_eigval_modified(const struct _spmat *A, const int *k, int M, allocations *alloc,
                                     double L1norm, double *eig_val);

void k_arrangment(struct _spmat *A, int **k, int number_of_1, double *s, int **rows_helper, int **onces_helper, int **relevant_indices_helper);
void rows_arrangment(struct _spmat *A, double *s, int number_of_1, int *rows_helper, node ***outer_array_helper);
void split_mat(struct _spmat *A, struct _spmat *A1, struct _spmat *A2, int **k, double *s,
               int number_of_1, int **rows_helper, int **onces_helper, node ***outer_array_helper, int **relevant_indices_helper);


#endif //CLUSTER_IMPROVING_B_H
