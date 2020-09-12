
#ifndef CLUSTER_IMPROVING_OPTIMIZATIONMAXIMIZATION_H
#define CLUSTER_IMPROVING_OPTIMIZATIONMAXIMIZATION_H
void modularity_max_modified(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *indicies,int *number_of_1 );
void find_improved_partition_modified(const struct _spmat *A, const int *k, int M, double *s,int *moved, int *improve_index,
                             double *max_improve, int *indicies, int *number_of_1, int flag_first_iter, double *reuse_sum);
void find_vertex_modified(const struct _spmat *A, const int *k, int M,double *s, int *moved, int *index_to_move, double *score, double *reuse_sum);
double compute_score_modified(const struct _spmat *A, const int *k, int M, double *s, int row_number, double *reuse_sum);

#endif /*CLUSTER_IMPROVING_OPTIMIZATIONMAXIMIZATION_H */
