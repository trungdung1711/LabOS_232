#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>

#define STACK_SIZE 8192

int do_something(void *arg)
{
    int i;
    for(i = 0; i < 10; i++){
        printf("Child says: %d\n", i);
        sleep(1);
    }
    return 0;
}

int main() 
{
    void *stack = malloc(STACK_SIZE);
    if(!stack) 
    {
        printf("Unable to allocate memory for stack.\n");
        exit(1);
    }

    printf("Creating child thread\n");
    if(clone(do_something, stack + STACK_SIZE, SIGCHLD|CLONE_VM|CLONE_VFORK, NULL) == -1) 
    {
        printf("Error creating child thread.\n");
        exit(1);
    }

    int i;
    for(i = 0; i < 10; i++)
    {
        printf("Parent says: %d\n", i);
        sleep(1);
    }

    free(stack);
    return 0;
}
