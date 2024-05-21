#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NUM_MOVIES 1682
#define SEM_NAME "sem"
#define MOVIE1 "./movie-100k_1.txt"
#define MOVIE2 "./movie-100k_2.txt"


typedef struct 
{
    long m_count;
    double m_total_rate;
} Movie;



int readMovie(Movie* movie, sem_t* sem, char* fileName)
{
    FILE* file;
    file = fopen(fileName,"r");
    if (file == NULL)
    {
        printf("Can not open the file\n");
        return -1;
    }
    char line[256];
    while (fgets(line,sizeof(line),file))
    {
        long movie_id;
        double rate;
        sscanf(line,"%*d\t%ld\t%lf\t%*d",&movie_id,&rate);

        sem_wait(sem);
        movie[movie_id].m_count++;
        movie[movie_id].m_total_rate+=rate;
        sem_post(sem);
    }    
}



int main()
{
    //0. Safely generate the key_t value for accessing this shared memory
    key_t myKey = ftok("/home",10);
    key_t myKagi = ftok("/proc",10);
    //1. Get a shared memory segment, for read and write and if they don't exist -> create one
    int shmid1 = shmget(myKey,sizeof(Movie)*1683, 0666|IPC_CREAT);
    int shmid2 = shmget(myKagi,(sizeof(int))*2,0666|IPC_CREAT);

    int* check = (int*)shmat(shmid2,NULL,0);
    check[0] = check[1] = 0;

    sem_t* sem = sem_open(SEM_NAME,O_CREAT,0666,1);

    Movie* movie = shmat(shmid1,NULL,0);
    
    for (long i = 1 ; i <= NUM_MOVIES ; ++i)
    {
        movie[i].m_count = 0;
        movie[i].m_total_rate = 0;
    }
    //MUTEX LOCK for mutual exclusion
    //pthread_mutex_t* mutex = shmat(shmid2,NULL,0);
    //pthread_mutex_init(mutex,NULL);

    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0)
    {
        //open file 1
        Movie* movie = shmat(shmid1,NULL,0); 
        //pthread_mutex_t* mutex = shmat(shmid2,NULL,0);
        sem_t* sem = sem_open(SEM_NAME,0);
        readMovie(movie,sem,MOVIE1);

        int* check = (int*)shmat(shmid2,NULL,0);
        check[0] = 1;
        exit(1);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            Movie* movie = shmat(shmid1,NULL,0); 
            sem_t* sem = sem_open(SEM_NAME,0); 

            readMovie(movie,sem,MOVIE2);

            int* check = (int*)shmat(shmid2,NULL,0);
            check[1] = 1;
            exit(1);      
        }
        else if (pid2 > 0)
        {
            wait(NULL);
            //busy waiting
            while (check[0] == 0 || check[1] == 0);
            long sum_count = 0;
            for (long i = 1 ; i <= NUM_MOVIES ; ++i)
            {
                sum_count+= movie[i].m_count;
                printf("ID\t%ld\tCOUNT\t%ld\tAVERAGE\t%lf\n",i,movie[i].m_count,movie[i].m_total_rate/movie[i].m_count);
            }
            printf("%ld\n",sum_count);
            shmctl(shmid1,IPC_RMID,NULL);
            shmctl(shmid2,IPC_RMID,NULL);
        }
        else
        {
            perror("Fail to clone a new process\n");
        }
    }
    else 
    {
        //false
        perror("Fail to clone a new process\n");
    }
}