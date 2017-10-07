#ifndef __q_H__
#define __q_H__

#include "TCB.h"

TCB_t*  head;
TCB_t*  newQueue();
void    AddQueue(TCB_t* q,TCB_t* ele);
TCB_t*  DelQueue(TCB_t* q)
TCB_t*  newItem();

TCB_t* newQueue(){
  head = newItem();
  return head;
}

TCB_t* newItem(){
  TCB_t* q;
  q->prev = null;
  q->next = null;
  return q;
}

void AddQueue(TCB_t* q,TCB_t* ele){
  InitQ(ele);
  TCB_t* temp = q->prev;
  if(q==NULL){
    q = ele;
  }else{
    if(temp==NULL){
      q->next = ele;
      q->prev = ele;
      ele->next = q;
      ele->prev = q;
    }else{
      temp->next = ele;
      ele->prev = temp;
      ele->next = q;
      q->prev = ele;
    }
  }
}

TCB_t* DelQueue(TCB_t* q){
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
