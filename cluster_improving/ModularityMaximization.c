#include "ModularityMaximization.h"
#include <stdio.h>
#include <memory.h>
#include <float.h>

void modularity_max1(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *indices, int *number_of_1) {
    int i, j, number_of_one;
    double delta_q, sj, s_max_index, *s_ptr;
    double current_improve, max_improve, previous_improve;
    int n = A->n;
    int index_of_max_score, index_of_max_improve;
    double original_reuse_sum;
    double current_score, max_score, reuse_sum;

    reuse_sum = 0.0;
    for (i = 0; i < n; i++) {
        reuse_sum += *(k + i) * (*(s + i));
    }

    do {
        /* set to zero relevant elements of moved */
        memset(moved, 0, n * sizeof(int));
        max_improve = LOWEST_VALUE;
        previous_improve = 0.0;
        for (i = 0; i < n; i++) {
            max_score = LOWEST_VALUE;
            for (j = 0; j < n; j++) {
                if (*(moved + j) == 0) {
                    sj = *(s + j);
                    *(s + j) = -sj;
                    original_reuse_sum = reuse_sum;
                    reuse_sum += (2 * ((double)(*(k + j)) * (-sj)));
                    current_score = compute_score1(A, k, M, s, j, reuse_sum);
                    *(s + j) = sj;
                    reuse_sum = original_reuse_sum;
                    /*reuse_sum = original_reuse_sum;*/
                    index_of_max_score = max_score < current_score ? j : index_of_max_score;
                    max_score = max_score < current_score ? current_score : max_score;

                }
            }
            s_max_index = *(s + index_of_max_score);
            *(s + index_of_max_score) = -s_max_index;

            reuse_sum += (2 * ((double) (*(k + index_of_max_score)) * (-s_max_index)));
            *(indices + i) = index_of_max_score;
            if (i == 0)
                current_improve = max_score;
            else
                current_improve = previous_improve + max_score;

            index_of_max_improve = current_improve > max_improve ? i : index_of_max_improve;
            max_improve = current_improve > max_improve ? current_improve : max_improve;
            previous_improve = current_improve;
            *(moved + index_of_max_score) = 1;
        }

        for (i = n - 1; i > index_of_max_improve; i--) {
            j = *(indices + i);
            sj = *(s + j);
            *(s + j) = -sj;
            reuse_sum += (2 * ((double) (*(k + j)) * (-sj)));
        }
        if (index_of_max_improve == n - 1)
            delta_q = 0.0;
        else
            delta_q = max_improve;
    } while (IS_POSITIVE(delta_q));
    /*counting the number of '1' in s*/
    number_of_one = 0;
    for (s_ptr = s; s_ptr < (s + n); s_ptr++) {
        if (*(s_ptr) == 1.0)
            number_of_one += 1;
    }
    *(number_of_1) = number_of_one;
    return;
}



double compute_score1(const struct _spmat *A, const int *k, int M, double *s, int row_number, double reuse_sum){
    node **rows;
    node *current;
    double res, m;
    double A_sum = 0.0;
    double k_row_number = (double)(*(k + row_number));
    rows = A->private;
    m = (double)M;
    current = *(rows + row_number);

    while(current != NULL){
        A_sum += *(s + current->col);
        current = current->next;
    }
    res = 4 * (*(s + row_number) * (A_sum - (k_row_number * reuse_sum / m)) +((k_row_number * k_row_number) / m));
    return res;
}
