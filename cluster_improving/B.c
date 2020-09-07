
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "B.h"
#include "Common.h"
#include "vector.h"
#include "SparseMatrix.h"

/*insert l1_norm == 0 if Matrix-Shifting is not require*/
void b_mult(const struct _spmat *A, const int *k, int M, double *v, double *res, const double *f, double l1_norm){
    double tmp = 0.0;
    int n = A->n;
    int i;
    double total_i;

    /*this calculation has to calculate just once (Linear_Algebra manipulations)*/
    for(i = 0; i < n; i++)
        tmp += (*(v + i ) * (double)(*(k + i)));
    for(i = 0; i < n; i++){
       total_i = 0.0;
       total_i -= (tmp * (*(k + i)) / ((double)M));
       total_i -= (*(f + i)) * (*(v + i)); /*Bgag Kroneaker delta element*/
       total_i += l1_norm * *(v + i);
       *(res + i) = total_i;

    }

    A->mult(A, v, res);



}

void f_array(const struct _spmat *A, const int *k, int M, double *f){
    int i;
    int n = A->n;
    double tmp = 0.0;
    /*tmp - calculate only once*/
    for(i = 0; i < n; i++){
        tmp += (double)(*(k + i)) / M;
    }
    for(i = 0; i < n; i++){
        *(f + i) = (double)(*(A->onces_num + i)) - (tmp * (*(k + i)));
    }
}

double L1_norm(const struct _spmat *A, const int *k, int M, double *f){
    int n = A->n;
    double reuse_sum = 0.0;
    int i, index, spmat_non_zero ;
    double total_max = -100 ;/*handle small numbers*/
    double current_row_sum = -100;/*handle small numbers*/
    double redundent;
    int is_f_negative;/*indicating if we need to add or subtract the element f*/
    node **outer_Array, *current_node;
    outer_Array = A->private;
    for(i = 0; i < n; i++){
        reuse_sum += (double)(*(k +i));
    }
    reuse_sum /= (double)M;
    /*outer loop calculate every single line*/
    for(i = 0; i < n; i++){
        current_node = *(outer_Array + i);
        spmat_non_zero = *(A->onces_num + i);
        is_f_negative = 0;
        redundent = 0.0;
        /*inner loop calculating each line elements*/
        for(index = 0; index < spmat_non_zero; index++){
            redundent += fabs((double)(*(k + current_node->col)));
            /*f handling*/
            if(current_node->col == i){
                is_f_negative = 1;
            }
            current_node = current_node->next;
        }
        redundent *= (((double)*(k + i)) / (double)M);
        current_row_sum = is_f_negative ? *(A->onces_num + i) + reuse_sum * (double)(*(k + i)) -2 * redundent - (*(f + i))
                                        : *(A->onces_num + i) + reuse_sum * (double)(*(k + i)) -2 * redundent + fabs(*(f + i));
        total_max = MAX(current_row_sum, total_max);
    }
    return total_max;
}

void power_iteration_modified(const struct _spmat *A, const int *k, int M, allocations *alloc, double L1norm) {

    int i/* num = 0*/;
    int n = A->n;
    /*int max_num_of_iteration = (n * n * n * n * n * n * n) * 1000;*/

    generate_random_normalized_vector(alloc->random_normalized_vector, n);

    while (1) {

        b_mult(A, k, M, alloc->random_normalized_vector, alloc->s, alloc->f, L1norm);
        vec_normalize(alloc->s, n);
        /*
         * here we have to calculate the median number of mult operation before reaching the desirable epsilon different
        if(num <= n * n){
            continue;
        }
       */
       /* vec_normalize(res, n); */
        if (diff_below_epsilon(alloc->random_normalized_vector, alloc->s, n)){
            break;
        }


        for (i = 0; i < n; i++)
            *(alloc->random_normalized_vector + i) = *(alloc->s + i);
    }
}

