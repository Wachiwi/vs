/* Sourcecode by David Schwarzmann, 20.04.17 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 2
#define TIMEOUT 6 // in s

typedef void* pthread_addr_t;
typedef struct {
  int id;
  int ms_wait;
} thread_info;


void *thread_operate(pthread_addr_t v) {
  int c;
  thread_info ti = *((thread_info*)v);
  for(c = 1; ((c * ti.ms_wait) / 1000) <= TIMEOUT; c++) {
    printf("Thread #%d: Iteration %02d (%02ds)\n", ti.id, c, (c * ti.ms_wait) / 1000);
    usleep(ti.ms_wait * 1000);
  }
  int* x = 0;
  pthread_exit(x);
}

int main(int argc, char** argv) {
  pthread_t threads[THREAD_COUNT];
  int i;
  int thread_data[THREAD_COUNT][2] = {{1, 500},{2, 2000}};

  for(i = 0; i < THREAD_COUNT; i++) {
    thread_info *ti = malloc(sizeof(thread_info));
    (*ti).id =thread_data[i][0];
    (*ti).ms_wait = thread_data[i][1];
    pthread_create(&threads[i], NULL, thread_operate,(pthread_addr_t) ti);
  }

  printf("Running until ^C...\n");
  int *r = (int*)malloc(sizeof(int));
  int up = THREAD_COUNT;
  while(up > 0){
    for(i = 0; i < THREAD_COUNT; i++) {
      pthread_join(threads[i], (void*)r);
      printf("Thread #%d ended with code %d!\n", i, *r);
      up--;
    }
  }
}
