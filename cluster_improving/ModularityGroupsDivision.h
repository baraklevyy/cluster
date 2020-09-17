/**
* Purpose: detect community structures in the network (represented by matrix),
* 			by recursively dividing matrix into two groups
*
*modularity_division_rec - finds division of input into groups
*/
#ifndef CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H
#define CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H

#include "Common.h"

/**--------------------------------------------------------------------------------------------------------------
 * Function: modularity_division_rec
 *
 * Purpose: find a division of a given matrix into groups, such that whole modularity of the network is maximal
 *
 * Parameters:
 * 		@param A [in] --                              sparse matrix that represent the group of vertices
 * 		@param k [in] --                              vector that represents degrees of vertices in the group
 * 		@param alloc [in/out] --                      pointer to a helper struct that holds all of arrays used in a program,
 * 								                      function updates at outer_array (included in alloc) - represents final division into groups
 * 		@param M [in] --                              sum of all the degrees of vertices in the initial group
 * 		@param l1_norm [in] --                        the 1-norm of the matrix
 * 		@param number_of_1 [in/out] --                number of 1 in the vector s after division of initial group into two
 * 		@param number_of_groups [out] --              final number of groups in the clustering process
 * 		@param number_of_written_elements [in/out] -- helper variable that holds number of elements
 * 								                      that were already written to the outer(result) array
 *
 */
void modularity_division_rec(struct _spmat *A, int *k, struct _allocations *alloc, int M, double L1_NORM, int number_of_1,
                             int *number_of_groups, int *number_of_written_elements);

#endif /* CLUSTER_IMPROVING_MODULARITYGROUPSDIVISION_H */