void power_iteration_eigval_modified(const struct _spmat *A, const int *k, int M, allocations *alloc,
                                       double L1norm, double *eig_val) {
    /*Status status = INVALID_STATUS_CODE;*/
    int n =A->n;
    double *Bgag_mul_eig_vec = alloc->random_normalized_vector;
   /* double denom; */

    /*Bgag_mul_eig_vec = (double*)malloc(n * sizeof(double));*/
    b_mult(A, k, M, alloc->s, Bgag_mul_eig_vec, alloc->f, L1norm);
    /*denom = vec_dot(eig_vec, eig_vec, n);
    if (!IS_POSITIVE(denom)) {
        status = ZERO_DIVISION_CODE;
        get_error_message(status);
        exit(status);
    }
     */
    *eig_val = vec_dot(alloc->s, Bgag_mul_eig_vec, n);
    /* *eig_val = vec_dot(eig_vec, Bgag_mul_eig_vec, n) / denom;*/
    *eig_val -= L1norm;

}
/*Please check pointers of helper and k. This func swap between them*/
void k_arrangment(struct _spmat *A, int **k, int number_of_1, double *s, int **rows_helper, int **onces_helper, int **relevant_indices_helper){
    int *tmp, *pointer;
    int i, n, k1_index = 0, k2_index = number_of_1;
    n = A->n;
    /*
    for(i=0;i<n;i++){
        printf("A.relevant[%d] = %d \n", i, *(A->relevant_indices + i));
        fflush(stdout);
    }
     */
    pointer = A->relevant_indices;
    for(i = 0; i < n; i++){
        if(*(s + i) == 1.0){

            *(*(relevant_indices_helper) + k1_index) = *(pointer);
            pointer++;
            *(*(rows_helper) + k1_index) = *(*(k) + i);
            *(*(k) + i) = k1_index;/*storing the correct col for node i*/
            /*onces attribute update*/
            *(*(onces_helper) + k1_index) = *(A->onces_num + i);
            k1_index++;
        }
        else{
            *(*(relevant_indices_helper) + k2_index) = *(pointer);
            pointer++;
            *(*(rows_helper) + k2_index) = *(*(k) + i);
            *(*(k) + i) = k2_index;
            /*onces attribute update*/
            *(*(onces_helper) + k2_index) = *(A->onces_num + i);
            k2_index++;
        }

    }
    /*First, helper should be the new k, second we dont want to loose access to dynamic allocated memory
     * After the end of this function, helper will store the the new column places in the indices of helper.
     * e.g: the new col for node number 4 will be helper[4]*/
    /*k and helper swap*/
    tmp = *k;
    *k = *rows_helper;
    *rows_helper = tmp;

    /*onces_num and onces_helper swap*/
    tmp = A->onces_num;
    A->onces_num = *onces_helper;
    *onces_helper = tmp;

    /*relevant_indices swap */
    tmp = A->relevant_indices;
    A->relevant_indices = *relevant_indices_helper;
    *relevant_indices_helper = tmp;

}

void rows_arrangment(struct _spmat *A, double *s, int number_of_1, int *rows_helper, node ***outer_array_helper) {
    int n = A->n;
    int i, k2_start_index = number_of_1, cur_col, cur_outer_arr_index;
    node **tmp;
    node *current_node, *previous_node, *next_node;

    for (i = 0; i < n; i++) {
        /*Assignment of outer_arr_helper[i] to the correct list belongs to it, and storing the index of that position*/
        cur_outer_arr_index = *(rows_helper + i);
        /* *(outer_array_helper) + (cur_outer_arr_index) = (node**)A->private + i;*/
        *(*(outer_array_helper) + (cur_outer_arr_index)) = *((node**)A->private + i);
        /*Initializing starting nodes*/
        current_node = *((node**)A->private + i);
        previous_node = *((node**)A->private + i);
        while (current_node != NULL) {
            next_node = current_node->next;
            cur_col = current_node->col;
            /*Deletion necessary*/
            if (((*(s + i) == 1.0) && (*(rows_helper + cur_col) >= k2_start_index)) ||
                (((*(s + i) == -1.0) && (*(rows_helper + cur_col) < k2_start_index)))){ /*current_node has to be deleted.The constraints depands on the location of the indices*/

                /*onces attribute update*/
                *(A->onces_num + cur_outer_arr_index) -= 1;/*empty row*/
/*
                if(*(A->onces_num + cur_outer_arr_index) == 0){
                    *(*(outer_array_helper) + (cur_outer_arr_index)) = NULL;
                    free(current_node);
                    continue;
                }
                */
                if(current_node == *((node**)A->private + i)) { /* The first element in the list should be deleted*/
                    /*here were in outer_array_helper*/
                    previous_node = next_node;
                    *((node**)A->private + i) = next_node;
                    *(*(outer_array_helper) + (cur_outer_arr_index)) = *((node**)A->private + i);
                }
                else
                    previous_node->next = next_node;

                free(current_node);
                current_node = next_node;
                continue;
            }
            /*incrementing loop condition*/
            previous_node = current_node;
            current_node->col = (*(s + i) == 1.0) ? *(rows_helper + cur_col) : *(rows_helper + cur_col) - k2_start_index ;
            current_node = next_node;
        }
    }
    /*pointers changing*/
    /* *(tmp) = *(outer_array); */
    tmp = (node**)A->private;
    A->private = *(outer_array_helper);
    *(outer_array_helper) = tmp;


    /*
    tmp = outer_array;
    A->private = *(outer_array_helper) ;
    *(outer_array_helper) = tmp;
     */
    /*free(tmp);*/
    /*were going to use outer_arr_helper again so free it just in the end of the program*/
}

