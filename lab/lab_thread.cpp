#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

int thread_count;

void* Hello(void* rank);

int main(int argc, char* argv[]) {
  long thread;
  long ** args;
  pthread_t* thread_handles;

  if(argc < 3)
    {
      std::cout << "usage: $ ./file <number of threads> <number to sum>" << std::endl;
      return 1;
    }
  else
    thread_count = strtol(argv[1], NULL, 10);
  
  thread_handles = (pthread_t *)malloc (thread_count*sizeof(pthread_t));
  
  args = (long**)malloc(thread_count*sizeof(long*));
  for(int i = 0; i < thread_count; i++)
    args[i] = (long*)malloc(2*sizeof(long));

  for (thread = 0; thread < thread_count; thread++)
    {
      args[thread][0] = thread;
      args[thread][1] = strtol(argv[2], NULL, 10);
      pthread_create(&thread_handles[thread], NULL, Hello, (void*) *(args+thread));
    }
  
  //printf("Hello from the main thread\n");

  long * p;
  for (thread = 0; thread < thread_count; thread++)
    {
      pthread_join(thread_handles[thread], (void**)&p);
      std::cout << "returned from thread " << thread << ": " << *p << std::endl;
    }

  free(thread_handles);
  return 0;
}

void * Hello(void * rank) {
  long * my_rank = (long *) rank;
  //printf("Hello from thread %ld:%ld of %d\n", my_rank[0], my_rank[1], thread_count);

  long * sum = (long*)malloc(sizeof(long));
  *sum = (my_rank[0] + my_rank[1]);
  
  pthread_exit(sum);
}
