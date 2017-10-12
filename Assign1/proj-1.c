// Dhananjayan Santhanakrishnan - 1211181423 & Joel Mascarenhas - 1211194319
// permission to use and distribute granted.
//
#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

#define N 3
semaphore_t empty, full, mutex;
int buffer[N];
int counter = 0;
int in = 0, out = 0, item_num=0, prod_delay = 1, cons_delay = 1;


void prod (int *arg)
{
    while (1){

        P(&empty);
          P(&mutex);
          printf("Writing child Thread # %d \n",*arg);

               buffer[*arg]++;
               counter++;
          V(&mutex);
          if(counter == 3){
            counter = 0;
            V(&full);
          }

    }
}



int main()
{
    int id[3] = {0, 1, 2};
    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;

    init_sem(&full, 1);
    init_sem(&empty,0);
    init_sem(&mutex, 1);

    start_thread(prod, &id[0]);

    start_thread(prod, &id[1]);

    start_thread(prod, &id[2]);

    while(1){

        P(&full);
          P(&mutex);
            printf("Reading from parent...\n");
        	    for(int i=0;i<3;i++){
                printf("%d ",buffer[i]);
                V(&empty);
              }
              printf("\n");
          V(&mutex);

      
    }
}
