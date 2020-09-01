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
    Status status = INVALID_STATUS_CODE;
    int number_of_1 = 0 , M, n, i, index;
    int *onces_helper, *k, *rows_helper, v_elem_num, *output_array, number_of_groups, number_of_written_elements, L1_calculation;
    double *s, *random_normalized_vector, *normalized_eig_vec, *f;
    spmat *A, *a1, *a2;
    node *nnpointer, **nnouterarry ;
    node **outer_array_helper;
    FILE *write_ptr;







   /* status = generate_graph(); */
   /*seed random*/
    srand((unsigned int) time(0));
    status = extract_matrix_size(argc, argv, &n);


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
    */
    A = spmat_allocate_list(n); /*allocation check within the function*/
    if (NULL == A) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    k = (int *) malloc(n * sizeof(int));
    if (NULL == k) {
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
    /*2n+1 for extreme case of each node lone in its own group*/
    output_array = (int *) malloc(((2 * n) + 1) * sizeof(int));
    if (NULL == output_array) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    f = (double *) malloc(n * sizeof(double));
    if (NULL == f) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    random_normalized_vector = (double *) malloc(n * sizeof(double));
    if (NULL == random_normalized_vector) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    normalized_eig_vec = malloc(n * sizeof(double));
    if (NULL == normalized_eig_vec) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    s = malloc(n * sizeof(double));
    if (NULL == s) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    rows_helper = (int*)malloc(sizeof(int) * n);
    if (NULL == rows_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    outer_array_helper = (node **) calloc(n, sizeof(node *));
    if (NULL == outer_array_helper) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }

    a1 = (spmat*)malloc(sizeof(spmat) );
    a2 = (spmat*)malloc(sizeof(spmat) );





    status = graph_loading(argc, argv, A, k, &M);
    /*

    f_array(A, k, M, f);
    L1_NORM = L1_norm(A, k, M, f);

    */

    write_ptr = fopen("output.bin","wb");  // w for write, b for binary
    L1_calculation = 1;
    number_of_written_elements = 1; /*allocating the first slot for the number of groups*/
    modularity_division_rec(A, k, M, s, f, 0.0, number_of_1, normalized_eig_vec,
                            random_normalized_vector, rows_helper, onces_helper, outer_array_helper, &number_of_groups, &number_of_written_elements,
                           write_ptr, output_array, L1_calculation);
    *(output_array) = number_of_groups;
    for(i = 0; i < number_of_written_elements; i++ ){
        printf("output_array[%d] = %d\n", i, *(output_array + i) );
        fflush(stdout);
    }


   /* algorithm2_modified(A, k, M, s, f, L1_NORM, &number_of_1, normalized_eig_vec, random_normalized_vector); */

    for(i = 0; i < n; i++ ){
        printf("s[%d] = %f\n", i, *(s + i) );
        fflush(stdout);
    }







    split_mat(A,a1,a2,&k,s,number_of_1,&rows_helper,onces_helper,&outer_array_helper);

    nnouterarry = a1->private;
    for (i = 0; i < a1->n; ++i) {
        nnpointer = ((node*)a1->private + i);
        nnpointer = nnouterarry[i];
        v_elem_num = *(a1->onces_num + i);
        index = 0;
        for (index= 0; index < v_elem_num; index++) {
            printf("a1.private[%d,%d] = %d \n", i, index, nnpointer->col);
            printf("a1.private(original)[%d,%d] = %d \n", i, index, nnpointer->original);
            fflush(stdout);
            nnpointer = nnpointer->next;
        }
    }
    nnouterarry = a2->private;
    for (i = 0; i < a2->n; ++i) {
        nnpointer = nnouterarry[i];
        v_elem_num = *(a2->onces_num + i);
        index = 0;
        for (index= 0; index < v_elem_num; index++) {
            printf("a1.private[%d,%d] = %d \n", i, index, nnpointer->col);
            printf("a1.private(original)[%d,%d] = %d \n", i, index, nnpointer->original);
            fflush(stdout);
            nnpointer = nnpointer->next;
        }
    }

    for(i=0;i<n;i++) {
        printf("k[%d] = %d \n", i, *(k + i));
        fflush(stdout);
    }
    for(i=0;i<n;i++) {
        printf("rows_helper[%d] = %d \n", i, *(rows_helper + i));
        fflush(stdout);
    }
    for(i=0;i<a1->n;i++) {
        printf("a1.onces[%d] = %d \n", i, *(a1->onces_num + i));
        fflush(stdout);
    }
    for(i=0;i<a2->n;i++) {
        printf("a2.onces[%d] = %d \n", i, *(a2->onces_num + i));
        fflush(stdout);
    }







    fclose(write_ptr);
    status = SUCCESS_STATUS_CODE;
    return 0;

}
