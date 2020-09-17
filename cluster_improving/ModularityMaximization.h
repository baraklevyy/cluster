/**
* ----------------------------------------------------------------------------------------------------------------------------
 * ---------------------------------------ModularityMaximization--------------------------------------------------------------
 *
 * Purpose: Optimized the network modularity by using the 'cluser modularity maximization' algorithm.
 *
 * modularity_max   - maximizes the division
 * compute_score	- computes score when vector is moved
 */

#include <stdio.h>
#include "Common.h"
#include "SparseMatrix.h"
#include <stdlib.h>
#include <stdlib.h>

#ifndef CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
#define CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H

/**-------------------------------------------------------------------------------------------------------------------------------
 * Function: modularity_max
 *
 * Purpose: the main function of this module, finds optimized division of the group based on initial division s.
 * 			function finds improved partition of the group till no improve is possible
 *
 * Parameters:
 * 		@param A [in] --            sparse matrix that represents the group of vertices
 * 		@param k [in] --            vector that represents degrees of vertices in the group
 * 		@param M [in] --            sum of all the degrees of vertices in the initial group
 * 		@param s [in/out] --        vector that represents initial division of the group into two groups,
 * 						            function  updates it to the improved partition
 * 		@param moved [in] --        helper vector that indicates for each vertex if it was already moved
 * 		@param indicies [in]--      helper vector holds for each step which vertex was moved
 * 		@param number_of_1 [out] -- number of 1 in vector s after maximization
 *
 *
 */
void modularity_max(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *indicies, int *number_of_1, double reuse_sum);

/**-------------------------------------------------------------------------------------------------------------------------------
 * Function: compute_score
 *
 * Purpose: finds the increase or decrease in modularity if vertex with index row_number will be moved
 *
 * Parameters:
 * 		@param A [in] --          sparse matrix that represents the group of vertices
 * 		@param k [in] --          vector that represents the degrees of vertices in the group
 * 		@param M [in] --          sum of all the degrees of vertices in the initial group
 * 		@param s [in] --          vector that represents initial division of the group into two groups
 * 		@param row_number [in] -- variable that indicates which vertex is need to be moved
 * 		@reuse_sum [in] --
 *
 * @return increase or decrease in modularity
 *
 */
double compute_score(const struct _spmat *A, const int *k, int M, double *s, int row_number, double reuse_sum);

#endif /*CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H*/
