#include "threads.h"
int global_count = 0;

void IncrementFunction1()
{
	int local_count = 0;
	while(1)
	{
    global_count++;
		local_count++;
    printf("\n\n Printing from Thread# %d :- Global value = %d and Local value = %d\n",currentThreadId(), global_count, local_count);
		sleep(1);
		yield();
	}
}

void IncrementFunction2()
{
	int local_count = 0;
	while(1)
	{
    global_count++;
		local_count++;
    printf("\n\n Printing from Thread# %d :- Global value = %d and Local value = %d\n",currentThreadId(), global_count, local_count);
		sleep(1);
		yield();
	}
}

void IncrementFunction3()
{
	int local_count = 0;
	while(1)
	{
    global_count++;
		local_count++;
    printf("\n\n Printing from Thread# %d :- Global value = %d and Local value = %d\n",currentThreadId(), global_count, local_count);
		sleep(1);
		yield();
	}
}


int main()
{
  createQueue();
  start_thread(IncrementFunction1);
  start_thread(IncrementFunction2);
  start_thread(IncrementFunction3);
  run();
  return 0;
}
