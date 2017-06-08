/* Sourcecode by David Schwarzmann, 06.04.17 */

#include <stdio.h>
#include "author.h"

void func(int argc, char** argv) {
  printf("CLI tool by %s\r\n\r\n", AUTHOR_NAME);
  printf("Size of basic types\r\n======================\n");
  printf("sizeof(char) = %lu\n", sizeof(char));
  printf("sizeof(short) = %lu\n", sizeof(short));
  printf("sizeof(int) = %lu\n", sizeof(int));
  printf("sizeof(long) = %lu\n", sizeof(long));
  printf("sizeof(long long) = %lu\n", sizeof(long long));
  printf("sizeof(char*) = %lu\n", sizeof(char*));
  printf("sizeof(int*) = %lu\n", sizeof(int*));
  printf("sizeof(void*) = %lu\n", sizeof(void*));
  printf("sizeof(void) = %lu\n", sizeof(void));

  printf("\r\nUnlisted basic types\r\n======================\n");
  printf("sizeof(float) = %lu\n", sizeof(float));

  printf("\r\nParameters\r\n======================\n");
  int i;
  for(i = 0; i < argc; i++) {
    printf("%d. Parameter = \"%s\"\r\n", i+1, argv[i]);
  }
}
