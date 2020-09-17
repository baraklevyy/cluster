/**
 * ----------------------------------------------------------------------------------------------------------------------------
 * ---------------------------------------UTILITY--------------------------------------------------------------
 *
 * Purpose: this module contains number of helper functions
 *
 * graph_loading		- loads input into variables
 * extract_matrix_size  - loads matrix size into variable
 *
 *
 *
 */
#ifndef CLUSTER_IMPROVING_UTILITY_H
#define CLUSTER_IMPROVING_UTILITY_H

/**--------------------------------------------------------------------------------------------------------------
 * Function: graph_loading
 *
 * Purpose: loads into relevant variables input data
 *
 * Parameters:
 * 			@param argc [in] --           number of command-line input
 * 			@param argv [in] --           command-line input
 * 			@param A [out] --             sparse matrix that represents the input network, updated in the function
 * 			@param k [out] --             vector that represents degrees of vertexes in the group, updated in the function
 * 			@param M [out] --             sum of all the degrees of vertexes in the group, updated in the function
 * 			@param current_vector [in] -- helper vector, each iteration holds one row of the matrix
 * @return
 * 			INVALID_ARGUMENTS_CODE  - if there were invalid number of arguments to the program
 * 			FOPEN_FAILED_CODE 		- if function failed to open input file
 * 			FREAD_FAILED_CODE       - if function couldn't read the input file
 * 			SUCCESS_STATUS_CODE     - if function succeeded to load input into relevant variables
 */
Status graph_loading(int argc, char** argv, struct _spmat *A, int *k, int *M, int *current_vector);

/**--------------------------------------------------------------------------------------------------------------
 * Function: extract_matrix_size
 *
 * Purpose: extract number of nodes in the input network, check that input is in the right format
 *
 * Parameters:
 * 			@param argc [in] -- number of inputs of the program
 * 			@param argv [in] -- array with inputs of the program
 * 			@param n [out] --   number of nodes and size of initial matrix, updated by the function
 *
 * @return
 * 			INVALID_ARGUMENTS_CODE  - if there were invalid number of arguments
 * 			FOPEN_FAILED_CODE 		- if function failed to open input file
 * 			FREAD_FAILED_CODE       - if function couldn't read the input file
 * 			SUCCESS_STATUS_CODE     - if function succeeded to load input into relevant variables
 */
Status extract_matrix_size(int argc, char** argv, int *n);



#endif /*CLUSTER_IMPROVING_UTILITY_H*/
