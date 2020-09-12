
#ifndef CLUSTER_IMPROVING_SPARSEMATRIX_H
#define CLUSTER_IMPROVING_SPARSEMATRIX_H
typedef struct _node {
    int col;
    int original;
    struct _node * next;
} node;

typedef struct _spmat {
    /* Matrix size (n*n) */
    int		n;
    int *onces_num;
    int *relevant_indices;

    /* Adds row i the matrix. Called before any other call,
     * exactly n times in order (i = 0 to n-1) */
   /* void(*add_row)(struct _spmat *A, const int *row, int size, int i);*/

    /* Frees all resources used by A */
    /*void(*free)(struct _spmat *A);*/

    /* Multiplies matrix A by vector v, into result (result is pre-allocated) */
   /* void(*mult)(const struct _spmat *A, const double *v, double *result);*/

    /* Private field for inner implementation.
     * Should not be read or modified externally */
    void *private;
} spmat;

/* Allocates a new linked-lists sparse matrix of size n */
spmat* spmat_allocate_list(int n);
void list_multiplay(const struct _spmat *A, const double *v, double *result);
void add_row_list(struct _spmat *A, const int *row, int size, int i);



#endif /*CLUSTER_IMPROVING_SPARSEMATRIX_H */
