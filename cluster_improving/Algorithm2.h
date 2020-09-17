/**
 * ---------------------------------------------------------------------------------------------------------------
 * ---------------------------------------ALGORITHM2--------------------------------------------------------------
 *
 * Purpose: this module is used to find vector s. This vector contain +- 1.0 which represents division of group into two separated groups.
 * 			Return vector of 1's if no division is found
 *
 * algorithm2 - finds division
 */
#ifndef CLUSTER_IMPROVING_ALGORITHM2_H
#define CLUSTER_IMPROVING_ALGORITHM2_H

#include "Common.h"
#include "B.h"
#include "SparseMatrix.h"
#include "vector.h"
/**--------------------------------------------------------------------------------------------------------------
 * Function: algorithm2
 *
 * Purpose: function finds division (represented by vector s that consists of 1.0 and -1.0) of the given group into two.
 * 			 If division is'nt possible, vector s includes only 1.
 *
 * Parameters:
 * 		@param A [in] -- sparse matrix that represents the group of vertices (using linked lists data structure)
 * 		@param k [in] -- vector that represents the degrees of vertices in the group
 * 		@param M [in] -- sum of all the degrees of vertices in the initial group
 * 		@param alloc [in/out] -- pointer to struct. This struct holds all the pointers to arrays that I used in order to save calculation time.
 * 		@param l1_norm [in] -- the 1-norm of of current matrix.
 *
 * 	@return
 * 		SUCCESS_STATUS_CODE -- if function succeeded to find a division
 *		NEGATIVE_EIGEN_VALUE -- if eigenvalue that was found is negative, means that group is not divisible
 *		GROUP_NOT_DIVISIBLE_CODE -- if group is not divisible
 *
 */

Status algorithm2(const struct _spmat *A, const int *k, int M, allocations *alloc, double l1_norm) ;

#endif /*CLUSTER_IMPROVING_ALGORITHM2_H*/
