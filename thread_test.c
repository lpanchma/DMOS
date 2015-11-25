/* DMOS Assignment 1 submission */
/* Leena Panchmatia ASU ID : 1208107975 */
/* Jaideep Gour     ASU ID : 1208721926*/

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include<unistd.h>
#include "threads.h"

/* Test functions which are threads */
void function1(){
    while(1){
        sleep(1);
        printf("Function 1\n");
        yield(Q);
        printf("Part 2\n");
    }

}

void function2(){
    while(1){
        sleep(1);
        printf("Function 2\n");
        yield(Q);
    }

}

void function3(){
    while(1){
        sleep(1);
        printf("Function 3\n");
        yield(Q);
    }

}

void function4(){
    while(1){
        sleep(1);
        printf("Function 4\n");
        yield(Q);
    }

}

/* Main function to test */
int main()
{
 Q = InitQ(Q);
 start_thread(function1);
// start_thread(function2);
// start_thread(function3);
// start_thread(function4);
 run();
}
 
