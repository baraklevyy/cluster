
/**
 * ----------------------------------------------------------------------------------------------------------------------------
 * ---------------------------------------B--------------------------------------------------------------
 *
 * Purpose: this module collects all of functions that work on matrix B
 *
 * b_mult							- multiplies matrix and vector
 * f_array							- computes and stores sum of each row
 * L1_norm							- computes L1 norm
 * power_iteration			        - finds eigenvector
 * power_iteration_eigval           - finds eigenvalue
 * k_arrangment						- arranges vector k
 * rows_arrangment					- arranges rows of matrix
 * split_mat						- splits matrix into two
 */
#ifndef CLUSTER_IMPROVING_B_H
#define CLUSTER_IMPROVING_B_H
#include <stdio.h>
#include "Common.h"
#include "SparseMatrix.h"


/**--------------------------------------------------------------------------------------------------------------
 * Function: b_mult
 *
 * Purpose: multiply matrix B (represented by matrix A, vector k and M) with vector v
 *
 * Parameters:
 * 		@param A [in] --       sparse matrix that represent the group of vertices
 * 		@param k [in] --       vector that represents degrees of vertices in the initial group
 * 		@param M [in] --       sum of all the degrees of vertices in the initial group
 * 		@param v [in] --       vector that is multiplied with matrix
 * 		@param res [out] --    vector (pre-allocated) that holds the result of multiplication, updated by the function
 * 		@param f [in] --       vector that holds the sum of all the elements in each row
 * 		@param l1_norm [in] -- the 1-norm of the matrix
 *
 *
 */
void b_mult(const struct _spmat *A, const int *k, int M, double *v, double *res, const double *f, double l1_norm);

/**--------------------------------------------------------------------------------------------------------------
 * Function: f_array
 *
 * Purpose: calculate for each row the sum of all the elements in that row and write it into vector f
 *
 * Parameters:
 * 		@param A [in] -- sparse matrix that represent the group of vertices
 * 		@param k [in] -- vector that represents degrees of vertices in the group
 * 		@param M [in] -- sum of all the degrees of vertices in the initial group
 * 		@param f [out] -- vector (pre-allocated) that holds for each row the corresponing sum of all the elements in that row,
 * 						updated by the function
 *
 *
 */
void f_array(const struct _spmat *A, int *const k, int M, double *f, double *reuse_sum);

/**--------------------------------------------------------------------------------------------------------------
 * Function: L1_norm
 *
 * Purpose: calculate the 1-norm of input matrix (represented by matrix A, vector k and M)
 *
 * Parameters:
 * 		@param A [in] --         sparse matrix that represent the group of vertices
 * 		@param k [in] --         vector that represents degrees of vertices in the group
 * 		@param M [in] --         sum of all the degrees of vertices in the initial group
 * 		@param f [in] --         vector that holds for each row sum of all the elements in that row
 *      @param reuse_sum [in] -- the total sum of all relevant k in the current recursion call.
 *
 *@return the 1-norm of the input matrix
 *
 */
double L1_norm(const struct _spmat *A, const int *k, int M, double *f, double reuse_sum);

/**--------------------------------------------------------------------------------------------------------------
 * Function: power_iteration
 *
 * Purpose: find dominant eigenvector of the given matrix
 * Parameters:
 * 		@param A [in] --         sparse matrix that represent the group of vertices
 * 		@param k [in] --         vector that represents degrees of vertices in the group
 * 		@param M [in] --         sum of all the degrees of vertices in the initial group
 * 		@param l1_norm [in] --   the 1-norm of the matrix
 *      @param reuse_sum [in] -- the total sum of all relevant k in the current recursion call
 *      @param alloc [in/out] -- pointer to a helper struct that holds all of arrays used in a program,
 * 							     result of function written into 'alloc ->random_normalized_vector' included in alloc
 *
 */
void power_iteration(const struct _spmat *A, const int *k, int M, allocations *alloc, double L1norm);