void split_mat(struct _spmat *A, struct _spmat *A1, struct _spmat *A2, int **k, double *s,
               int number_of_1, int **rows_helper, int **onces_helper, node ***outer_array_helper, int **relevant_indices_helper){
    /*Status status = INVALID_STATUS_CODE;*/
    int n = A->n;
    /*Groups sizes*/

    A1->n = number_of_1;
    A2->n = n - number_of_1;
    /*Attributes assignment*/
    A1->mult = A->mult;
    A2->mult = A->mult;
    A1->add_row = A->add_row;
    A2->add_row = A->add_row;
    A1->free = A->free;
    A2->free = A->free;
    /* this function divide vector k into 2 groups, same for onces_num vector */
    k_arrangment(A, k, number_of_1, s, rows_helper, onces_helper, relevant_indices_helper);


    /*deleting unnecessary elements within the rows, as well as arranging the outer_array of list pointers obeying the vector s classification */
    rows_arrangment(A, s, number_of_1, *(rows_helper), outer_array_helper);
    /*
    for(i=0;i<n;i++){
        printf("rows_helper[%d] = %d \n", i, *(*(rows_helper) + i));
        fflush(stdout);
    }
     */

    A1->relevant_indices = A->relevant_indices;
    A2->relevant_indices = A->relevant_indices + number_of_1;
    A1->onces_num = A->onces_num;
    A2->onces_num =  A->onces_num + number_of_1;
    /*Private attribute assignment*/
    A1->private = A->private;
    A2->private = (node **)(A->private) + number_of_1;
    /*
    for(i=0;i<A1->n;i++){
        printf("A1.relevant[%d] = %d \n", i, *(A1->relevant_indices + i));
        fflush(stdout);
    }
    for(i=0;i<A2->n;i++){
        printf("A1.relevant[%d] = %d \n", i, *(A2->relevant_indices + i));
        fflush(stdout);
    }
     */


}















































void k_arrangment_modified(struct _spmat *A,allocations *alloc, int number_of_1){
    int *pointer;
    int i, n, k1_index = 0, k2_index = number_of_1;
    n = A->n;
    pointer = A->relevant_indices;
    for(i = 0; i < n; i++){
        if(*(alloc->s + i) == 1.0){

            *(alloc->relevant_indices_helper + k1_index) = *(pointer);
            pointer++;
            *(alloc->rows_helper + k1_index) = *(alloc->k + i);
            *(alloc->k + i) = k1_index;/*storing the correct col for node i*/
            /*onces attribute update*/
            *(alloc->onces_helper + k1_index) = *(A->onces_num + i);
            k1_index++;
        }
        else{
            *(alloc->relevant_indices_helper + k2_index) = *(pointer);
            pointer++;
            *(alloc->rows_helper + k2_index) = *(alloc->k + i);
            *(alloc->k + i) = k2_index;
            /*onces attribute update*/
            *(alloc->onces_helper + k2_index) = *(A->onces_num + i);
            k2_index++;
        }

    }
    /*returning to the original arrays*/
    for(i = 0; i < n; i++){
        *(A->relevant_indices + i) = *(alloc->relevant_indices_helper + i);
        *(alloc->k + i) = *(alloc->rows_helper);
        *(A->onces_num + i) = *(alloc->onces_helper);
    }

}





























