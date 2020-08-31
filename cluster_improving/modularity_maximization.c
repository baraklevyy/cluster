/*
 * modularity_maximization.c

 */
#include <stdlib.h>
#include "modularity_maximization.h"


void modularity_max(const struct _spmat *A, const int *k, int M, int *s, int *moved, int *indicies){
    int i, j;
    double improve;
    int improve_index, A_size = A->n;
    double delta_q;
    do{
        /* set to zero relevant elements of moved */
        for(i = 0; i<A_size; i++){
            moved[i]=0;
        }
        find_improved_partition(A, k, M, s,moved, &improve_index, &improve, indicies);
        if(improve_index == A_size-1){
            delta_q =0;
        }
        else{
            delta_q = improve;
        }
        for (i=A_size-1; i>improve_index; i--){
            j = *(indicies +i);
            *(s +j ) = - *(s +j);
        }
    }
    while( IS_POSITIVE(delta_q));
    return;
}


void find_improved_partition(const struct _spmat *A, const int *k, int M, int *s,int *moved, int *improve_index,double *max_improve, int *indicies){
    int i;
    double prev_improve,curr_improve;
    int ind_for_move;
    double score;
    for(i=0;i<A->n ; i++){
        find_vertex(A, k, M,s, moved, &ind_for_move, &score);

        *(s + ind_for_move) = -*(s + ind_for_move); /*move vertex */
        *(indicies + i) = ind_for_move;
        if (i==0){
            *improve_index =i;
            *max_improve = score;
            prev_improve = score;
        }
        else{
            curr_improve = prev_improve + score;
            if(curr_improve>*max_improve){
                *max_improve = curr_improve;
                *improve_index =i;
            }
            prev_improve = curr_improve;
        }
        *(moved + ind_for_move) =1; /*mark this index as moved */
    }
    return;
}

/*double compute_modularity(const struct _spmat *A, const int *k, int M, int A_size, int *s,double *b_mult_s){
    double res;
    b_mult(A, k, M, s, b_mult_s , f, 0);
    res = vec_dot_int(s, b_mult_s, A_size);
    return res;
}
*/

void find_vertex(const struct _spmat *A, const int *k, int M,int *s, int *moved, int *index_to_move, double *score){
    /* find vertex with biggest increase */
    double diff_mod;
    int i,first_moved;
    first_moved =0;
    for(i=0;i< A->n ;i++){
        if(*(moved + i)==0){ /* true only for vertexes that is not moved */
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
                if (diff_mod >*score ){
                    *score = diff_mod;
                    *index_to_move = i;
                }
                *(s + i ) = -*(s + i);
            }
        }
    }
    return;
}

double compute_score(const struct _spmat *A, const int *k, int M, int *s, int row_number){
    int column;
    node **rows = A->private;
    node *current = rows[row_number];
    double di,dgii;
    double res=0, temp=0;
    for (column=0;column < A->n; column++){
        while (current != NULL) {
            if (current->col == column) {
                temp += (1.0 - ((double)k[row_number] * (double)k[column]) / (double)M) * (double)s[column];

                break;
            }
            else if (current->col > column || !current->next) {
                temp += (-((double)k[row_number] * (double)k[column]) / (double)M) * (double)s[column] ;
                break;
            }
            current = current->next;

        }


    }
    di = s[row_number] ;
    dgii = ((double)k[row_number] *(double)k[row_number] ) / (double)M;
    res += 4*di* temp + 4*dgii;
    return res;
}
