


#include <stdio.h>
#include "Common.h"
#include "SparseMatrix.h"
#include <stdlib.h>
#include "OptimizationMaximization.h"
#include <stdlib.h>

void modularity_max_modified(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *indicies, int *number_of_1 ){
    int i, j, u;
    int improve_index;
    double delta_q;
    double improve;
    int flag_first_iter =1; /* indicate if this first iteration of do-while loop ---> for number_of_1 */
    int local_num_1 =0;
    int n = A->n;
    double sj;
    double reuse_sum;
/*
    for(u=0;u<n;u++){
        printf("\ns[%d]=%f", u, *(s+u));
        fflush(stdout);

    }
    for(u = 0; u < n; u++){
        reuse_sum += ((double)(*(k + u) * (*(s + u))));
        fflush(stdout);
    }

    reuse_sum /= M;
    */
    reuse_sum = 0.0;
    for(u = 0; u < n; u++){
        reuse_sum += ((double)(*(k + u) * (*(s + u))));
    }
    reuse_sum /= M;
    do{
        /* set to zero relevant elements of moved */
        for(i = 0; i<n; i++){
            moved[i]=0;
        }

        find_improved_partition_modified(A, k, M, s, moved, &improve_index, &improve, indicies, &local_num_1, flag_first_iter, &reuse_sum);
        if(improve_index == n - 1){
            delta_q =0;
        }
        else{
            delta_q = improve;
        }
        for (i = n - 1; i > improve_index; i--){
            j = *(indicies + i);

            *(s + j) = - *(s + j);

            sj = *(s + j);

            /*reuse_sum = reuse_sum + (2 * ((double)(*(k + i) * sj)) /  (double) M); */

            /* update counter for number of ones */
            if(sj == -1.0){
                local_num_1 -= 1;
            }
            else local_num_1 += 1;
        }
        flag_first_iter =0;
    }
    while(IS_POSITIVE(delta_q));
    *number_of_1 =local_num_1;
    return;
}

void find_improved_partition_modified(const struct _spmat *A, const int *k, int M, double *s,int *moved, int *improve_index,
                             double *max_improve, int *indicies, int *number_of_1, int flag_first_iter, double *reuse_sum){
    int i, j;
    double prev_improve,curr_improve;
    int ind_for_move;
    double score;
    int n = A->n;
    double s_index_to_move;

    for(i=0;i< n; i++){

        find_vertex_modified(A, k, M, s, moved, &ind_for_move, &score, reuse_sum);
        *(s + ind_for_move) = -*(s + ind_for_move); /*move vertex */


        for(j=0;j<A->n;j++){
            printf("\ns[%d]= %f", j, *(s + j));
            fflush(stdout);
        }

        s_index_to_move = *(s + ind_for_move);
        *(reuse_sum) = *(reuse_sum) + (2 * ((double)(*(k + i) * s_index_to_move)) /  (double) M);

        /* number of 1 */
        if(flag_first_iter == 1 ){ /*this is the first iteration */
            if(s_index_to_move == 1.0){
                *number_of_1 += 1;
            }
        }
        else{
            if(*(s + ind_for_move) == 1){
                *number_of_1 += 1;
            }
            else *number_of_1 -= 1;
        }
        *(indicies + i) = ind_for_move;
        if (i==0){
            *improve_index =i;
            *max_improve = score;
            prev_improve = score;
        }
        else{
            curr_improve = prev_improve + score;
            if(curr_improve > *max_improve){
                *max_improve = curr_improve;
                *improve_index =i;
            }
            prev_improve = curr_improve;
        }
        *(moved + ind_for_move) =1; /*mark this index as moved */
    }
    return;
}

void find_vertex_modified(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *index_to_move, double *score, double *reuse_sum){
    /* find vertex with biggest increase */
    double diff_mod;
    int i,first_moved, j;
    int n = A->n;
    double si, original_sum;
    first_moved =0;
    original_sum = *(reuse_sum);
    for(i=0;i< n ;i++){
        if(*(moved + i)==0){ /* true only for vertices that doesnt move */
            if(first_moved ==0){
                *(s + i) = -*(s + i);
                si = *(s + i);
                for(j=0;j<A->n;j++){
                    printf("\ns[%d]= %f", j, *(s + j));
                    fflush(stdout);
                }
                *(reuse_sum) = *(reuse_sum) + (2 * ((double)(*(k + i) * si)) /  (double) M);
                diff_mod = compute_score_modified(A, k, M, s, i, reuse_sum);
                *score = diff_mod;
                *index_to_move = i;
                *(s + i ) = -*(s + i);
                *(reuse_sum) = original_sum;
                first_moved ++;
            }
            else{
                *(s + i ) = -*(s + i);
                si = *(s + i);
                for(j=0;j<A->n;j++){
                    printf("\ns[%d]= %f", j, *(s + j));
                    fflush(stdout);
                }
                *(reuse_sum) = *(reuse_sum) + (2 * ((double)(*(k +i ) * si)) /  (double) M);
                diff_mod = compute_score_modified(A, k, M, s, i, reuse_sum);
                if (diff_mod > *score ){
                    *score = diff_mod;
                    *index_to_move = i;
                }
                *(s + i ) = -*(s + i);
                *(reuse_sum) = original_sum;
            }
        }
    }
    return;
}



double compute_score_modified(const struct _spmat *A, const int *k, int M, double *s, int row_number, double *reuse_sum) {
    node **rows = A->private;
    double di, dgii;
    int i;
    double res, tmp_sum;
    node *current;
    double A_sum = 0.0;
    double k_row_number = (double)*(k + row_number);
    current = *(rows + row_number);

    while(current != NULL){
        A_sum += *(s + current->col);
        current = current->next;
    }


    for(i=0;i<A->n;i++){
        printf("\ns[%d]= %f", i, *(s + i));
        fflush(stdout);

    }

    tmp_sum = A_sum - (k_row_number * (*(reuse_sum)));

    /*
    for(current = *(rows + row_number); current < current + spmat_non_zero; current++){
        current_col = current->col;
        A_sum += *(s + current_col);
        redundent += (double)(*(k + current_col));
    }


    redundent *= ( (k_row_number) / (double)M );
    tmp_sum = A_sum - *(reuse_sum) * k_row_number + 2 * redundent;
     */
    di = s[row_number];
    dgii = (k_row_number * k_row_number / (double) M);
    res = 4 * di * tmp_sum + 4 * dgii;
    return res;
}