void rows_arrangment_modified(struct _spmat *A, allocations *alloc, int number_of_1) {
    int n = A->n;
    int i, k2_start_index = number_of_1, cur_col, cur_outer_arr_index;
    node *current_node, *previous_node, *next_node;

    for (i = 0; i < n; i++) {
        /*Assignment of outer_arr_helper[i] to the correct list belongs to it, and storing the index of that position*/
        cur_outer_arr_index = *(alloc->rows_helper + i);
        /* *(outer_array_helper) + (cur_outer_arr_index) = (node**)A->private + i;*/
        *(alloc->outer_array_helper + (cur_outer_arr_index)) = *((node**)A->private + i);
        /*Initializing starting nodes*/
        current_node = *((node**)A->private + i);
        previous_node = *((node**)A->private + i);
        while (current_node != NULL) {
            next_node = current_node->next;
            cur_col = current_node->col;
            /*Deletion necessary*/
            if (((*(alloc->s + i) == 1.0) && (*(alloc->rows_helper + cur_col) >= k2_start_index)) ||
                (((*(alloc->s + i) == -1.0) && (*(alloc->rows_helper + cur_col) < k2_start_index)))){ /*current_node has to be deleted.The constraints depands on the location of the indices*/
                /*onces attribute update*/
                *(A->onces_num + cur_outer_arr_index) -= 1;
                if(current_node == *((node**)A->private + i)) { /* The first element in the list should be deleted*/
                    /*here were in outer_array_helper*/
                    previous_node = next_node;
                    *((node**)A->private + i) = next_node;
                    *(alloc->outer_array_helper + (cur_outer_arr_index)) = *((node**)A->private + i);
                }
                else
                    previous_node->next = next_node;

                free(current_node);
                current_node = next_node;
                continue;
            }
            /*incrementing loop condition*/
            previous_node = current_node;
            current_node->col = (*(alloc->s + i) == 1.0) ? *(alloc->rows_helper + cur_col) : *(alloc->rows_helper + cur_col) - k2_start_index ;
            current_node = next_node;
        }
    }

    for(i=0;i<n;i++){
        *((node**)A->private + i) = *(alloc->outer_array_helper + i);
    }
}







void split_mat_modified(struct _spmat *A, struct _spmat *A1, struct _spmat *A2, allocations *alloc, int number_of_1){
    /*Status status = INVALID_STATUS_CODE;*/
    int n = A->n;
    /*Groups sizes*/

    A1->n = number_of_1;
    A2->n = n - number_of_1;
    /*Attributes assignment*/
    A1->mult = A->mult;
    A2->mult = A->mult;
    A1->add_row = A->add_row;
    A2->add_row = A->add_row;
    A1->free = A->free;
    A2->free = A->free;
    /* this function divide vector k into 2 groups, same for onces_num vector */
    k_arrangment_modified(A, alloc, number_of_1);


    /*deleting unnecessary elements within the rows, as well as arranging the outer_array of list pointers obeying the vector s classification */
    rows_arrangment_modified(A, alloc, number_of_1);
    /*
    for(i=0;i<n;i++){
        printf("rows_helper[%d] = %d \n", i, *(*(rows_helper) + i));
        fflush(stdout);
    }
     */

    A1->relevant_indices = A->relevant_indices;
    A2->relevant_indices = A->relevant_indices + number_of_1;
    A1->onces_num = A->onces_num;
    A2->onces_num =  A->onces_num + number_of_1;
    /*Private attribute assignment*/
    A1->private = A->private;
    A2->private = (node **)(A->private) + number_of_1;
    /*
    for(i=0;i<A1->n;i++){
        printf("A1.relevant[%d] = %d \n", i, *(A1->relevant_indices + i));
        fflush(stdout);
    }
    for(i=0;i<A2->n;i++){
        printf("A1.relevant[%d] = %d \n", i, *(A2->relevant_indices + i));
        fflush(stdout);
    }
     */










}































