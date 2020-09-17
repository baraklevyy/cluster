/**
 * ----------------------------------------------------------------------------------------------------------------------------
 * ---------------------------------------SPARSE_MATRIX--------------------------------------------------------------
 *
 * Purpose: implementation of a sparse matrix with linked lists
 *
 * spmat_allocate_list  - allocates linked list
 * list_multiplay		- multiplies vector and matrix (represented by linked list)
 * add_row_list			- adds row to the sparse matrix
 *
 */
#ifndef CLUSTER_IMPROVING_SPARSEMATRIX_H
#define CLUSTER_IMPROVING_SPARSEMATRIX_H

/**
 * Type used to represent single node
 */
typedef struct _node {
    int col;
    struct _node * next;
} node;

/**
 * Type used to represent sparse matrix
 */
typedef struct _spmat {
    /* Matrix size (n*n) */
    int		n;
    int *onces_num;
    int *relevant_indices;


    /** Private field for inner implementation.
     * This attribute indicates the pointer into the linked list array */
    void *private;
} spmat;

/* Allocates a new sparse matrix(linked-lists implementation) of size n */

/**
 * Function: spmat_allocate_list
 *
 * Purpose: Allocates a new linked-lists sparse matrix of size n
 *
 * Parameters:
 * 		@param n[in] -- size of matrix
 */
    spmat* spmat_allocate_list(int n);

/**
 * Function: list_multiplay
 *
 * Purpose: Multiplies matrix A (represented by linked list) with vector v
 *
 * Parameters:
 * 		@param A[in] --       sparse matrix that represent the group of vertices
 * 		@param v[in] --       vector that multiplied with function
 * 		@param result[out] -- vector (pre-allocated) into which the result of multiplication is loaded
 */
    void list_multiplay(const struct _spmat *A, const double *v, double *result);

/**
 * Function: add_row_list
 *
 * Purpose: Adds row i to the matrix A
 *
 * Parameters:
 * 		@param A[in/out] -- sparse matrix that represent the group of vertices, updated by the function
 * 		@param row[in] --   row that needs to be added
 * 		@param size[in] --  size of the row
 * 		@param i[in] --     index of current row
 *
 */
    void add_row_list(struct _spmat *A, const int *row, int size, int i);



#endif /*CLUSTER_IMPROVING_SPARSEMATRIX_H */
