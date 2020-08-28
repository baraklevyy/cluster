//
// Created by barak on 26/08/2020.
//

#ifndef CLUSTER_IMPROVING_UTILITY_H
#define CLUSTER_IMPROVING_UTILITY_H
Status generate_graph();
Status graph_loading(int argc, char** argv, struct _spmat *A, int *k, int *M);
Status extract_matrix_size(int argc, char** argv, int *n);



#endif //CLUSTER_IMPROVING_UTILITY_H
