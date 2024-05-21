#include <stdlib.h>

#include "util.h"
#include "constant.h"
#include "global.h"



int isInsideCircle(double x, double y)
{
    return (x*x + y*y <= RSQUARED );
}



void* routine(void* arg)
{
    unsigned long long int C_count = 0;

    unsigned long t_id = *(unsigned long*)arg;
    srand(t_id);

    unsigned long long int POINT = POINT_NUMBER/THREAD_NUMBER;

    for (unsigned long long int i = 0 ; i < POINT ; ++i)
    {
        double x = (MAX-MIN)*(double)rand()/RAND_MAX + MIN;
        double y = (MAX-MIN)*(double)rand()/RAND_MAX + MIN;

        if (isInsideCircle(x,y))
        {
            ++C_count;
        }
    }
    pthread_mutex_lock(&mutex);
    circle_point_count += C_count;
    pthread_mutex_unlock(&mutex);
}