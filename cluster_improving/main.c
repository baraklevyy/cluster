#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SparseMatrix.h"
#include "Common.h"
#include "Utility.h"
#include "B.h"
#include "Algorithm2.h"
#include "Stack.h"
#include"ModularityGroupsDivision.h"

int main(int argc, char *argv[]) {
    fflush(stdout);
    int number_of_1 = 0;
    int *onces_helper;
    double res1[] = {0,0,0,0};;
    double l1_norm ;
    Status status = INVALID_STATUS_CODE;
    Stack *O, *P;
    int i;



    double v[] = {2,-2,2,-2};
    double *res = (double*)malloc(4);


    spmat *A;
    double *f;
    int M, *k;
    int n;
    /*######################################################################################
     * ##                                                                                 ##
     * ##                                                                                 ##
     * ##                        NECESSARY MALLOCS                                        ##
     * ##                                                                                 ##
     * ##                                                                                 ##
     * ##                                                                                 ##
     * ##                                                                                 ##
     * #####################################################################################
     *

    // seed random
    status = generate_graph();
    srand((unsigned int) time(0));
    status = extract_matrix_size(argc, argv, &n);
    A = spmat_allocate_list(n); /*allocation check within the function*/


   /* status = generate_graph(); */
    srand((unsigned int) time(0));
    status = extract_matrix_size(argc, argv, &n);
    A = spmat_allocate_list(n); /*allocation check within the function*/
    if (NULL == A) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }
    k = (int *) malloc(n * sizeof(int));
    if (NULL == k) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }
    onces_helper = (int *) malloc(n * sizeof(int));
    if (NULL == onces_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    /*f allocation*/
    f = (double *) malloc(n * sizeof(double));
    if (NULL == f) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
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

    double s[] = {0,0,0,0,0,0};
    int *helper = (int*)malloc(sizeof(int) * n);


    algorithm2_modified(A, k, M, s, f, l1_norm, &number_of_1);

    for(i = 0; i < n; i++ ){
        printf("\nk[%d] = %d\ns[%d] = %f",i,k[i],i,s[i]);
        fflush(stdout);
    }
    k_arrangment(A, &k, number_of_1, s, &helper, &onces_helper);
    for(i = 0; i < n; i++ ){
        printf("\nk[%d] = %d\nhelper[%d] = %d\nonces[%d] = %d",i,k[i],i,helper[i],i, *(A->onces_num+i));
        fflush(stdout);
    }

    rows_arrangment(A, s, number_of_1, k, helper, &outer_array_helper);
    node **outer = A->private;
    node* nnn;
    int cc;
    for(i = 0; i < n; i++ ){
       nnn = outer[i];
        cc = nnn->col;
        printf("\nonces[%d] = %d\nprivate[%d] = %d",i,*(A->onces_num+i),i,cc);
        fflush(stdout);
    }






    /*
    P = initiate_P(g_size);
    printf("%d", *(P->head->indices + 4));
    printf("\n");

    O = algorithm3(A, k, M, g_size);
    while (O->head->previous != NULL)
    {
        for (int i = 0; i < 3; i++) {
            printf("%d", *(O->head->indices + i));
        }
        O->head = O->head->previous;
    }


    */




    status = SUCCESS_STATUS_CODE;
    return 0;

    l_cleanup:
    exit(status);
}
