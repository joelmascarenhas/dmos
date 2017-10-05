#ifndef __q_H__
#define __q_H__

#include "TCB.h"

void InitQ  (TCB_t* q);
void AddQ   (TCB_t* q,TCB_t* ele);
void DelQ   (TCB_t* q);
void PrintQ (TCB_t* q);

void InitQ(TCB_t* q){
  q->prev = null;
  q->next = null;
}

void AddQ(TCB_t* q,TCB_t* ele){
  InitQ(ele);
  TCB_t* runner = q;
  if(q==NULL){
    q = ele;
  }else{
    while(runner->next!=NULL){
      runner = runner->next;
    }
    runner->next = ele;
    ele->prev = runner;
  }
}
