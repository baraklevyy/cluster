#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SparseMatrix.h"
#include "Common.h"
#include "Utility.h"
#include "B.h"
#include "Algorithm2.h"
#include"ModularityGroupsDivision.h"

int main(int argc, char *argv[]) {
    int number_of_1 = 0;
    int *onces_helper;
    double l1_norm;
      Status status = INVALID_STATUS_CODE;
    int i;
    spmat *A;
    double *f;
    double *random_vector, *eigen_vector, *s;
    int M, *k, *row_helper;
    int n;
    /* status = generate_graph(); */
    /* seed random */
    srand((unsigned int) time(0));

    status = extract_matrix_size(argc, argv, &n);
    A = spmat_allocate_list(n); /*allocation check within the function*/
    if (NULL == A) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    random_vector = (double *)malloc(sizeof(double) * n);
    if (NULL == random_vector) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    eigen_vector = (double *)malloc(sizeof(double) * n);
    if (NULL == eigen_vector) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }

    s = (double *)malloc(sizeof(double) * n);
    if (NULL == s) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }

    k = (int *) malloc(sizeof(int) * n);
    if (NULL == k) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    row_helper = (int *) malloc(sizeof(int) * n);
    if (NULL == row_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    onces_helper = (int *) malloc(n * sizeof(int));
    if (NULL == onces_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }

    /*f allocation*/
    f = (double *) malloc(n * sizeof(double));
    if (NULL == f) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    status = graph_loading(argc, argv, A, k, &M);
    node **outer_array_helper = (node **) calloc(n, sizeof(node *));

    if (NULL == outer_array_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    f_array(A, k, M, f);
    l1_norm = L1_norm(A, k, M, f);
    l1_norm += 0;



    algorithm2_modified(A, k, M, s, f, l1_norm, &number_of_1, random_vector, eigen_vector);

    for (i = 0; i < n; i++) {
        printf("\nk[%d] = %d\ns[%d] = %f", i, k[i], i, s[i]);
        fflush(stdout);
    }



    k_arrangment(A, &k, number_of_1, s, &row_helper, &onces_helper);

    for (i = 0; i < n; i++) {
        printf("\nk[%d] = %d\nhelper[%d] = %d\nonces[%d] = %d", i, k[i], i, row_helper[i], i, *(A->onces_num + i));
        fflush(stdout);
    }

    rows_arrangment(A, s, number_of_1, row_helper, &outer_array_helper);
    node **outer = A->private;
    node *nnn;
    int cc;
    for (i = 0; i < n; i++) {
        nnn = outer[i];
        cc = nnn->col;
        printf("\nonces[%d] = %d\nprivate[%d] = %d", i, *(A->onces_num + i), i, cc);
        fflush(stdout);
    }
    return 0;


}