#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include<unistd.h>
#include "q.h"

/* Function initializes the context for function thread and adds to ready queue */
void start_thread(void (*function)(void)){
    char *stack = (char *) malloc(8192*sizeof(char));
    struct TCB_t *tcb = (struct TCB_t *) malloc(sizeof(struct TCB_t));
    init_TCB(tcb, function, (void *) stack, 8192);
    AddQ(Q,tcb);

}

/* Swaps the current context with that of head of queue for context_switch */
void run() {
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(Q->head->context));

}

/* Current thread swaps context with that of last element in queue */
void yield(){
    struct TCB_t *temp;
    RotateQ(Q);
    swapcontext(&(Q->head->prev->context), &(Q->head->context));

}

