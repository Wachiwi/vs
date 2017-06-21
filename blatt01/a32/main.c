/* Sourcecode by David Schwarzmann, 20.04.17 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define THREAD_COUNT 2
#define TIMEOUT 5 // in s

// Props to http://man7.org/linux/man-pages/man3/pthread_cancel.3.html
#define handle_error_en(en, msg) do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

typedef void* pthread_addr_t;
typedef struct {
  int id;
  int ms_wait;
} thread_info;


// Simple thread function that prints a simple string to stdout
void *thread_operate(pthread_addr_t v) {
  thread_info ti = *((thread_info*)v);
  int c;
  // Repeat printing for lifetime
  for(c = 1; 1; c++) {
    usleep(ti.ms_wait * 1000);
    // Print        ID     TERATION       UPTIME
    printf("Thread #%d: Iteration %02d (%ds uptime)\n", ti.id, c, (c * ti.ms_wait) / 1000);
  }
}

int main(int argc, char** argv) {
  // Array for all threads
  pthread_t threads[THREAD_COUNT];
  // Array that stores the information of the threads
  thread_info *tis[THREAD_COUNT];
  // Thread Meta-data
  int thread_data[THREAD_COUNT][2] = {{1, 500},{2, 2000}};
  int i, s;

  // ==================== [ SECTION 1 ] =========================

  for(i = 0; i < THREAD_COUNT; i++) {
    // Create a information struct based on given meta data
    tis[i] = malloc(sizeof(thread_info));
    tis[i]->id = thread_data[i][0];
    tis[i]->ms_wait = thread_data[i][1];
    // Spin off thread an check for an error
    s = pthread_create(&threads[i], NULL, thread_operate,(pthread_addr_t) tis[i]);
    if (s != 0)
      handle_error_en(s, "pthread_create");
  }

  // ==================== [ SECTION 2 ] =========================
  // Wait for timeout

  int* r = malloc(sizeof(int));;
  int time = TIMEOUT;
  while(time >= 0){
    printf ("Remaining until timeout: %ds...\n", time--);
    sleep(1);
  }

  // ==================== [ SECTION 3 ] =========================
  // Send a cancel signal to all threads started above

  printf("TIMEOUT! Cancelling all running threads...\n");
  for(i = 0; i < THREAD_COUNT; i++) {
    printf("Cancelling thread #%d...\n", tis[i]->id);
    s = pthread_cancel(threads[i]);
    if (s != 0) handle_error_en(s, "pthread_cancel");
   }

  // Wait for threads to cancel && debugging purposes
  sleep(3);

  // ==================== [ SECTION 4 ] =========================
  // Join with stopped threads and check if they were cancelled

  for(i = 0; i < THREAD_COUNT; i++) {
    pthread_join(threads[i], (void*)r);
    if (s != 0) handle_error_en(s, "pthread_join");
    if(r == PTHREAD_CANCELED) {
      printf("Thread #%d was sucessfully cancelled!\n", tis[i]->id);
    } else {
      printf("Thread #%d was no cancelled but stopped with code %d!\n", tis[i]->id, *(int*)r);
    }
  }
  return 0;
}
