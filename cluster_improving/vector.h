/**
 * ----------------------------------------------------------------------------------------------------------------------------
 * ---------------------------------------VECTOR--------------------------------------------------------------
 *
 * Purpose: this module bundle the vector operations
 *
 * vec_normalize					 - normalizes vector
 * diff_below_epsilon				 - checks if difference is small
 * vec_dot							 - multiples two vectors
 * generate_random_normalized_vector - generates random vector
 */
#ifndef CLUSTER_IMPROVING_VECTOR_H
#define CLUSTER_IMPROVING_VECTOR_H

/**--------------------------------------------------------------------------------------------------------------
 * Function: vec_normalize
 *
 * Purpose: normalize a given vector
 *
 * Parameters:
 * 			@param v [in/out] -- input vector
 * 			@param size [in] --  corresponding size
 */
void vec_normalize(double *v, int size);

/**--------------------------------------------------------------------------------------------------------------
 * Function: diff_below_epsilon
 *
 * Purpose: check if difference between two vectors is small enough
 *
 * Parameters:
 * 			@param v1 [in] --   first vector
 * 			@param v2 [in] --   second vector
 * 			@param size [in] -- size of vectors
 * @return
 * 			0 - if difference isn't small enough
 * 			1 - if difference is small enough
 */
int diff_below_epsilon(double *v1, double *v2, int size, int flag);

/**--------------------------------------------------------------------------------------------------------------
 * Function: vec_dot
 *
 * Purpose: multiplies two vectors
 *
 * Parameters:
 * 			@param v1 [in] --   first vector
 * 			@param v2 [in] --   second vector
 * 			@param size [in] -- size of vectors
 * @return result of a multiplication
 */
double vec_dot(const double *v1, const double *v2, int size);

/**--------------------------------------------------------------------------------------------------------------
 * Function: generate_random_normalized_vector
 *
 * Purpose: generate random vector
 *
 * Parameters:
 * 			@param v [out] --   the random values load into this pre-allocated vector
 * 			@param size [in] -- size of vector
 */
void generate_random_normalized_vector(double *v,  int size);
#endif /*CLUSTER_IMPROVING_VECTOR_H*/
