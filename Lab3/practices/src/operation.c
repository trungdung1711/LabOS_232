#include "opeartion.h"
#include "constant.h"
#include "buffer.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "sem.h"


void * producer( void * arg) 
{
    int* t_id = (int*)arg ;
    for (int i = 0 ; i < LOOPS; i++) 
    {
        sem_wait(&empty);
        put ( i ) ; 
        printf("Producer  %d   put   data  %d\n" , *t_id , i ) ;
        sem_post(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}




void * consumer ( void * arg ) 
{
    int tmp = 0 ;
    int* t_id = (int*) arg ;
    while ( tmp != - 1 ) 
    {
        sem_wait(&full);
        tmp = get();
        printf("Consumer  %d   get   data  %d\n" , *t_id , tmp) ;
        sem_post(&empty);
        sleep(2);
    }
    pthread_exit(NULL);
}



void put ( int value ) 
{
    buffer[fill] = value ;
    fill = (fill + 1) % BUF_SIZE ;
}




int get() 
{
    int tmp = buffer[use];
    buffer[use] = -1 ; 
    use = (use + 1) % BUF_SIZE ; 
    return tmp ;
}