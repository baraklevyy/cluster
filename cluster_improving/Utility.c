#define _CRT_SECURE_NO_WARNINGS



#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "SparseMatrix.h"



/*example graph generator.*/
Status generate_graph() {
    Status status = INVALID_STATUS_CODE;
    FILE *file;
    int sanity_check;
    int arr[23] = {6,3,3,4,5,2,2,5,3,1,3,5,3,0,2,4,2,0,3,3,0,1,2};
    file = fopen("C:\\Users\\barak\\CLionProjects\\cluster_improving\\graph6_test.in", "wb");
    sanity_check = fwrite(arr, sizeof(int), 23, file);
    if (23 != sanity_check) {
        status = FREAD_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }

    status = SUCCESS_STATUS_CODE;
    return status;
    l_cleanup:
    exit(status);

}





















Status extract_matrix_size(int argc, char** argv, int *n) {
    Status status = INVALID_STATUS_CODE;
    int sanity_check;
    FILE *input_file;
    if (argc != 3) {
        status = INVALID_ARGUMENTS_CODE;
        get_error_message(status);
        exit(status);
    }
    input_file = fopen(*(argv + 1), "rb");

    if (NULL == input_file) {
        status = FOPEN_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    sanity_check = fread(n, sizeof(int), 1, input_file); /*first values indicates the number of vertices*/
    if (1 != sanity_check) {
        status = FREAD_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    status = SUCCESS_STATUS_CODE;
    fclose(input_file);
    return status;
}

/*This function return a Status variable in order to indicate errors.
 * It is also loaded into A, k, M the corresponding values (load the actuall graph)
 * */
Status graph_loading(int argc, char** argv, struct _spmat *A, int *k, int *M, int *current_vector){
    Status status = INVALID_STATUS_CODE;
    int n, sanity_check, current_num_of_neighbors, current_row, current_neighbor, cur_neighbor_i;
    FILE* input_file;
    *M = 0;/*initializing the graph total ranking*/

    if (argc != 3) {
        status = INVALID_ARGUMENTS_CODE;
        get_error_message(status);
        exit(status);
    }
    input_file = fopen(*(argv + 1), "rb");
    if (NULL == input_file) {
        status = FOPEN_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    sanity_check = fread(&n, sizeof(int), 1, input_file);	/*first values indicates the number of vertices*/
    if (1 != sanity_check) {
        status = FREAD_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }

    for (current_row = 0; current_row < n; ++current_row) {
        sanity_check = fread(&current_num_of_neighbors, sizeof(int), 1, input_file);
        if (1 != sanity_check) {
            status = FREAD_FAILED_CODE;
            get_error_message(status);
            exit(status);
        }
        *(k + current_row) = current_num_of_neighbors; /*loading K , the ranking vector*/
        *(A->onces_num + current_row) = current_num_of_neighbors; /*loading K , the ranking vector*/
        *M += current_num_of_neighbors; /*updating total graph ranking*/
        /*adding to to sparse matrix*/
        for (cur_neighbor_i = 0; cur_neighbor_i < current_num_of_neighbors; cur_neighbor_i++) {
            sanity_check = fread(&current_neighbor, sizeof(int), 1, input_file);
            if (1 != sanity_check) {
                status = FREAD_FAILED_CODE;
                get_error_message(status);
                exit(status);
            }
            *(current_vector + cur_neighbor_i) = current_neighbor;/*loading the neighbor into the vector to be inserted into the sparse matrix*/
        }
        add_row_list(A, current_vector, current_num_of_neighbors, current_row); /*Loading the sparse matrix*/
    }
    status = SUCCESS_STATUS_CODE;
    fclose(input_file);
    return status;
}






