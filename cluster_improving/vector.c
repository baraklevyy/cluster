#include <math.h>
#include "Common.h"
#include "vector.h"
#include <stdio.h>

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

double vec_dot_int(const int *v1, const double *v2, int size) {
    double res = 0;
    int i;

    for (i = 0; i < size; i++)
        res += (double)*(v1 + i) * *(v2 + i);

    return res;
}

void generate_random_normalize_vector(double *v, int size) {

	for (i = 0; i < n; i++)
		*(v + i) = (double)rand() / (double)RAND_MAX;
	vec_normalize(v, n);
}
