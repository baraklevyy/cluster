
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
    double total_i, m;
    m = (double)M;

    /*this calculation has to calculate just once (Linear_Algebra manipulations)*/
    for(i = 0; i < n; i++)
        tmp += (*(v + i ) * (double)(*(k + i)));
    for(i = 0; i < n; i++){
       total_i = 0.0;

       /*total_i -= (tmp * (*(k + i)) / m);*/
       /*total_i -= (*(f + i)) * (*(v + i));*/ /*Bgag Kroneaker delta element*/
       /*total_i += l1_norm * *(v + i);*/
       total_i = -(tmp * (*(k + i)) / m) - (*(f + i)) * (*(v + i)) + l1_norm * *(v + i);
       *(res + i) = total_i;
    }
    list_multiplay(A, v, res);
}

void f_array(const struct _spmat *A, int *const k, int M, double *f, double *reuse_sum){
    int i, n, *k_ptr, *for_limit;
    double tmp, m;
    m = (double)M;
    n = A->n;
    tmp = 0.0;
    for_limit = k + n;

    /*tmp - calculate only once*/
    for(k_ptr = k; k_ptr < for_limit; k_ptr++){
        tmp += (*(k_ptr)) ;
    }
    tmp = tmp / m;
    *(reuse_sum) = tmp;
    for(i = 0; i < n; i++){
        *(f + i) = (double)(*(A->onces_num + i)) - (tmp * (*(k + i)));
    }
}

