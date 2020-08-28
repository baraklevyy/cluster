//
// Created by barak on 26/08/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "B.h"
#include "Common.h"
#include "vector.h"
#include "SparseMatrix.h"


double f_i_g(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int i) {
    double res = 0.0;
    const int *g_pointer = g;
    int g_i = 0;
    node **rows = A->private;
    node *current = rows[i];/*first element in the list[i]*/

    while (g_i < g_size) {
        if (NULL != current){
            if (current->col > *(g_pointer + g_i)) {
                res -= ((double)k[i] * (double)k[*(g_pointer + g_i)]) / (double)M;
                g_i++;
                continue;
            }
            else if (current->col < *(g_pointer + g_i)) {
                current = current->next;
                continue;
            }
            else {/*Element in A*/
                res += (1.0 - ((double)k[i] * (double)k[current->col]) / (double)M);
                current = current->next;
                g_i++;
                continue;
            }
        }
        else {
            res -= ((double)k[i] * (double)k[*(g_pointer + g_i)]) / (double)M;
            g_i++;
            continue;
        }
    }
    return res;
}


double B_gag_i_j(int i, int j, const struct _spmat *A, const int *k, const int *g, int g_size, int M) {
    double first = 0.0;
    double second = 0.0;
    int g_i = 0;
    const int *g_pointer = g;
    node **rows = A->private;
    node *current = rows[i];/*first element in the list[i]*/

    // calculate first element
    while (current != NULL) {
        if (current->col == j) {
            first = 1.0 - ((double)k[i] * (double)k[j]) / (double)M;
            break;
        }
        else if (current->col > j || !current->next) {
            first = -((double)k[i] * (double)k[j]) / (double)M;
            break;
        }
        current = current->next;
    }

    second = (i == j ? f_i_g(A, k, M, g, g_size, i) : 0);

    return first - second;
}

double B_gag_L1_norm(const struct _spmat *A, const int *k, int M, const int *g, int g_size) {
    int gi, gj;
    int i, j;
    double Bgagij;
    double current_row_sum;
    double max_row_sum;

    for (gi = 0; gi < g_size; gi++) {
        i = g[gi];
        current_row_sum = 0;
        for (gj = 0; gj < g_size; gj++) {
            j = g[gj];
            Bgagij = B_gag_i_j(i, j, A, k, g, g_size, M);
            current_row_sum += fabs(Bgagij);
        }

        if (gi == 0)
            max_row_sum = current_row_sum;
        else
            max_row_sum = MAX(max_row_sum, current_row_sum);
    }

    return max_row_sum;
}

// helper function that multiplies Bgag with a given vector, and stores the result in res
void B_gag_vec_mult(const struct _spmat *A, const int *k, const int *g, int g_size, int M, double L1norm,
                    const double *v, double *res) {
    int gi, gj;
    int i, j;
    double Bgagij;
    double row_sum;

    for (gi = 0; gi < g_size; gi++) {
        i = g[gi];
        row_sum = 0;

        for (gj = 0; gj < g_size; gj++) {
            j = g[gj];
            Bgagij = B_gag_i_j(i, j, A, k, g, g_size, M);

            // matrix shifting addition
            if (i == j)
                Bgagij += L1norm;

            row_sum += Bgagij * (*(v + gj));
        }

        *(res + gi) = row_sum;
    }
}

// int version of the helper function above
void B_gag_vec_mult_int(const struct _spmat *A, const int *k, const int *g, int g_size, int M, double L1norm,
                        const int *v, double *res) {
    int gi, gj;
    int i, j;
    double Bgagij;
    double row_sum;

    for (gi = 0; gi < g_size; gi++) {
        i = g[gi];
        row_sum = 0;

        for (gj = 0; gj < g_size; gj++) {
            j = g[gj];
            Bgagij = B_gag_i_j(i, j, A, k, g, g_size, M);

            // matrix shifting addition
            if (i == j)
                Bgagij += L1norm;

            row_sum += Bgagij * (double)(*(v + gj));
        }

        *(res + gi) = row_sum;
    }
}

#define disp(v) printf("[%lf, %lf]\n", v[0], v[1])

Status power_iteration(const struct _spmat *A, const int *k, const int *g, int g_size, int M, double L1norm, double *res) {
    Status status = INVALID_STATUS_CODE;
    int i;
    //int is_res = 1; // if is_res==1 then the result of the multiplication is stored in res, otherwise in v

    //generate a random normalized vector
    double *v = (double*)malloc(g_size * sizeof(double));
    if (NULL == v) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    for (i = 0; i < g_size; i++)
        *(v + i) = (double)rand() / (double)RAND_MAX;
    vec_normalize(v, g_size);

    while (1) {
        B_gag_vec_mult(A, k, g, g_size, M, L1norm, v, res);

        vec_normalize(res, g_size);

        if (diff_below_epsilon(v, res, g_size))
            break;

        for (i = 0; i < g_size; i++)
            *(v + i) = *(res + i);
    }

    free(v);
    status = SUCCESS_STATUS_CODE;
    return status;
    l_cleanup:
    exit(status);
}

