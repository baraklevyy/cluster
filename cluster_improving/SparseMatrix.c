
#include <stdio.h>
#include "SparseMatrix.h"
#include <assert.h>
#include <stdlib.h>
#include "Common.h"

void list_multiplay(const struct _spmat *A, const double *v, double *result) {
    int n, current_row;
    double sum_so_far;
    node **outer_Array, *current_node;
    outer_Array = A->private;
    n = A->n;
    for (current_row = 0; current_row < n; ++current_row) {
        current_node = outer_Array[current_row];
        sum_so_far = 0.0;
        while(current_node != NULL){
            sum_so_far += *(v + current_node->col);
            current_node = current_node->next;
        }
        *(result + current_row) += sum_so_far;
    }

}

/*add element to list after the specific element(elem) with column (col)*/
node* add_to_list(int col, node *elem) {
    Status status = INVALID_STATUS_CODE;
    node *new_node = (node*)malloc(sizeof(node));
    if (NULL == new_node) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    new_node->col = col;
    new_node->original = col;
    new_node->next = NULL;
    if (elem == NULL) {
        return new_node;
    }
    elem->next = new_node;

    status = SUCCESS_STATUS_CODE;
    return new_node;
}

void add_row_list(struct _spmat *A, const int *row, int size, int i) {
    int column_number;
    int value;
    node *cell;
    node** rows = A->private;
    cell = rows[i];
    column_number = 0;
    /*	iterating over row*/
    for (column_number = 0; column_number < size; ++column_number) {
        value = row[column_number];
        if (cell == NULL) {/*initialize the first element of the outerArray*/
            cell = add_to_list(value, cell);
            rows[i] = cell;
        }
        else {
            cell = add_to_list(row[column_number], cell);
        }
    }
}


/*
void list_cleanup(struct _spmat *A) {
    node** outer_array;
    node* next_node, *current_node;
    int n, i;
    outer_array = A->private;
    n = A->n;
    i = 0;
    for (i = 0; i < n; ++i) {
        next_node = *(outer_array +i);
        current_node = next_node;
        while (current_node != NULL) {
            next_node = next_node->next;
            free(current_node);
            current_node = next_node;
        }
    }

    free(outer_array);

}
*/
spmat* spmat_allocate_list(int n) {
    Status status = INVALID_STATUS_CODE;
    spmat *sp = NULL;
    node **rows = NULL;
    int i, *onces, *relevant_indices;
    sp = (spmat *) malloc(sizeof(spmat));
    if (NULL == sp) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    /*Rows*/
    rows = (node **) calloc(n, sizeof(node *));
    if (NULL == rows) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    onces = (int *) malloc(n * sizeof(int));
    if (NULL == onces) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    relevant_indices= (int *) malloc(n * sizeof(int));
    if (NULL == relevant_indices) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        exit(status);
    }
    /* initialized relevant indices 0 - (n-1) */
    for(i = 0; i < n; i++)
        *(relevant_indices + i) = i;
    /*Initiazling variables*/
    sp->n = n;
    sp->private = rows;
    sp->onces_num = onces;
    sp->relevant_indices = relevant_indices;
    status = SUCCESS_STATUS_CODE;
    return sp;

}
