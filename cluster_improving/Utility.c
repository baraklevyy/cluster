#define _CRT_SECURE_NO_WARNINGS



#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "Common.h"
#include "SparseMatrix.h"



/*example graph generator.*/
Status generate_graph() {
    Status status = INVALID_STATUS_CODE;
    FILE *file;
    int sanity_check;
    int arr[39] = {8,5,1,3,4,5,7,3,0,2,6,2,1,6,4,0,4,5,7,4,0,3,5,7,4,0,3,4,7,3,1,2,7,5,0,3,4,5,6};
    file = fopen("C:\\Users\\barak\\CLionProjects\\cluster_improving\\graph8.in", "wb");
    sanity_check = fwrite(arr, sizeof(int), 39, file);
    if (39 != sanity_check) {
        status = FREAD_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    status = SUCCESS_STATUS_CODE;
    return status;
    l_cleanup:
    exit(status);

}
void subtract_vector_from_mat(const struct _spmat *A, int *k, int M, int *g, int ng, int row, int *result) {
    int i;
    node** matrix_rows = A->private;
    node* current = matrix_rows[row];
    for (i = 0; i < ng; ++i) {
        if (g[i] == current->col) {
            result[i] = 1 - (k[row] * k[i]) / M;
        }
        else {
            while (g[i] >= current->col && current != NULL) {
                current = current->next;
            }
            if (g[i] == current->col) result[i] = 1 - (k[row] * k[i]) / M;
            if (g[i] < current->col) continue;
        }
    }
}


Status extract_matrix_size(int argc, char** argv, int *n) {
    Status status = INVALID_STATUS_CODE;
    int sanity_check;
    FILE* input_file;
    if (argc != 2) {
        status = INVALID_ARGUMENTS_CODE;
        get_error_message(status);
        goto l_cleanup;
    }
    input_file = fopen(*(argv + 1), "rb");

    if (NULL == input_file) {
        status = FOPEN_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }
    sanity_check = fread(n, sizeof(int), 1, input_file);	/*first values indicates the number of vertices*/
    if (1 != sanity_check) {
        status = FREAD_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    status = SUCCESS_STATUS_CODE;
    return status;
    l_cleanup:
    exit(status);
}
/*This function return a Status variable in order to indicate errors.
 * It is also loaded into A, k, M the corresponding values (load the actuall graph)
 * */
Status graph_loading(int argc, char** argv, struct _spmat *A, int *k, int *M) {
    Status status = INVALID_STATUS_CODE;
    int n, sanity_check, current_num_of_neighbors, current_row, current_neighbor, cur_neighbor_i;
    int *current_vector;
    FILE* input_file;
    *M = 0;/*initializing the graph total ranking*/

    if (argc != 2) {
        status = INVALID_ARGUMENTS_CODE;
        get_error_message(status);
        goto l_cleanup;
    }
    input_file = fopen(argv[1], "rb");
    if (NULL == input_file) {
        status = FOPEN_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }
    sanity_check = fread(&n, sizeof(int), 1, input_file);	/*first values indicates the number of vertices*/
    if (1 != sanity_check) {
        status = FREAD_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    for (current_row = 0; current_row < n; ++current_row) {
        sanity_check = fread(&current_num_of_neighbors, sizeof(int), 1, input_file);
        if (1 != sanity_check) {
            status = FREAD_FAILED_CODE;
            get_error_message(status);
            goto l_cleanup;
        }
        *(k + current_row) = current_num_of_neighbors; /*loading K , the ranking vector*/
        *(A->onces_num + current_row) = current_num_of_neighbors; /*loading K , the ranking vector*/
        *M += current_num_of_neighbors; /*updating total graph ranking*/
        current_vector = (int*)malloc(current_num_of_neighbors * sizeof(int));
        if (NULL == current_vector) {
            status = MALLOC_FAILED_CODE;
            get_error_message(status);
            goto l_cleanup;
        }

        /*adding to to sparse matrix*/
        for (cur_neighbor_i = 0; cur_neighbor_i < current_num_of_neighbors; cur_neighbor_i++) {
            sanity_check = fread(&current_neighbor, sizeof(int), 1, input_file);
            if (1 != sanity_check) {
                status = FREAD_FAILED_CODE;
                get_error_message(status);
                goto l_cleanup;
            }
            *(current_vector + cur_neighbor_i) = current_neighbor;/*loading the neighbor into the vector to be inserted into the sparse matrix*/		}
        A->add_row(A, current_vector, current_num_of_neighbors, current_row); /*Loading the sparse matrix*/
        free(current_vector);
    }
    status = SUCCESS_STATUS_CODE;
    return status;

    l_cleanup:
    exit(status);
}






