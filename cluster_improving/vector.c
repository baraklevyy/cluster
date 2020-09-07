#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Common.h"
#include "vector.h"

void vec_normalize(double * v, int size)
{
    double sum = 0.0;
    double val;
    int i;

    for (i = 0; i < size; i++) {
        val = *(v + i);
        sum += (val * val);
    }

    sum = sqrt(sum);
    if (!IS_POSITIVE(sum))
        return;

    for (i = 0; i < size; i++)
        *(v + i) /= sum;
}

int diff_below_epsilon(double *v1, double *v2, int size) {
    int i;

    for (i = 0; i < size; i++)
        if ( IS_POSITIVE(fabs(*(v1 + i) - *(v2 + i))) ){
            /*
            printf("%f", fabs(*(v1 + i) - *(v2 + i)));
            fflush(stdout);
             */
            return 0;
        }


    return 1;
}

double vec_dot(const double *v1, const double *v2, int size) {
    double res = 0.0;
    int i;

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

