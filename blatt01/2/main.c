/* Sourcecode by David Schwarzmann, 06.04.17 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

typedef void* pthread_addr_t;
typedef struct {
  int val;
} data;

#define LENGTH 4

int field[LENGTH][2];
int sums[LENGTH];

// Thread "work" function
void *add_op_thread(pthread_addr_t arg) {
  // For convenience the index/name of the thread
  int index = (*(data*)arg).val;
  printf("Thread #%d is starting in %ds ...\n", index, index +1);
  sleep(index + 1);
  printf("Thread #%d started!\n", index);
  int *input = (int*)field[index];
  int *result = (int*)malloc(sizeof(int));
  *result = input[0] + input[1];
  free(arg);
  printf("Thread #%d exited with result %d\n", index, *result);
  pthread_exit((pthread_addr_t) result);
} // add_op_thread()

int main (void) { // Erzeugerthread
  srand(time(NULL));
  // Create an array to hold all created threads
  pthread_t thread[LENGTH];
  int i;
  int* result = (int*) malloc(sizeof(int));

  // Generate random default values from 0..9 and store them as example values
  for(i=0; i < LENGTH; i++) {
    field[i][0] = rand() % 10;
    field[i][1] = rand() % 10;
  }

  // Print starting time & message
  time_t now = time(NULL);
  printf("Program started at (%lds) %s\n", now, ctime(&now));

  // Create each thread
  for (i = 0; i < LENGTH; i++) {
    // Create a temporary struct to store the inde (dirty)
    data* d = malloc(sizeof(data));
    // double check return code of malloc
    if (errno != 0) {
      printf("WARNING: malloc returned the return code %d for creating a data struct!\n", errno);
    }
    // assign current index to struct
    (*d).val = i;

    // Spinoff thread with the previous defined struct
    int s = pthread_create(&thread[i], NULL, add_op_thread,(pthread_addr_t) d);
    // Dublecheck return code of pthread_create
    if (s != 0) {
      printf("WARNING: pthread_create returned the return code %d!\n", errno);
    }
  }

  // Wait for the created threads to finish
  for (i = 0; i < LENGTH; i++) {
    // Wait...
    pthread_join(thread[i], (void*)result);
    printf("A: result=%d\n",*result);
    // Store result
    sums[i]=*result;
    printf("B: result=%d\n",*result);
    pthread_detach(thread[i]);
  }

  *result = 0;

  for(i = 0; i < LENGTH; i++) {
    *result = sums[i];
  }
  printf("Total result is %d!\n", *result);

  now = time(NULL);
  printf("Program ended at (%lds) %s\n", now, ctime(&now));
} // main()
// Warten auf Threadergebnis
// Thread zerstören ?!
