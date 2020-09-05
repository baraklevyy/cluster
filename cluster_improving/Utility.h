//
// Created by barak on 26/08/2020.
//

#ifndef CLUSTER_IMPROVING_UTILITY_H
#define CLUSTER_IMPROVING_UTILITY_H
Status generate_graph();
Status graph_loading(int argc, char** argv, struct _spmat *A, int *k, int *M, int *current_vector);

Status extract_matrix_size(int argc, char** argv, int *n);
Status isolated_nodes_handling(int argc, char** argv, int *n, int *output_array, int *number_of_groups, int *number_of_written_elements);



#endif //CLUSTER_IMPROVING_UTILITY_H
