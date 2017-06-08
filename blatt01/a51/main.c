/* Sourcecode by David Schwarzmann, 20.04.17 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#define THREAD_COUNT 2
#define BUFFER_SIZE 3
// Props to http://man7.org/linux/man-pages/man3/pthread_cancel.3.html
#define handle_error(en, msg) do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

typedef enum { false, true } bool;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t finished = PTHREAD_COND_INITIALIZER;

void *print_thread(void* buffer) {
  int* s = malloc(sizeof(int));
  bool stopped = false;
  printf("Thread #2 started...\n\r");
  while(!stopped) {
    *s = pthread_mutex_lock(&mut);
    if(*s != 0) handle_error(*s, "pthread_mutex_lock");
    printf("Thread #2: %d\n\r", *(int*)buffer);
    if (*(int*)buffer == 0) {
      *s = pthread_cond_signal(&finished);
      if(*s != 0) handle_error(*s, "pthread_cond_signal");
      *s = pthread_mutex_unlock(&mut);
      if(*s != 0) handle_error(*s, "pthread_mutex_unlock");
      break;
    }
    *s = pthread_mutex_unlock(&mut);
    if(*s != 0) handle_error(*s, "pthread_mutex_unlock");
    sleep(1);
  }
  pthread_exit(s);
}

void *generate_random(void* buffer) {
  srand(time(NULL));
  int c, s;
  printf("Thread #1 started...\n\r");
  for(c = 1; 1; c++) {
    s = pthread_mutex_lock(&mut);
    if(s != 0) handle_error(s, "pthread_mutex_lock");
    *(int*)buffer = rand() % 20;
    printf("Thread #1: %d (It: %d)\n\r", *(int*)buffer, c);
    s = pthread_mutex_unlock(&mut);
    if(s != 0) handle_error(s, "pthread_mutex_unlock");
    sleep(1);
  }
}

int main() {
  if (BUFFER_SIZE < 3) handle_error(1, "BUFFER_SIZE too small");
  int s;
  int* buffer = calloc(BUFFER_SIZE, sizeof(int));
  pthread_t threads[THREAD_COUNT];

  s = pthread_create(&threads[0], NULL, generate_random, buffer);
  if(s != 0) handle_error(s, "pthread_create");
  s = pthread_create(&threads[0], NULL, print_thread, buffer);
  if(s != 0) handle_error(s, "pthread_create");

  printf("Running until done or ^C...\n\r");
  int* res = malloc(sizeof(int));
  pthread_join(threads[0], (void*)res);
  return *res;
}
