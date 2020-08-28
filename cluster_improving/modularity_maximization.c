/*
 * modularity_maximization.c

 */
#include <stdlib.h>
#include "modularity_maximization.h"


Status modularity_max(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int *s){
    Status status = INVALID_STATUS_CODE;
    int *moved, *indicies, i, j;
    double improve;
    int improve_index;
    double delta_q;
    do{
        moved = (int*)calloc(g_size, sizeof(int));  /* create moved vector that will indicate if moved[i] vertex was already moved*/
        if (NULL == moved) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            exit(status);

        }
        indicies =(int*)calloc(g_size, sizeof(int));
        if (NULL == indicies) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            exit(status);}
        status = find_improved_partition(A, k, M, g, g_size,s,moved, &improve_index, &improve, indicies);
        if(improve_index == g_size-1){
            delta_q =0;
        }
        else{
            delta_q = improve;
        }
        for (i=g_size-1; i>improve_index; i--){
            j = *(indicies +i);
            *(s +j ) = - *(s +j);
        }
        free(moved);
        free(indicies);
    }
    while( IS_POSITIVE(delta_q));
    status = SUCCESS_STATUS_CODE;
    return status;
}


Status find_improved_partition(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int *s,int *moved, int *improve_index,double *max_improve, int *indicies){
    Status status = INVALID_STATUS_CODE;
    int i;
    double primary_modularity, prev_improve,curr_improve;
    int ind_for_move;
    double score;
    for(i=0;i<g_size; i++){
        status =  compute_modularity(A, k, M, g, g_size, s, &primary_modularity);
        status = find_vertex(A, k, M, g, g_size,s, primary_modularity, moved, &ind_for_move, &score);

        *(s + ind_for_move) = -*(s + ind_for_move); /*move vertex */
        printf("after_max_s %d: ", i);
        for (int i = 0; i < g_size; i++)
            printf("%d, ", s[i]);
        printf("\n");
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
    return status;
}

Status compute_modularity(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int *s, double *res){
    Status status = INVALID_STATUS_CODE;
    double *B_gag_mult_s;
    double L1norm = B_gag_L1_norm(A, k, M, g, g_size);
    B_gag_mult_s = (double*)malloc(g_size * sizeof(double));
    if (NULL == B_gag_mult_s) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);}
    B_gag_vec_mult_int(A, k, g, g_size, M, L1norm, s, B_gag_mult_s);
    *res = vec_dot_int(s, B_gag_mult_s, g_size);
    free(B_gag_mult_s);
    status = SUCCESS_STATUS_CODE;
    return status;
}


Status find_vertex(const struct _spmat *A, const int *k, int M, const int *g, int g_size, int *s, double prim_mod,int *moved, int *index_to_move, double *score){
    /* find vertex with biggest increase */
    Status status = INVALID_STATUS_CODE;
    double curr_mod, diff_mod;
    int i,first_moved;
    first_moved =0;
    for(i=0;i<g_size;i++){
        if(*(moved + i)==0){ /* true only for vertexes that is not moved */
            if(first_moved ==0){
                *(s + i) = -*(s + i);
                status = compute_modularity(A, k, M, g, g_size, s,&curr_mod); /* if its first vertex initialize max_mod */
                diff_mod = curr_mod - prim_mod;
                *score = diff_mod;
                *index_to_move = i;
                *(s + i ) = -*(s + i);
                first_moved ++;
            }
            else{
                *(s + i ) = -*(s + i);
                status = compute_modularity(A, k, M, g, g_size, s,&curr_mod);
                diff_mod = curr_mod - prim_mod;
                if (diff_mod >*score ){
                    *score = diff_mod;
                    *index_to_move = i;
                }
                *(s + i ) = -*(s + i);
            }
        }
    }
    return status;
}
