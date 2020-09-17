/**
 * ----------------------------------------------------------------------------------------------------------------------------
 * ---------------------------------------COMMON--------------------------------------------------------------
 *
 * Purpose: this module is collect general structs and function used in the whole project
 * */
#ifndef CLUSTER_IMPROVING_COMMON_H
#define CLUSTER_IMPROVING_COMMON_H
#define LOWEST_VALUE -DBL_MAX
#define IS_POSITIVE(X) ((X) > 0.00001)
#define IS_POSITIVE_WEAK(X) ((X) > 0.0001)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#include <float.h>
#include "SparseMatrix.h"

/**
 *  _Status:
 * 		 enum used to classify the differences between errors
 */
typedef enum _Status {
    INVALID_STATUS_CODE = -1,
    SUCCESS_STATUS_CODE = 0,
    MALLOC_FAILED_CODE,
    NULL_ARGUMENT_CODE,
    FOPEN_FAILED_CODE,
    FREAD_FAILED_CODE,
    FWRITE_FAILED_CODE,
    INVALID_ARGUMENTS_CODE,
    ZERO_DIVISION_CODE,
    GROUP_NOT_DIVISIBLE_CODE,
    REACHED_MAX_NUMBER_OF_ITERATION,
    NEGATIVE_EIGEN_VALUE,
    ZERO_NUMBER_OF_EDGES,
    /*COUNTER FOR ERRORS*/
    STATUS_CODE_COUNT
}Status;

/**--------------------------------------------------------------------------------------------------------------
 * Function: get_error_message
 *
 * Purpose: get error message according status and print it out
 *
 * Parameters:
 * 			@param result [in] -- status that represent which error occurred
 * */
void get_error_message(Status result);


/**
 * _allocations:
 * 			struct used to collect pointers of the dynamic allocations.
 */
typedef struct _allocations {
    int *k;
    double *s;
    double *f;
    double *random_normalized_vector;
    int *onces_helper;
    int *rows_helper;
    int *relevant_indices_helper;
    int *output_array;
    node **outer_array_helper;
} allocations;

/**
 * _pointers:
 * 			Type used to collect and hold main pointers of the program(those on allocation will change due to the recursion).
 */
typedef struct _pointers {
    int *k;
    double *s;
    double *f;
    double *random_normalized_vector;
    int *onces_helper;
    int *rows_helper;
    int *relevant_indices_helper;
    int *output_array;
    node **outer_array_helper;
    /*spmat first pointers*/
    int *A_onces_num;
    int *A_relevant_indices;
    node **A_outer_array_helper;
    spmat *A;
} pointers;

/**--------------------------------------------------------------------------------------------------------------
 * Function: initialized_pointer
 *
 * Purpose: initializes all the pointers
 *
 * Parameters:
 * 			@param alloc [in] -- struct consist allocated dynamic memory
 * 			@param A [in] --     sparse matrix that represents the network
 *
 * @return _pointers with initialized fields
 * */
pointers* initialized_pointer(allocations *alloc, spmat *A);

/**--------------------------------------------------------------------------------------------------------------
 * Function: alloc_allocations
 *
 * Purpose: allocates all the dynamic memory needed for program
 *
 * Parameters:
 * 			@param n [in] -- size of input network (number of elements in network)
 *
 * @return _allocations = struct that holds all of allocated memory
 * */
allocations* alloc_allocations(int n);

/**--------------------------------------------------------------------------------------------------------------
 * Function: free_allocations
 *
 * Purpose: free all of the fields of given pointer to _pointers
 *
 * Parameters:
 * 			@param main_pointer [in] -- _pointer that needs to be freed
 *
 *
 * */
void free_allocations(pointers *main_pointer);

/**--------------------------------------------------------------------------------------------------------------
 * Function: outer_array_free
 *
 * Purpose: free outer_array of the matrix. In this stage the nodes have to be free'd.
 *
 * Parameters:
 * 			@param outer_array [in] -- pointer to outer array of matrix A (initial)
 * 			@param n [in] -- size of input network (number of elements in network)
 *
 * */
void outer_array_free(node** outer_array, int size);

#endif /*CLUSTER_IMPROVING_COMMON_H*/
