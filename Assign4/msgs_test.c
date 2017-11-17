#include "msgs.h"
#define SERVER_PORT 0

int replyPortCounter = 1;
semaphore_t *replyPortSem;

void server(){
  int replyPort = 0;
  int data[10];
  int dummyPort = 0;
  printf("Inside Server...\n");
  while(1){
    printf("Server receiving data... \n");
    receive(SERVER_PORT,data,&replyPort);
    for(int i=0; i<10 ; i++){
      data[i] = (data[i] * 4)+1;
    }
    printf("Data after processing in server: ");
    for(int i=0; i<10 ; i++){
      printf(" %d ",data[i]);
    }
    printf("\n");
    printf("Server sending data...\n");
    send(replyPort,data,dummyPort);
    //sleep(1);
  }
}

void client(){
  int tID = currentThreadId();
  int replyPort = 0;
  int dummyPort = 0;
  // Assigning a unique reply port for each client thread
  P(replyPortSem);
    replyPort = replyPortCounter++;
  V(replyPortSem);

  int data[10];
  for(int i=0 ; i<10 ; i++){
    data[i] = tID * (i+1);
  }

  while(1){
      printf("Data before processing in client %d: ",tID);
      for(int i=0; i<10 ; i++){
        printf(" %d ",data[i]);
      }
      printf("\n");
      printf("Client %d sending data...\n",tID);
      send(SERVER_PORT,data,replyPort);
      printf("Client %d receiving data...\n",tID);
      receive(replyPort,data,&dummyPort);

      printf("Data after processing in client %d: ",tID);
      for(int i=0; i<10 ; i++){
        printf(" %d ",data[i]);
      }
      printf("\n");
      //sleep(1);
  }
}

int main(){
  replyPortSem = CreateSem(1);
  createQueue();
  initPort();
  start_thread(server);
  start_thread(client);
  start_thread(client);
  start_thread(client);
  run();
  return 0;
}
