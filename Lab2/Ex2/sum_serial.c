#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
long sum_serial(long number)
{
    long sum = 0;
    for (long i = 1 ; i <= number ; ++i)
    {
        sum += i;
    }
    return sum;
}



int main(int argc, char** argv)
{
    //printf("_____SERIAL_____\n");
    if (argc != 2)
    {
        printf("False argument\n");
        return -1;
    }
    long number = atoi(argv[1]);
    //printf("%li",number);
    printf("Sum of numbers from 1 to %li: %li\n",number,sum_serial(number));
    //printf("_____SERIAL_____\n");
}