/**--------------------------------------------------------------------------------------------------------------
 * Function: power_iteration_eigval
 *
 * Purpose: find dominant eigenvalue based on given matrix and dominant eigenvector of this matrix
 * Parameters:
 * 		@param A [in] --         sparse matrix that represent the group of vertices
 * 		@param k [in] --         vector that represents degrees of vertices in the group
 * 		@param M [in] --         sum of all the degrees of vertices in the initial group
 * 		@param alloc [in/out] -- pointer to a helper struct that holds all of arrays used in the program
 * 		@param l1_norm [in] --   the 1-norm of the matrix
 * 		@param eig_val [out] --  dominant eigenvalue of the matrix
 *
 */
void power_iteration_eigval(const struct _spmat *A, const int *k, int M, allocations *alloc, double L1norm, double *eig_val);


/**--------------------------------------------------------------------------------------------------------------
 * Function: k_arrangment
 *
 * Purpose: arrange the degrees vector, k. The first 'num_of_1' elements will belongs to the corresponding elements which obey to the division.
            The rest obey to the other group divided by s.
 * Parameters:
 * 		@param A [in] --                       sparse matrix that represent the group of vertices
 * 		@param k [in/out] --                   vector that represents degrees of vertices in the group, updated in the function
 * 		@param number_of_1 [in] --             number of 1.0 elements in the vector s after division the group into two
 * 		@param s [in] --                       vector that represents division of the group into two
 * 		@param rows_helper [in] --             helper vector - will holds at the end of that function the new index of each element after the division.
 * 		@param onces_helper [in] --            helper vector - number of elements in each row
 * 		@param relevant_indices_helper [in] -- helper vector - the original indices in the group
 */
void k_arrangment(struct _spmat *A, int *k, int number_of_1, double *s, int *rows_helper, int *onces_helper, int *relevant_indices_helper);

/**--------------------------------------------------------------------------------------------------------------
 * Function: rows_arrangment
 *
 * Purpose: arrange rows of matrix so it matches the groups (and representing matrices) after division.
 *          This function will arrange A within the division: delete irrelevant nodes, change node cols, number of elements in each row.
 * Parameters:
 * 		@param A [in/out] --              sparse matrix that represent the group of vertices.A->Private attribute updated by that function
 * 		@param s [in] --                  vector that represents division of group into two
 * 		@param number_of_1 [in] --        number of 1 in the vector s after division of initial group into two
 * 		@param rows_helper [in] --        helper vector - used in that function to order nodes
 * 		@param outer_array_helper [in] -- helper vector that used as a 'tmp' array in order to sort (A->private)
 */
void rows_arrangment(struct _spmat *A, double *s, int number_of_1, int *rows_helper, node **outer_array_helper);


/**--------------------------------------------------------------------------------------------------------------
 * Function: split_mat
 *
 * Purpose: split the given matrix A into two smaller matrices A1 and A2, each one is independent, contains all relevant attributes
 * Parameters:
 * 		@param A [in] --                           sparse matrix that ha have be splitted
 * 		@param A1 [out] --                         sparse matrix that will represent on of the groups after split, updated by the function
 * 		@param A2 [out] --                         sparse matrix that will represent on of the groups after split, updated by the function
 * 		@param k [in/out] --                       pointer to a vector that represents degrees of vertices in the group
 * 		@param s [in] --                           vector that represents division of group into two
 * 		@param number_of_1 [in] --                 number of 1 in the vector s after division of initial group into two
 * 								                   == number of elements that supposed to be in A1
 * 		@param rows_helper [in/out] --             helper vector
 * 		@param onces_helper [in/out] --            helper array, used in rows_arrangment
 * 		@param outer_array_helper [in/out] --      helper array, used in rows_arrangment
 * 		@param relevant_indices_helper [in/out] -- helper array, used in rows_arrangment
 */
void split_mat(struct _spmat *A, struct _spmat *A1, struct _spmat *A2, int *k, double *s,
               int number_of_1, int *rows_helper, int *onces_helper, node **outer_array_helper, int *relevant_indices_helper);







#endif /*CLUSTER_IMPROVING_B_H*/
