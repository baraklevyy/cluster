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
void power_iteration_modified(const struct _spmat *A, const int *k, int M, double L1norm, double *res, double *f);
void power_iteration_eigval_modified(const struct _spmat *A, const int *k, int M, double *f,
                                     double L1norm, double *eig_vec, double *eig_val);

void k_arrangment(int **k, int k_size, int number_of_1, double *s, int **helper);
void split_mat(struct _spmat *A, int *k, double *s, int number_of_1, int *helper);

#endif //CLUSTER_IMPROVING_B_H
