
#ifndef CLUSTER_IMPROVING_SPARSEMATRIX_H
#define CLUSTER_IMPROVING_SPARSEMATRIX_H
typedef struct _node {
    int col;
    struct _node * next;
} node;

typedef struct _spmat {
    /* Matrix size (n*n) */
    int		n;
    int *onces_num;
    int *relevant_indices;


    /* Private field for inner implementation.
     * Should not be read or modified externally */
    void *private;
} spmat;

/* Allocates a new linked-lists sparse matrix of size n */
spmat* spmat_allocate_list(int n);
void list_multiplay(const struct _spmat *A, const double *v, double *result);
void add_row_list(struct _spmat *A, const int *row, int size, int i);



#endif /*CLUSTER_IMPROVING_SPARSEMATRIX_H */
