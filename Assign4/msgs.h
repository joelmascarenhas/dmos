#include "sem.h"
#define PORTS 10
#define MESSAGES 10

typedef struct port{
  semaphore_t *full,*empty,*accesslock;
  int messageArr[MESSAGES][10];
  int inputPointer,outputPointer;
}port;

port portObject[PORTS];

// Intializes all the ports with appropriate values
void initPort();

// Used to send message to the intended port
void send(int intendedPort,int messageSent[]);

// Used to receive message for the intended port
void receive(int intendedPort, int messageReceived[]);


void initPort(){
  for (int i=0 ; i < PORTS ; i++){
      portObject[i].empty = CreateSem(MESSAGES);
      portObject[i].full = CreateSem(0);
      portObject[i].accesslock = CreateSem(1);
      portObject[i].inputPointer = 0;
      portObject[i].outputPointer = 0;
  }
}

void send(int intendedPort,int messageSent[]){
  P(portObject[intendedPort].empty);
  P(portObject[intendedPort].accesslock);

    for(int i=0 ; i < 10 ; i++){
      portObject[intendedPort].messageArr[portObject[intendedPort].inputPointer][i] = messageSent[i];
    }

    // portObject[intendedPort].messageArr[portObject[intendedPort].inputPointer] = messageSent;

    portObject[intendedPort].in = (portObject[intendedPort].in+1)%MESSAGES;

  V(portObject[intendedPort].accesslock);
  V(portObject[intendedPort].full);
}


void receive(int intendedPort, int messageReceived[]){
  P(portObject[intendedPort].full);
  P(portObject[intendedPort].accesslock);

    for(int i=0 ; i < 10 ; i++){
      messageReceived[i]  = portObject[intendedPort].messageArr[portObject[intendedPort].outputPointer][i];
    }

    portObject[port].out = (portObject[port].outputPointer+1)%MESSAGES;

  V(portObject[intendedPort].accesslock);
  V(portObject[intendedPort].empty);
}
