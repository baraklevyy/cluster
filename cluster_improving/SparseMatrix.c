
#include <stdio.h>
#include "SparseMatrix.h"
#include <assert.h>
#include <stdlib.h>
#include "Common.h"


/*l1_norm == 0 if Matrix_Shifting is not necessary*/
void list_multiplay(const struct _spmat *A, const double *v, double *result) {
    int n, current_row, v_elem_num, i;
    double sum_so_far = 0.0;
    node **outer_Array, *current_node;
    double l1_modified;

    int* onces  = A->onces_num;
    outer_Array = A->private;
    n = A->n;
    for (current_row = 0; current_row < n; ++current_row) {
        current_node = outer_Array[current_row];
        v_elem_num = *(onces + current_row);
        sum_so_far = 0.0;
        for (i = 0; i < v_elem_num; i++) {
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
        goto l_cleanup;
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
    l_cleanup:
    if (status != SUCCESS_STATUS_CODE) {
        free(new_node);
        new_node = NULL;
        exit(status);
    }
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

void list_cleanup(struct _spmat *A) {
    node** outer_array;
    node* head, *current_node;
    int dimantion, i;
    outer_array = A->private;
    dimantion = A->n;
    i = 0;
    for (i = 0; i < dimantion; ++i) {
        head = outer_array[i];
        while ((current_node = head) != NULL) {/*set currentNode to head, stop when empty*/
            head = head->next;
            free(current_node);
        }
    }
    free(A->onces_num);
    free(outer_array);
    free(A);
}

spmat* spmat_allocate_list(int n) {
    Status status = INVALID_STATUS_CODE;
    spmat *sp = NULL;
    node **rows = NULL;
    int *onces;
    /*Initializing functions pointers*/
    void (*cleaup_ptr)(struct _spmat *);
    void (*add_row_ptr)(struct _spmat *, const int *, int, int);
    void (*mult_list_ptr)(const struct _spmat *, const double *, double *);
    add_row_ptr = &(add_row_list);
    cleaup_ptr = &(list_cleanup);
    mult_list_ptr = &(list_multiplay);
    /*Allocating spmat*/
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
    /*Initiazling variables*/
    sp->n = n;
    sp->private = rows;
    sp->onces_num = onces;
    sp->add_row = add_row_ptr;
    sp->free = cleaup_ptr;
    sp->mult = mult_list_ptr;

    status = SUCCESS_STATUS_CODE;
    return sp;

}
