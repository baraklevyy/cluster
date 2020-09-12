
#include <stdlib.h>

#include "ModularityMaximization.h"
#include <stdio.h>

void modularity_max(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *indicies, int *number_of_1 ){
    int i, j;
    int improve_index;
    double delta_q;
    double improve;
    int flag_first_iter =1; /* indicate if this first iteration of do-while loop ---> for number_of_1 */
    int local_num_1 =0;
    int n = A->n;
    do{
        /* set to zero relevant elements of moved */
        for(i = 0; i<n; i++){
            moved[i]=0;
        }
        find_improved_partition(A, k, M, s,moved, &improve_index, &improve, indicies,&local_num_1, flag_first_iter);
        if(improve_index == n - 1){
            delta_q = 0;
        }
        else{
            delta_q = improve;
        }
        for (i = n - 1; i > improve_index; i--){
            j = *(indicies + i);
            *(s + j) = - *(s +j);
            /* update counter for number of ones */
            if(*(s +j) == -1){
                local_num_1 -=1;
            }
            else local_num_1 +=1;
        }
        flag_first_iter =0;
    }
    while(IS_POSITIVE(delta_q));
    *number_of_1 =local_num_1;
    return;
}

void find_improved_partition(const struct _spmat *A, const int *k, int M, double *s,int *moved, int *improve_index,double *max_improve, int *indicies, int *number_of_1, int flag_first_iter){
    int i;
    double prev_improve,curr_improve;
    int ind_for_move;
    double score;
    int n = A->n;
    for(i=0;i< n; i++){
        find_vertex(A, k, M,s, moved, &ind_for_move, &score);
        *(s + ind_for_move) = -*(s + ind_for_move); /*move vertex */
        /* number of 1 */
        if(flag_first_iter == 1 ){ /*this is the first iteration */
            if(*(s + ind_for_move) == 1){
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
        if (i == 0){
            *improve_index = i;
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

void find_vertex(const struct _spmat *A, const int *k, int M,double *s, int *moved,
                 int *index_to_move, double *score){
    /* find vertex with biggest increase */
    double diff_mod;
    int i,first_moved;
    int n = A->n;
    first_moved =0;
    for(i=0;i< n ;i++){
        if(*(moved + i)==0){ /* true only for vertices that doesnt move */
            if(first_moved ==0){
                *(s + i) = -*(s + i);
                diff_mod = compute_score(A, k, M, s, i);
                *score = diff_mod;
                *index_to_move = i;
                *(s + i ) = -*(s + i);
                first_moved ++;
            }
            else{
                *(s + i ) = -*(s + i);
                diff_mod = compute_score(A, k, M, s, i);
                if (diff_mod > *score ){
                    *score = diff_mod;
                    *index_to_move = i;
                }
                *(s + i ) = -*(s + i);
            }
        }
    }
    return;
}

double compute_score(const struct _spmat *A, const int *k, int M, double *s, int row_number) {
    /*int column;
    node **rows = A->private;
    node *current = rows[row_number];
    double di, dgii;
    double res = 0, temp = 0;
    int n = A->n;
    for (column = 0; column < n; column++) {
        while (current != NULL) {
            if (current->col == column) {
                temp += (1.0 - ((double) k[row_number] * (double) k[column]) / (double) M) * (double)s[column];
                break;
            } else if (current->col > column || !current->next) {
                temp += (-((double) k[row_number] * (double) k[column]) / (double) M) * (double)s[column];
                break;
            }
            current = current->next;
        }
    }
    di = s[row_number];
    dgii = ((double) k[row_number] * (double) k[row_number]) / (double) M;
    res += 4 * di * temp + 4 * dgii;
    return res;
     */



    int n, i;
    node **rows;
    node *current;
    double di,dgii;
    double res = 0.0, temp = 0.0;
    double A_sum = 0.0, D_sum = 0.0;
    double k_row_number = (double)*(k + row_number);
    n =  A->n;
    rows = A->private;
    current = rows[row_number];
    for(i = 0; i < n; i++){
        D_sum += *(k + i) * (*(s + i));
    }
    D_sum /= M;

    while(current != NULL){
        A_sum += *(s + current->col);
        current = current->next;
    }

    temp = A_sum - (k_row_number * (D_sum));



    di = s[row_number] ;
    dgii = ((double)k[row_number] *(double)k[row_number] ) / (double)M;
    res += 4*di* temp + 4*dgii;
    return res;
}





