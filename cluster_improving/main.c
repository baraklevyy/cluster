#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SparseMatrix.h"
#include "Common.h"
#include "Utility.h"
#include"ModularityGroupsDivision.h"

int main(int argc, char *argv[]) {
    int number_of_1 , M, n, sanity_check,number_of_groups, number_of_written_elements;
    Status status;
    clock_t	start, end;
    pointers *main_pointer;
    spmat *A;
    FILE *write_ptr;
    allocations *alloc;
/* start measuring time */
    start = clock();
    status = INVALID_STATUS_CODE;
    number_of_written_elements = 1; /*reserving the first slot for the total number of groups*/
    number_of_groups = 0;
    number_of_1 = 0;
    status = extract_matrix_size(argc, argv, &n);
    alloc = alloc_allocations(n); /*allocating helper arrays*/
    A = spmat_allocate_list(n);
    status = graph_loading(argc, argv, A, alloc->k, &M, alloc->rows_helper);
    main_pointer = initialized_pointer(alloc, A); /*keeping addresses of helper arrays*/
    if(M == 0){
        status = ZERO_NUMBER_OF_EDGES;
        get_error_message(status);
        exit(status);
    }
    modularity_division_rec(A, alloc->k, alloc, M, -1.0, number_of_1, &number_of_groups, &number_of_written_elements);
    /*writing the output file*/
    *(alloc->output_array) = number_of_groups;
    write_ptr = fopen(*(argv + 2),"wb");
    sanity_check = fwrite((int*)(alloc->output_array), sizeof(int), number_of_written_elements, write_ptr);
    if(sanity_check != number_of_written_elements){
        status = FWRITE_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    /*finishing execution*/
    fclose(write_ptr);
    free_allocations(main_pointer);
    free(alloc);
    end = clock();
    printf("Execution took %f seconds\n", ((double)(end-start) / CLOCKS_PER_SEC));
    fflush(stdout);
    status = SUCCESS_STATUS_CODE;
    return 0;

}
