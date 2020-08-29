#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "B.h"
#include "Common.h"
#include "vector.h"
#include "Stack.h"
#include "SparseMatrix.h"
#include "Algorithm2.h"
#include "modularity_maximization.h"

Stack* initiate_P(int size) {
    Status status = INVALID_STATUS_CODE;
    int *indices, i;
    Stack *s;
    Dick *d;
    d = (Dick*)malloc(sizeof(Dick));
    if (NULL == d) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    indices = (int*)malloc(size * sizeof(int));
    if (NULL == indices) {
        status = MALLOC_FAILED_CODE ;
        get_error_message(status);
        goto l_cleanup;
    }

    /*Initiate the first group*/
    for (i = 0; i < size; i++)
        *(indices + i) = i;
    /*Allocating stack data stucture*/
    s = stack_allocate();/*Stack_allocate will handle the malloc failure case*/
    d->indices = indices;
    d->size = size;
    s->push(s, d);
    return s;
    l_cleanup:
    exit(status);
}
/*
Stack* algorithm3(const struct _spmat *A, const int *k, int M, int size, double *f) {
    Status status = INVALID_STATUS_CODE;
    Stack *P, *O;
    Dick *d, *d1_tmp, *d2_tmp;
    int *indices1, *indices2, g_size;

    int g1 = 0, g2 = 0, *g;
    O = stack_allocate();
    /*Initiate the starting step
    P = initiate_P(size);
    while (P->size != 0) {
        d = P->pop(P);
        g = d->indices;
        g_size = d->size;
        g1 = 0, g2 = 0;
        double *s = (double*)malloc(g_size * sizeof(double));
        if (NULL == s) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            goto l_cleanup;
        }
        status = algorithm2_modified(A, k, M, s, f,0);/*l1 norm addition*/
        /*status = modularity_max(A, k, M, g, g_size, s);
        extract_vectors_sizes(g_size, s, &g1, &g2);
        indices1 = (int*)malloc(g1 * sizeof(int));
        if (NULL == indices1) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            goto l_cleanup;
        }
        indices2 = (int*)malloc(g2 * sizeof(int));
        if (NULL == indices2) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            goto l_cleanup;
        }
        extract_vectors(g, g_size, s, indices1, indices2);
        if (g1 == 0 || g2 == 0) {
            O->push(O, d);
            continue;
        }
        d1_tmp = (Dick*)malloc(sizeof(Dick));
        if (NULL == d1_tmp) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            goto l_cleanup;
        }
        d2_tmp = (Dick*)malloc(sizeof(Dick));
        if (NULL == d2_tmp) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            goto l_cleanup;
        }
        if (g1 == 1 && g2 == 1) {
            d1_tmp->indices = indices1;
            d2_tmp->indices = indices2;
            d1_tmp->size = g1;
            d2_tmp->size = g2;
            O->push(O, d1_tmp);
            O->push(O, d2_tmp);
            free(d);
            continue;
        }
        if (g1 == 1 && g2 > 1) {
            d1_tmp->indices = indices1;
            d2_tmp->indices = indices2;
            d1_tmp->size = g1;
            d2_tmp->size = g2;
            O->push(O, d1_tmp);
            P->push(P, d2_tmp);
            free(d);
            continue;
        }
        if (g1 > 1 && g2 == 1) {
            d1_tmp->indices = indices1;
            d2_tmp->indices = indices2;
            d1_tmp->size = g1;
            d2_tmp->size = g2;
            P->push(P, d1_tmp);
            O->push(O, d2_tmp);
            free(d);
            continue;
        }
        if (g1 > 1 && g2 > 1) {
            d1_tmp->indices = indices1;
            d2_tmp->indices = indices2;
            d1_tmp->size = g1;
            d2_tmp->size = g2;
            P->push(P, d1_tmp);
            P->push(P, d2_tmp);
            free(d);
            continue;
        }
    }
    return O;
    l_cleanup:
    exit(status);
}
*/


void modularity_division_rec(struct _spmat *A, int *k, int M, double *s, double *f, double L1_NORM, int number_of_1,
                             int *rows_helper, int *onces_helper, node **outer_array_helper){
    Status status = INVALID_STATUS_CODE;
    status = algorithm2_modified(A, k, M, s, f, L1_NORM, number_of_1);

    if(status = GROUP_NOT_DIVISIBLE_CODE){ /*stopping condition*/

    }
    spmat *A1 = (spmat*)malloc(sizeof(spmat));
    if (NULL == A1) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    spmat *A2 = (spmat*)malloc(sizeof(spmat));
    if (NULL == A2) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    else{
        split_mat(A, A1, A2, k, s, number_of_1, rows_helper, onces_helper, outer_array_helper);
        /*
        modularity_division_rec(A1);
        modularity_division_rec(A2);
        */

    }




}
















