#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SparseMatrix.h"
#include "Common.h"
#include "Utility.h"
#include "B.h"
#include "Algorithm2.h"
#include"ModularityGroupsDivision.h"

int main(int argc, char *argv[]) {
    clock_t	start, end;
    Status status;
    int number_of_1 , M, n, sanity_check, /*size*/
            number_of_groups, number_of_written_elements;
    pointers *main_pointer;
    spmat *A;
    FILE *write_ptr;
    allocations *alloc;
/*
    int v_elem_num, index;
    int i;
    node *nnpointer, **nnouterarry ;
*/

/* start measuring time */
    start = clock();


     /*status = generate_graph();*/
    /*seed random*/
    srand((unsigned int) time(0));
    number_of_1 = 0;
    number_of_groups = number_of_1;
    number_of_1 = number_of_groups;
    status = INVALID_STATUS_CODE;
    number_of_written_elements = 1; /*allocating the first slot for the number of groups*/
    number_of_groups = 0;
    status = extract_matrix_size(argc, argv, &n);
    /*size = n; */
    alloc = alloc_allocations(n);
    A = spmat_allocate_list(n);
    status = graph_loading(argc, argv, A, alloc->k, &M, alloc->rows_helper);
    main_pointer = initialized_pointer(alloc, A);


/*

    nnouterarry = A->private;
    for (i = 0; i < A->n; ++i) {
        nnpointer = ((node*)A->private + i);
        nnpointer = nnouterarry[i];
        v_elem_num = *(A->onces_num + i);
        index = 0;
        printf("\n%s ","|->");
        fflush(stdout);
        for (index= 0; index < v_elem_num; index++) {
            printf("%d ->",nnpointer->original);
            fflush(stdout);
            nnpointer = nnpointer->next;
        }
    }
    */

    if(M == 0){
        status = ZERO_NUMBER_OF_EDGES;
        get_error_message(status);
        exit(status);
    }


    modularity_division_rec(A, alloc->k, alloc, M, -1.0, number_of_1, &number_of_groups, &number_of_written_elements);
/*
 *
    nnouterarry = main_pointer->A_outer_array_helper;
    for (i = 0; i < A->n; ++i) {
        nnpointer = ((node*)A->private + i);
        nnpointer = nnouterarry[i];
        printf("\n%s ","|->");
        fflush(stdout);
        while(nnpointer != NULL){
            printf("%d ->",nnpointer->original);
            fflush(stdout);
            nnpointer = nnpointer->next;
        }
    }

*/
/*
    *(alloc->output_array) = number_of_groups;
    for(i = 0; i < number_of_written_elements; i++ ){
        printf("output_array[%d] = %d\n", i, *(alloc->output_array + i));
        fflush(stdout);
    }
*/
    *(alloc->output_array) = number_of_groups;
    write_ptr = fopen(*(argv + 2),"wb");
    sanity_check = fwrite((int*)(alloc->output_array), sizeof(int), number_of_written_elements, write_ptr);
    if(sanity_check != number_of_written_elements){
        status = FWRITE_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    fclose(write_ptr);





    /*
    f_array(A, k, M, f);
    l1 = L1_norm(A, k, M, f);
    algorithm2_modified(A, k, M, s, f, l1, &number_of_1, normalized_eig_vec, random_normalized_vector);
    split_mat(A,a1,a2,&k,s,number_of_1,&rows_helper,onces_helper,&outer_array_helper, relevant_indices_helper);
     */





    /*
    nnouterarry = a2->private;
    for (i = 0; i < a2->n; ++i) {
        nnpointer = nnouterarry[i];
        v_elem_num = *(a2->onces_num + i);
        index = 0;
        for (index= 0; index < v_elem_num; index++) {
            printf("a1.private[%d,%d] = %d \n", i, index, nnpointer->col);
            printf("a1.private(original)[%d,%d] = %d \n", i, index, nnpointer->original);
            fflush(stdout);
            nnpointer = nnpointer->next;
        }
    }

    for(i=0;i<n;i++) {
        printf("k[%d] = %d \n", i, *(k + i));
        fflush(stdout);
    }
    for(i=0;i<n;i++) {
        printf("rows_helper[%d] = %d \n", i, *(rows_helper + i));
        fflush(stdout);
    }
    for(i=0;i<a1->n;i++) {
        printf("a1.onces[%d] = %d \n", i, *(a1->onces_num + i));
        fflush(stdout);
    }
    for(i=0;i<a2->n;i++) {
        printf("a2.onces[%d] = %d \n", i, *(a2->onces_num + i));
        fflush(stdout);
    }
    for(i=0;i<a1->n;i++) {
        printf("A1.relevant[%d] = %d \n", i, *(a1->relevant_indices + i));
        fflush(stdout);
    }
    for(i=0;i<a2->n;i++) {
        printf("A2.relevant[%d] = %d \n", i, *(a2->relevant_indices + i));
        fflush(stdout);
    }
*/

/*
    if(A->private == main_pointer->A_outer_array_helper){
        outer_array_free(main_pointer->A_outer_array_helper, size);
        free(main_pointer->outer_array_helper);
    }
    else{
        outer_array_free(main_pointer->outer_array_helper, size);
        free(main_pointer->A_outer_array_helper);
    }
    */
    free_allocations(main_pointer);
    free(alloc);
    end = clock();
    printf("Execution took %f seconds\n", ((double)(end-start) / CLOCKS_PER_SEC));
    fflush(stdout);
    status = SUCCESS_STATUS_CODE;
    return 0;

}
