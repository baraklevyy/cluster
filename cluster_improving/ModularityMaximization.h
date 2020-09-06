

/**
 * ----------------------------------------------------------------------------------------------------------------------------
 * ---------------------------------------MODULARITY_MAXIMIZATION--------------------------------------------------------------
 *
 * Purpose: this module is used to optimize
 *
 */


#ifndef CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
#define CLUSTER_IMPROVING_MODULARITY_MAXIMIZATION_H
#include "Common.h"
#include "SparseMatrix.h"


/**--------------------------------------------------------------------------------------------------------------
 * Function: find_vertex
 *
 * Purpose: from all the vertices that weren't moved yet,
 * 			find a vertex v that, when moved to the other group,
 * 			will give the biggest increase in the modularity (or smallest decrease if no increase is possible)
 *
 * Parameters:
 * 		_spmat *A (IN) -- sparse matrix that represent the group of vertices
 * 		*k (IN) -- vector that represents degrees of vertices in the group
 * 		M (IN) -- sum of all the degrees of vertices in the group
 * 		*s (IN) -- vector that represents initial division of the group into two groups
 * 		moved (IN) -- helper vector that indicates for each vertex if it was already moved
 * 		*index_to_move (OUT) -- pointer to a variable, function updates it to the index of the vertex that will be moved
 * 		*score (OUT) -- pointer to a double variable, function updates it to the decrease (or increase) in modularity
 * 						when vertex will be moved
 */

void find_vertex(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *index_to_move, double *score);

/**-------------------------------------------------------------------------------------------------------------------------------
 * Function: find_improved_partition
 *
 * Purpose: function finds improvement of the initial partition by iterating over all the vertices,
 * 			and moving each time one of them, until all the vertices have been moved
 *
 * Parameters:
 * 		_spmat *A (IN) -- sparse matrix that represent the group of vertices
 * 		*k (IN) -- vector that represents degrees of vertexes in the group
 * 		M (IN) -- sum of all the degrees of vertexes in the group
 * 		*s (IN/OUT) -- vector that represents initial division of the group into two groups,
 * 					   function updates it each time vertex is moved
 * 		moved (IN) -- helper vector that indicates for each vertex if it was already moved
 * 		*improve_index (OUT) -- pointer to a variable,
 * 								function updates it to the index of vertex that leads to the biggest increase when moved
 * 		*improve (OUT) -- pointer to a variable,
 * 						function updates it to the biggest increase in modularity that was found
 * 		*indicies (OUT)	-- helper vector contains for each iteration of function which vertex was moved
 * 		*number_of_1 (IN/OUT) -- pointer to a variable that counts number of 1 in vector s, updated by the function
 * 		flag_first_iter (IN) -- helper variable, indicates if it is the first iteration of the whole module
 *
 */
void find_improved_partition(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *improve_index,double *improve, int *indicies, int *number_of_1, int flag_first_iter);



/**-------------------------------------------------------------------------------------------------------------------------------
 * Function: compute_score
 *
 * Purpose: finds the increase or decrease in modularity if vertex with index row_number will be moved
 *
 * Parameters:
 * 		_spmat *A (IN) -- sparse matrix that represent the group of vertices
 * 		*k (IN) -- vector that represents degrees of vertexes in the group
 * 		M (IN) -- sum of all the degrees of vertexes in the group
 * 		*s (IN) -- vector that represents initial division of the group into two groups,
 * 		row_number(IN) -- variable that indicates which vertex is need to be moved
 *
 * Returns:
 * 		increase or decrease in modularity
 *
 */
double compute_score(const struct _spmat *A, const int *k, int M, double *s, int row_number);

/**-------------------------------------------------------------------------------------------------------------------------------
 * Function: modularity_max
 *
 * Purpose: main function of the module, finds optimized division of the group based on initial division s.
 * 			function finds improved partition of the group till no improve is possible
 *
 * Parameters:
 * 		_spmat *A (IN) -- sparse matrix that represent the group of vertices
 * 		*k (IN) -- vector that represents degrees of vertexes in the group
 * 		M (IN) -- sum of all the degrees of vertexes in the group
 * 		*s (IN/OUT) -- vector that represents initial division of the group into two groups,
 * 						function  updates it to the improved partition
 * 		*moved (IN) -- helper vector that indicates for each vertex if it was already moved
 * 		*indicies (IN)-- helper vector for find_improved_partition function
 * Returns:
 * 		increase or decrease in modularity
 *
 */
void modularity_max(const struct _spmat *A, const int *k, int M, double *s, int *moved, int *indicies,int *number_of_1);

#endif
