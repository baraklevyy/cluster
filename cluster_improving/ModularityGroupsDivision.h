
#ifndef CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H
#define CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H

#include "Common.h"


void modularity_division_rec(struct _spmat *A, int *k, struct _allocations *alloc, int M, double L1_NORM, int number_of_1,
                             int *number_of_groups, int *number_of_written_elements);

#endif /* CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H */
