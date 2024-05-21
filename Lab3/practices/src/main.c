#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "opeartion.h"
#include "constant.h"
#include "buffer.h"
#include "sem.h"

int fill = 0 ;
int use = 0 ;
int buffer[BUF_SIZE] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

sem_t full;
sem_t empty;



int main ( int argc , char ** argv ) 
{
    sem_init(&empty,0,BUF_SIZE);
    sem_init(&full,0,0);

    int i , j ;
    int t_id[THREADS];
    pthread_t producers[THREADS];
    pthread_t consumers[THREADS];

    for ( i = 0 ; i < THREADS; i++) 
    {
        t_id[i] = i ;
        pthread_create( &producers[i] , NULL, producer , (void *)&t_id[i]);
        pthread_create( &consumers[i] , NULL, consumer , ( void *)&t_id[i]);
    }

    for ( i = 0 ; i < THREADS; i++) 
    {
        pthread_join( producers[i], NULL );
        pthread_join( consumers[i] , NULL ) ;
    }

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0 ;
}