Status power_iteration_eigval(const struct _spmat *A, const int *k, const int *g, int g_size, int M,
                              double L1norm, const double *eig_vec, double *eig_val) {
    Status status = INVALID_STATUS_CODE;
    double *Bgag_mul_eig_vec;
    double denom;

    Bgag_mul_eig_vec = (double*)malloc(g_size * sizeof(double));

    B_gag_vec_mult(A, k, g, g_size, M, L1norm, eig_vec, Bgag_mul_eig_vec);

    denom = vec_dot(eig_vec, eig_vec, g_size);
    if (!IS_POSITIVE(denom)) {
        status = ZERO_DIVISION_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    *eig_val = vec_dot(eig_vec, Bgag_mul_eig_vec, g_size) / denom;
    *eig_val -= L1norm;

    free(Bgag_mul_eig_vec);
    status = SUCCESS_STATUS_CODE;
    return status;

    l_cleanup:
    free(Bgag_mul_eig_vec);
    exit(status);
}
/*insert l1_norm == 0 if Matrix-Shifting is not require*/
void b_mult(const struct _spmat *A, const int *k, int M, double *v, double *res, const double *f, double l1_norm){
    double tmp = 0.0;
    int n = A->n;
    int i;
    double l1_norm_handling;

    /*this calculation has to calculate just once (Linear_Algebra manipulations)*/
    for(i = 0; i < n; i++)
        tmp += (*(v + i ) * (double)(*(k + i)));
    for(i = 0; i < n; i++){
        /*
        l1_norm_handling = tmp - (*(v + i ) * (double)(*(k + i))) + (*(v + i ) * (double)(*(k + i)) * l1_norm);
        *(res + i) -= (l1_norm_handling * ((double)*(k + i)) / (double)M);
         */
       /* *(res + i) -= (tmp * (*(k + i)) / ((double)M)) + ((l1_norm) * (*(v + i))) ;*/
        *(res + i) -= (tmp * (*(k + i)) / ((double)M));
        /**(res + i) = -((((double)(*(k + i)) * l1_norm_handling) / (double)M));/*this element should be distracted in B*v*/
        *(res + i) -= (*(f + i)) * (*(v + i)); /*Bgag Kroneaker delta element*/
        *(res + i) += l1_norm * *(v + i);

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

void power_iteration_modified(const struct _spmat *A, const int *k, int M, double L1norm, double *res, double *f) {
    Status status = INVALID_STATUS_CODE;
    int i;
    int n = A->n;
    //generate a random normalized vector
    double *v = (double*)malloc(n * sizeof(double));
    if (NULL == v) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }

    for (i = 0; i < n; i++)
        *(v + i) = (double)rand() / (double)RAND_MAX;
    vec_normalize(v, n);

    while (1) {

        b_mult(A, k, M, v, res, f,L1norm);
        for(i=0;i<n;i++){
            printf("%f\n", res[i]);
            fflush(stdout);
        }

        vec_normalize(res, n);

        if (diff_below_epsilon(v, res, n)){
            for(i=0;i<n;i++){
                printf("%f\n", res[i]);
                fflush(stdout);
            }

            break;
        }


        for (i = 0; i < n; i++)
            *(v + i) = *(res + i);
    }

    free(v);
}

void power_iteration_eigval_modified(const struct _spmat *A, const int *k, int M, double *f,
                                       double L1norm, double *eig_vec, double *eig_val) {
    Status status = INVALID_STATUS_CODE;
    int n =A->n;
    double *Bgag_mul_eig_vec;
    double denom;

    Bgag_mul_eig_vec = (double*)malloc(n * sizeof(double));
    b_mult(A, k, M, eig_vec, Bgag_mul_eig_vec, f, L1norm);
    denom = vec_dot(eig_vec, eig_vec, n);
    if (!IS_POSITIVE(denom)) {
        status = ZERO_DIVISION_CODE;
        get_error_message(status);
        exit(status);
    }
    *eig_val = vec_dot(eig_vec, Bgag_mul_eig_vec, n) / denom;
    *eig_val -= L1norm;
    free(Bgag_mul_eig_vec);
}

void k_arrangment(int **k, int k_size, int number_of_1, double *s, int **helper){
    int *tmp;
    int i, k1_index = 0, k2_index = number_of_1;
    for(i = 0; i < k_size; i++){
        if(*(s + i) == 1.0){
            *(*(helper) + k1_index) = *(*(k) + i);
            k1_index++;
        }
        else{
            *(*(helper) + k2_index) = *(*(k) + i);
            k2_index++;
        }
    }
    /*First, helper should be the new k, scond we dont want to loose access to dynamic allocated memory */
    tmp = *k;
    *k = *helper;
    *helper = tmp;
}

void split_mat(struct _spmat *A, int *k, double *s, int number_of_1, int *helper){
    Status status = INVALID_STATUS_CODE;
    int n = A->n;
    int *k_ptr = &k, *helper_ptr = &helper;
    int i, j, inner_index;
    spmat* A1 = (spmat*)malloc(sizeof(spmat));
    if (NULL == A1) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    spmat* A2 = (spmat*)malloc(sizeof(spmat));
    if (NULL == A2) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    node** outer_array = A->private;
    node *current_node, *previous;
    /*Private attribute assignment*/
    A1->private = outer_array;
    A2->private = outer_array + number_of_1;
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

    k_arrangment(k_ptr, n, number_of_1, s, helper_ptr);




    /* s==1 --> group A1, s==-1 --> group A2 */
    for(i = 0; i < n; i++){
        if(*(s + i) == 1.0){
            inner_index++;
        }


        current_node = *(outer_array + i);
        previous = *(outer_array + i);
        inner_index = 0;
        for(j = 0; j < *(A->onces_num + i); j++){

            *(A1->onces_num + i) = *(A->onces_num + i);

            /*vertex in the right group*/


            if(*(s + current_node->col) == 1.0){
                inner_index++;
                current_node->col = A1->n - current_node->col + inner_index ;
                previous = current_node;
                current_node = current_node->next;
                inner_index++;
                continue;
            }
            /*delete vertex*/
            else{
                if(current_node->next == NULL){
                    previous->next = NULL;
                    *(A1->onces_num + i) -= 1;
                }
                else{
                    previous->next = current_node->next;
                    *(A1->onces_num + i) -= 1;
                }
            }
        }



        if(*(s + i) == 1.0){

        }


    }














}