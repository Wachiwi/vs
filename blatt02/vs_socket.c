/* Sourcecode by David Schwarzmann, Fabian Vetter - 27.04.2017 */
#include "vs_socket.h"

void handle_error(int s, const char* msg) {
  if (s > 0) errno = s;
  perror(msg);
  exit(EXIT_FAILURE);
}

int read_socket(int s_fd, char* r_buffer) {
  int length = read(s_fd, r_buffer, VS_SERVER_READ_BUFFER_SIZE);
  if (length < 0) handle_error(length, "read");
  return length;
}

void ms_sleep(int n) {
  usleep(n * 1000);
}
