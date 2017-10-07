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
  TCB_t* temp = q->prev;
  if(q==NULL){
    q = ele;
  }else{
    temp->next = ele;
    ele->prev = temp;
    ele->next = q;
    q->prev = ele;
  }
}

TCB_t* DelQ(TCB_t* q){
  TCB_t temp;
  if(q == NULL){
    return NULL;
  }else{
    temp = q;
    q = q-> next;
    if(q==temp){
      q = NULL;
      free(temp);
      return NULL;
    }else{
      temp->prev->next = q;
      q->prev = temp->prev;
      free(temp);
    }
  }
  return temp;
}
