
#ifndef CLUSTER_IMPROVING_VECTOR_H
#define CLUSTER_IMPROVING_VECTOR_H

void vec_normalize(double *v, int size);
int diff_below_epsilon(double *v1, double *v2, int size);
double vec_dot(const double *v1, const double *v2, int size);
double vec_dot_int(const int *v1, const double *v2, int size);
void generate_random_normalized_vector(double *v,  int size);
#endif //CLUSTER_IMPROVING_VECTOR_H
