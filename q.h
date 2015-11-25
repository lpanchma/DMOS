/* Functions which implement a circular queue from doubly linked list */

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include<unistd.h>
#include"TCB.h"

/* struct representing a queue */
struct queue { 
   struct TCB_t *head;
};

struct queue *Q;

/* Function to check if queue is empty */
int isEmpty(struct queue *Q) {
   if(Q->head == NULL)
      return 1;
   return 0;
}

/* Adds an element to the queue to the front where
   a pointer to the element is provided */
void AddQ(struct queue *Q, struct TCB_t *item) {
   if(isEmpty(Q)) {
       Q->head = item;
       Q->head->next = Q->head;
       Q->head->prev = Q->head;
   } else {
       item->prev = Q->head->prev;
       item->next = Q->head;
       Q->head->prev->next = item; 
       Q->head->prev = item;
   }
}

/* Returns pointer to the last element in the queue
   and deletes it from the queue */
struct TCB_t* DelQ(struct queue *Q) {
   struct TCB_t *temp;
   if(isEmpty(Q))
      return NULL;
   else {
      temp = Q->head;
      if(Q->head->next == Q->head)
         Q->head = NULL;
      else {
      Q->head = Q->head->next;
      Q->head->prev = temp->prev;
      temp->prev->next = Q->head;
      }
      return temp;
   }
}

/* Initializes the queue with head as NULL */
struct queue* InitQ(struct queue *Q) {
   Q = (struct queue *)malloc(sizeof(struct queue));
   Q->head = NULL;
   return Q;
}

/* Deletes element from end of queue and puts
   at the front */
void RotateQ(struct queue *Q) {
   struct TCB_t *temp;
   temp = DelQ(Q);
   AddQ(Q, temp);
}

