#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Common.h"
#include "vector.h"
void vec_normalize(double * v, int size){
    double val, *for_limit, *v_ptr, sum;
    for_limit = (v + size);
    sum = 0.0;
    for(v_ptr = v; v_ptr < for_limit; v_ptr++){
        val = *(v_ptr);
        sum += (val * val);
    }
    sum = sqrt(sum);
    if (!IS_POSITIVE(sum))
        return;
    for (v_ptr = v; v_ptr < for_limit; v_ptr++)
        *(v_ptr) /= sum;
}
int diff_below_epsilon(double *v1, double *v2, int size, int flag) {
    int i;
    if(flag == 0) {
        for (i = 0; i < size; i++) {
            if (IS_POSITIVE(fabs(*(v1 + i) - *(v2 + i)))) {
                return 0;
            }
        }
    }
    else{
        for (i = 0; i < size; i++){
            if ( IS_POSITIVE_WEAK(fabs(*(v1 + i) - *(v2 + i))) ){
                return 0;
            }

        }

    }
    return 1;
}
double vec_dot(const double *v1, const double *v2, int size) {
    int i;
    double res;
    res = 0.0;
    for (i = 0; i < size; i++)
        res += (*(v1 + i)) * (*(v2 + i));
    return res;
}
void generate_random_normalized_vector(double *v,  int size) {
    int i;
    /* seed random */
    srand((unsigned int) time(0));
    for (i = 0; i < size; i++)
        *(v + i) = (double)rand() / (double)RAND_MAX;
    vec_normalize(v, size);
}

