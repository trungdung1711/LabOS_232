#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "constant.h"
#include "util.h"


unsigned long long int circle_point_count = 0;
pthread_mutex_t mutex;


int main()
{
    pthread_mutex_init(&mutex,NULL);

    pthread_t t_id[THREAD_NUMBER];
    for (int i = 0 ; i < THREAD_NUMBER ; ++i)
    {
        pthread_create(&t_id[i],NULL,&routine,(void*)&t_id[i]);
    }
    
    for (int i = 0 ; i < THREAD_NUMBER ; ++i)
    {
        pthread_join(t_id[i],NULL);
    }
    printf("The approximation of pi is: %lf\n",((double)circle_point_count/POINT_NUMBER)*4);

    pthread_mutex_destroy(&mutex);
}