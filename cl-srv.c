/*
 Assignment 4 CSE 531
 Leena Panchmatia ASUID : 1208107975
 Jaideep Gour     ASUID : 1208721926
*/

#include<stdlib.h>
#include<stdio.h>
#include "msgs.h"

#define STRING_SIZE 10

struct server_table_entry {
    char string[STRING_SIZE];
};

/* Server function
   Blocks if no message for it
   Removes first received message
   Sends reply to corresponding client
*/
void serverport0(){
     struct server_table_entry[10];
     struct message *rec_message;
     while(1) {
        printf("\nServer Port [%d] : Listening\n", SERVER_PORT0); 
        rec_message = receive(SERVER_PORT0);
        printf("\nServer Port [%d] : Sending Message to %d\n", SERVER_PORT0, rec_message->message_arr[1]);
        send(rec_message->message_arr[1], SERVER_PORT0);   
     }
}

/* Client function
   Randomly chooses a port
   Randomly chooses an operation
   Sends message from that port
   Waits for reply on that port
   Recieves the messae and prints it 
   Then chooses another port
*/
void client_prod(){
     int my_port;
     int server_operation = rand() % 3; 
     struct message *rec_message;

     while(1) {
        my_port = rand() % 98;
        printf("\nClient Port [%d] : Sending Message to %d\n", my_port, server_port);

     	switch(server_opeation) {
            case ADD:
             	break;
            case DEL:
             	break;
            case MOD:
              	break;
            default:
                printf(stderr,"No permitted operation specified");
        }
        send(server_port, my_port);
        rec_message = receive(my_port);
        printf("\nClient Port [%d] : Recieving Message from %d\n", my_port, server_port);
        print_message(rec_message);
        sleep(1);
     } 
}

void client_cons(){
     int my_port;
     struct message *rec_message;

     while(1) {
        my_port = rand() % 98;
        printf("\nClient Port [%d] : Sending Message to %d\n", my_port, server_port);
        send(server_port, my_port);
        rec_message = receive(my_port);
        printf("\nClient Port [%d] : Recieving Message from %d\n", my_port, server_port);
        print_message(rec_message);
        sleep(1);
     } 
}


int main()
{
    Q = InitQ(Q);                            //Modification to initialize the run queue
    int i;
    for(i = 0; i < 100; i++)
        create_port(10, i);                  // Initializes all the ports
    start_thread(serverport0);               // Only argument passed to thead_start is function name
    start_thread(serverport1); 
    start_thread(client);
    start_thread(client);
    start_thread(client);
    start_thread(client);
    run();                                  //Since run function is non-terminating we do not require an infinite loop in main
}
