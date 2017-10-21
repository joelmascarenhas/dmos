#include "TCB.h"
#define LOCKED 1
#define UNLOCKED 0
struct Semaphore_t{
  int locker;
  TCB_t *semQ;
  int count;
}Semaphore_t;

// mallocs a semaphore structure, initializes it to the InitValue and returns
// the pointer to the semaphore.
Semaphore_t CreateSem(int InputValue);
// takes a pointer to a semaphore and performs P, i.e. decrements the semaphore,
// and if the value is less than zero then blocks the thread in the queue
// associated with the semaphore.
void P(Sempahore_t *sem);
// increments the semaphore, and if the value is 0 or negative,
// then takes a PCB out of the semaphore queue and puts it into the ReadyQ.
// Note: The V routine also "yields" to the next runnable thread.
void V(Semaphore_t *sem);

Semaphore_t CreateSem(int InputValue){
    Semaphore_t *tempSem = (Semaphore_t *) (malloc(sizeof(Semaphore_t*)));
    tempSem->semQ = (TCB_t*) (malloc(sizeof(TCB_t*)));
    tempSem->count = InputValue;
    tempSem->locker = 1;
    return tempSem;
}

void P(Sempahore_t* sem){
  sem->count--;
  if(sem->count<0){
    AddQueue(sem->semQ,Curr_Thread);
    Prev_Thread = Curr_Thread;
    Curr_Thread = DelQueue(ReadyQ);
    swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
  }
}

void V(Sempahore_t* sem){
  sem->count++;
  if(sem->count<=0){
    AddQueue(ReadyQ,DelQueue(sem->semQ));
  }
  yield();
}

void lock(Semaphore_t* sem){
  while(sem->locker==LOCKED);
  sem->locker = LOCKED;
}

void unlock(Sempahore_t* sem){
  sem->locker = UNLOCKED;
}