double L1_norm(const struct _spmat *A, const int *k, int M, double *f, double reuse_sum){
    int n = A->n;
    int i, index, spmat_non_zero ;
    double total_max = LOWEST_VALUE ;/*handle small numbers*/
    double current_row_sum = LOWEST_VALUE;/*handle small numbers*/
    double redundent;
    int is_f_negative;/*indicating if we need to add or subtract the element f*/
    node **outer_Array, *current_node;
    outer_Array = A->private;
    /*outer loop calculate every single line*/
    for(i = 0; i < n; i++){
        current_node = *(outer_Array + i);
        spmat_non_zero = *(A->onces_num + i);
        is_f_negative = 0;
        redundent = 0.0;
        /*inner loop calculating each line elements*/
        for(index = 0; index < spmat_non_zero; index++){
            redundent += ((double)(*(k + current_node->col)));
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
    Status status = INVALID_STATUS_CODE;
    int i, num = 0;
    int n = A->n;

    generate_random_normalized_vector(alloc->random_normalized_vector, n);

    while (num <= 300000) {
        num += 1;
        b_mult(A, k, M, alloc->random_normalized_vector, alloc->s, alloc->f, L1norm);
        vec_normalize(alloc->s, n);

        if(num <= n / 15){
            continue;
        }

       /* vec_normalize(res, n); */
        if (diff_below_epsilon(alloc->random_normalized_vector, alloc->s, n)){
            break;
        }

        for (i = 0; i < n; i++)
            *(alloc->random_normalized_vector + i) = *(alloc->s + i);
    }
    if(num >= 300000){
        status = REACHED_MAX_NUMBER_OF_ITERATION;
        get_error_message(status);
        exit(status);
    }
    printf("total number of mult in Power_Iteration is %d\n", num);
    fflush(stdout);
}

void power_iteration_eigval_modified(const struct _spmat *A, const int *k, int M, allocations *alloc,
                                     double L1norm, double *eig_val) {

    int n =A->n;
    double eigen_value;
    double *Bgag_mul_eig_vec = alloc->random_normalized_vector;

    b_mult(A, k, M, alloc->s, Bgag_mul_eig_vec, alloc->f, L1norm);
    eigen_value = vec_dot(alloc->s, Bgag_mul_eig_vec, n);
    eigen_value -= L1norm;
    *eig_val = eigen_value;

}
/*Please check pointers of helper and k. This func swap between them*/
void k_arrangment(struct _spmat *A, int *k, int number_of_1, double *s, int *rows_helper, int *onces_helper, int *relevant_indices_helper){
    int *pointer;
    int i, n, k1_index = 0, k2_index = number_of_1;
    n = A->n;

    pointer = A->relevant_indices;
    for(i = 0; i < n; i++){
        if(*(s + i) == 1.0){
            *(relevant_indices_helper + k1_index) = *(pointer++);
            *(rows_helper + k1_index) = *(k + i);
            *(k + i) = k1_index;/*storing the correct col for node i*/
            /*onces attribute update*/
            *(onces_helper + (k1_index)++) = *(A->onces_num + i);
        }
        else{
            *(relevant_indices_helper + k2_index) = *((pointer)++);
            *(rows_helper + k2_index) = *(k + i);
            *(k + i) = k2_index;
            /*onces attribute update*/
            *(onces_helper + (k2_index)++) = *(A->onces_num + i);
        }

    }
    /*First, helper should be the new k, second we dont want to loose access to dynamic allocated memory
     * After the end of this function, helper will store the the new column places in the indices of helper.
     * e.g: the new col for node number 4 will be helper[4]*/
    /*k and helper swap*/

    for(i = 0; i < n; i++){
        *(A->onces_num + i) = *(onces_helper + i);
        *(A->relevant_indices + i) = *(relevant_indices_helper + i);
    }
    for(i = 0; i < n; i++){
        *(relevant_indices_helper + i) = *(rows_helper + i);
        *(onces_helper + i) = *(k + i);
    }
    for(i = 0; i < n; i++){
        *(k + i) = *(relevant_indices_helper + i);
        *(rows_helper + i) = *(onces_helper + i);
    }
}

void rows_arrangment(struct _spmat *A, double *s, int number_of_1, int *rows_helper, node **outer_array_helper) {
    double si;
    int i, n, k2_start_index = number_of_1, cur_col, cur_outer_arr_index, rows_helper_tmp ;
    node *current_node, *previous_node, *next_node, *first_node;
    n = A->n;

    for (i = 0; i < n; i++) {
        /*Assignment of outer_arr_helper[i] to the correct list belongs to it, and storing the index of that position*/
        cur_outer_arr_index = *(rows_helper + i);
        first_node = *((node**)A->private + i);
        *(outer_array_helper + (cur_outer_arr_index)) = first_node;
        /*Initializing starting nodes*/
        current_node = first_node;
        previous_node = first_node;
        while (current_node != NULL) {
            next_node = current_node->next;
            cur_col = current_node->col;
            si = *(s + i);
            rows_helper_tmp = *(rows_helper + cur_col);
            /*Deletion necessary*/
            if (((si == 1.0) && (rows_helper_tmp >= k2_start_index)) ||
                (((si == -1.0) && (rows_helper_tmp < k2_start_index)))){ /*current_node has to be deleted.The constraints depands on the location of the indices*/

                /*onces attribute update*/
                *(A->onces_num + cur_outer_arr_index) -= 1;/*empty row*/
                if(current_node == first_node) { /* The first element in the list should be deleted*/
                    /*here were in outer_array_helper*/
                    previous_node = next_node;
                    first_node = next_node;
                    *((node**)A->private + i) = next_node;
                    *(outer_array_helper + (cur_outer_arr_index)) = first_node;
                }
                else
                    previous_node->next = next_node;

                free(current_node);
                current_node = next_node;
                continue;
            }
            /*incrementing loop condition*/
            previous_node = current_node;
            current_node->col = (si == 1.0) ? rows_helper_tmp : rows_helper_tmp - k2_start_index ;
            current_node = next_node;
        }
    }
    for (i = 0; i < n; i++) {
        *((node**)A->private + i) = *(outer_array_helper + i);
    }
}

void split_mat(struct _spmat *A, struct _spmat *A1, struct _spmat *A2, int *k, double *s,
               int number_of_1, int *rows_helper, int *onces_helper, node **outer_array_helper, int *relevant_indices_helper) {
    int n = A->n;
    /*Groups sizes*/

    A1->n = number_of_1;
    A2->n = n - number_of_1;
    /* this function divide vector k into 2 groups, same for onces_num vector */
    k_arrangment(A, k, number_of_1, s, rows_helper, onces_helper, relevant_indices_helper);
    /*deleting unnecessary elements within the rows, as well as arranging the outer_array of list pointers obeying the vector s classification */
    rows_arrangment(A, s, number_of_1, rows_helper, outer_array_helper);
    A1->relevant_indices = A->relevant_indices;
    A2->relevant_indices = A->relevant_indices + number_of_1;
    A1->onces_num = A->onces_num;
    A2->onces_num = A->onces_num + number_of_1;
    /*Private attribute assignment*/
    A1->private = A->private;
    A2->private = (node **) (A->private) + number_of_1;

}





