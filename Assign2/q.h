#ifndef __q_H__
#define __q_H__

#include "TCB.h"

void InitQ  (TCB_t** q);
void AddQ   (TCB_t** q,TCB_t** ele);
void DelQ (TCB_t** q);
void PrintQ(TCB_t* q);
