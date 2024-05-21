#include "CALC.h"
#include <string.h>
#include "stdio.h"
#include "stdlib.h"     //for system()
#include "ctype.h"
//Function for operator
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "divi.h"
#include "mod.h"
int pattern_checking(char* s, int length)
{
    // ****** * ******
    int numwp = 0;
    for (int i = 0 ; i < length ; ++i)
    {
        if (s[i] == ' ') ++numwp;
    }

    //more than 2 whitespaces
    if (numwp != 2) return 0;
    else
    {
        //nump == 2
        //whitespace is 2
        if (s[0] == ' ') return 0;

        if (s[length - 1] == ' ') return 0;

        for (int i = 0 ; i < length - 1; ++i)
        {
            if (s[i] == ' ' && s[i+1] == ' ') 
            {   
                return 0;
            }
        }

        return 1;
        /*dddddd op ddddddd*/

        /*ddd    op  ddd*/

        /*dd  opdd*/

        /* 5-3 */

    }
}



int isNumber(char *s, int length)
{
    if (strcmp(s,"ANS") == 0) return 1;

    double check;
    int reading =  sscanf(s,"%lf",&check);

    if (reading == 1)
    {
        //valid string
        return 1;
    }
    else 
    {
        return 0;
    }
    // int countDot = 0;
    // for (int i = 0 ; i < length ; ++i)
    // {
    //     if (s[i] == '.') ++countDot;
    //     if ( ! ( ((s[i] <= '9' && s[i] >= '0') || s[i] == '.') && countDot <= 1)  )
    //     {
    //         return 0;
    //     }
    // }
    // return 1;
}



int syntaxChecking(char *s)
{
    //***** **** ******
    //true format
    char a[100];
    char o[100];
    char b[100];
    sscanf(s,"%s %s %s", a,o,b);
    //printf("%s %s %s\n",a,o,b);

    //printf("%d\n", (int)strlen(o));
    int lengthO = (int)strlen(o);
    if ( lengthO != 1 )
    {
        printf("SYNTAX ERROR\r");
        return 2;
    }

    if ( !isNumber(a,(int)strlen(a)) || !isNumber(b,(int)strlen(b)))
    {
        printf("SYNTAX ERROR\r");
        return 2;
    }

    return 1;
    //ANS * ANS    c
    //6.4 - 23.4   d c d
    //ANS - 45.3   - d
    //45 - ANS     d c
}



void CALC()
{
    double ANS = 0;
    char operator;
    double a = 0;
    double b = 0;
    int int_status = 1;
    //1-working, 2-error, 3--exit

    while ( 1 )
    {
        char s[100];
        int_status = 1;
        printf(">> ");
        fgets(s,100,stdin);
        //printf("%d",strlen(s));
        //omit the new line
        s[strlen(s) - 1] = '\0';
        char check_ans[100];

        
        if (strcmp(s,"EXIT") == 0)
        {
            int_status = 3;
        }
        else if (pattern_checking(s,(int)strlen(s)) == 0)
        {
            printf("SYNTAX ERROR\r");
            int_status = 2;
        }
        //**** ***** ****
        else if (syntaxChecking(s) == 2)
        {
            int_status = 2;
        }
        else if (sscanf(s,"%lf %c %lf", &a, &operator, &b) == 3  )
        {
            //write out a and b
        }
        else if (sscanf(s,"ANS %c %lf", &operator,&b) == 2 )
        {
            //printf("check2\n");
            a = ANS;
        }
        else if (sscanf(s,"%lf %c ANS", &a,&operator) == 2 )
        {
            //printf("check3\n");
            b = ANS;
        }
        else if (sscanf(s,"ANS %c ANS", &operator) == 1)
        {
            a = ANS;
            b = ANS;
        }

        else 
        {
            printf("SYNTAX ERROR\r");
            int_status = 2;
        }
        //printf("a = %lf b = %lf",a,b);

        //we get the patter *number cha number*
        if (int_status == 1)
        {
            switch (operator)
            {
                case '+': ANS = add(a,b);
                break;

                case '-': ANS = sub(a,b);
                break;

                case '*': ANS = mul(a,b);
                break;

                case '/': 
                if (b == 0)
                {
                    printf("MATH ERROR\r");
                    int_status = 2;
                }
                ANS = divi(a,b);
                break;


                case '%':
                int int_a = (int)a;
                int int_b = (int)b;

                if (int_a != a || int_b != b)
                {
                    printf("MATH ERROR\r");
                    int_status = 2;
                }
                //division
                else if (b == 0)
                {
                    printf("MATH ERROR\r");
                    int_status = 2;
                }
                else 
                {
                    ANS = mod(int_a,int_b);
                }
                break;

                default:
                printf("SYNTAX ERROR\r");
                int_status = 2;
                break;
            }
        }

        if (int_status == 2)
        {
            //print the error depends on type
            //printf ("check4\n");
        }
        else if (int_status == 3)
        {
            break;
        }
        else if (int_status == 1)
        {
            //working
            // if ((int)ANS == ANS)
            //     {
            //         //ANS is int value
            //         int int_ANS = (int)ANS;
            //         printf("%d\r",int_ANS);
            //     }
            // else
            // {
                //ANS is double
                printf("%.2lf\r",ANS);
            // }
        }

        char any[10];
        fgets(any,10,stdin);
        system("clear");
    }
}