#include "threads.h"

//Struct for semaphore including counter and pointer to wait queue
struct Semaphore_t {
    int value;
    struct queue *sem_Q;
};

//Initialization : 1) Initialize with a given value
//                 2) Intialize the wait queue
struct Semaphore_t* CreateSem(struct Semaphore_t *my_sem, int InputValue){
    my_sem->value = InputValue;
    my_sem->sem_Q = InitQ(my_sem->sem_Q);
    return my_sem;
}

//P(sem)
//No need for atomicity as threads are non-preemptable
//Blocked processes from ready queue and placed on sem wait queue
void P(struct Semaphore_t *sem){
    struct TCB_t *temp;

    sem->value--;
    if(sem->value < 0){
       temp = DelQ(Q);
       AddQ(sem->sem_Q, temp);
       swapcontext(&(temp->context), &(Q->head->context));
    } 

}

//V(sem)
//No need for atomicity as threads are non-preemptable
//If any blocked process, it is removed from wait queue and placed into ready queue
void V(struct Semaphore_t *sem){
    struct TCB_t *temp;

    sem->value++;
    if(sem->value <= 0){
       temp = DelQ(sem->sem_Q);
       AddQ(Q, temp);
    }
    yield(Q);
}
