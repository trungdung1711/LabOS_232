#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



struct Range 
{
    long begin;
    long end;
};


void* routine(void* para)
{
    //allocate the memory for saving
    long* sum = malloc(sizeof(long));
    *sum = 0;

    struct Range* range = (struct Range*)(para);
    for (long i = range->begin ; i <= range->end ; ++i)
    {
        *sum += i;
    }
    return (void*)sum;
}



long sum_multi_thread(long n, long number_thread)
{
    long num_each_thread = n/number_thread;
    long num_last_thread = (n % number_thread == 0) ? (num_each_thread) : (num_each_thread + n % number_thread);

    struct Range range[number_thread];

    long begin = 1;
    for (int i = 0 ; i < number_thread ; ++i)
    {
        range[i].begin = begin;
        long temp = (i == number_thread - 1)?(num_last_thread - 1):(num_each_thread - 1);
        range[i].end = range[i].begin + temp ;
        begin = begin + num_each_thread;
    }

    long *result[number_thread];

    pthread_t tid[number_thread];
    //initialise the attribute of the threads
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for (int i = 0 ; i < number_thread; ++i)
    {
        pthread_create(&tid[i],&attr,&routine,&range[i]);
    }
    long sum = 0;

    for (int i = 0 ; i < number_thread ; ++i)
    {
        //the return value would be the pointer to long
        pthread_join(tid[i],(void**)&result[i]);
        sum+= *result[i];
    }
    for (int i = 0 ; i < number_thread ; ++i)
    {
        free(result[i]);
    }
    return sum;
}



int main(int argc, char** argv)
{
    //printf("_____MULTI_THREAD_____\n");
    if (argc != 3)
    {
        printf("False argument\n");
        return -1;
    }
    long number = atoi(argv[2]);
    long number_thread = atoi(argv[1]);
    if (number_thread == 0)
    {
        printf("Number of threads can not be 0\n");
        return -1;
    }
    printf("Sum of numbers from 1 to %li using %li threads: %li\n",number,number_thread,sum_multi_thread(number,number_thread));
    //printf("_____MULTI_THREAD_____\n");
}