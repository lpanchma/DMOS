#include<stdio.h>
#include<stdlib.h>
#include "sem.h"

/* Port number for servers statically assigned */
#define SERVER_PORT0 99
#define SERVER_PORT1 98

/* Message data structure */
struct message{
    int message_arr[10];
};

/* Port data structure */
/* Strategy 2 : per port semaphore for synchronization and mutex */
struct port{
    int index;
    struct message *port_message;
    int head;
    int tail;
    struct Semaphore_t producer, consumer;
    struct Semaphore_t mutex;   
};

/* Set of ports */
struct port port_set[100];

/* Function for initializing an individual port with port_index and size */
void create_port(int port_size, int ind){
    port_set[ind].port_message = (struct message *) malloc (port_size * sizeof(struct message));
    port_set[ind].index = ind;
    port_set[ind].head = 0;
    port_set[ind].tail = 0;
    CreateSem(&(port_set[ind].mutex), 1);
    CreateSem(&(port_set[ind].producer), port_size);
    CreateSem(&(port_set[ind].consumer), 0);  
}

/* Message 
   Client : serverid + clientid + 0..
   Server : sending clientid + serverid + clientid.. 
*/
struct message* create_message(int dest_index, int src_index){
    struct message *temp;
    int i;
    int msg;
    temp = (struct message*) malloc(sizeof(struct message));
    temp->message_arr[0] = dest_index;
    temp->message_arr[1] = src_index;
    msg = (dest_index == SERVER_PORT0 || dest_index == SERVER_PORT1) ? 0 : dest_index;
    for(i = 2; i < 10; i++){
        temp->message_arr[i] = msg;
    }
    return temp;
}

/* 
   Function that prints received message for clients
   destination id == client id
   source id == server id
   message
*/
void print_message(struct message *rec_message){
    if(rec_message == NULL){
       printf("Message Empty");
       return;
    }
    int i;
    printf("--------------------------------------------------------------------------------\n");
    printf("destination : %d\n", rec_message->message_arr[0]);
    printf("source : %d\n", rec_message->message_arr[1]);
    printf("message");
    for(i = 2; i < 10; i++){
        printf("%d ", rec_message->message_arr[i]);

    }
    printf("\n------------------------------------------------------------------------------\n");
    return;
}

/* Storing message in server's buffer and blockingg if full */
void send(int dest_index, int src_index){
    struct message *my_msg = create_message(dest_index, src_index);
    P(&(port_set[dest_index].producer));
    P(&(port_set[dest_index].mutex)); 
    port_set[dest_index].port_message[port_set[dest_index].tail] = *my_msg;
    port_set[dest_index].tail++;  
    V(&(port_set[dest_index].mutex));
    V(&(port_set[dest_index].consumer));
}

/* frunction to get message from one's buffer */
struct message* receive(int my_index){
    struct message *my_msg;
    P(&port_set[my_index].consumer);
    P(&port_set[my_index].mutex);
    my_msg =&(port_set[my_index].port_message[port_set[my_index].head]);
    port_set[my_index].head++;
    V(&port_set[my_index].mutex);
    V(&port_set[my_index].producer);
    return my_msg;
}

