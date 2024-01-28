#ifndef RNG_H_
#define RNG_H_
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265359

int16_t norm_rand(int16_t mean, int16_t std, int16_t min, int16_t max)
{
    double u = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    double v = ((double)rand() / RAND_MAX) * 2.0 - 1.0;

    double tmp = sqrt(-2.0 * log(fabs(u))) * sin(2.0 * PI * v);
    int16_t ret = mean + (int16_t)(tmp * std);

    return (ret < min ? min : (ret > max ? max : ret));
}

#endif
