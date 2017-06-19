/* Sourcecode by David Schwarzmann, 27.04.2017 */
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include "vs_socket.h"

#define DEBUG 1
#define MAX_CLIENT_COUNT 10
#define MAX_CLIENT_QUEUE_LENGTH 5
#define _GNU_SOURCE

typedef struct {
  int c_fd;
  int c_len;
  struct sockaddr_in c_addr;
} client_data;

typedef struct {
  int c_fd;
  char* buffer;
  vs_message* msg;
} client_con;

void print_usage(char*);
void *handle_client(void*);
void *read_client(void*);
void *handle_msg(void*);
void vs_shutdown(pthread_t*);

int sock;

void print_usage(char* cli) {
  printf("Usage: %s <PORT>\n\r", cli);
}

void *handle_client(void* cd) {
  client_data* c_data = (client_data*)cd;
  pthread_t read_thread, send_thread;
  vs_message* msg;
  int uptime = 0;
  int* r;

  printf("[INFO] Started thread for client...\n\r");

  client_con* cc = malloc(sizeof(client_con));
  cc->c_fd = c_data->c_fd;
  cc->buffer = calloc(VS_SERVER_READ_BUFFER_SIZE, sizeof(char));

  // Finally start a thread that handles the client

  pthread_create(&read_thread, NULL, read_client,(void*) cc);
  while(uptime <= VS_CLIENT_NOP_TIMEOUT) {
    if (send_thread) {
      int *cmd;
      int s = pthread_tryjoin_np(send_thread, (void*)&cmd);
      if (s != EBUSY && *cmd == 0) break;
    }
    int s = pthread_tryjoin_np(read_thread, (void*)&msg);
    if (s == EBUSY) {
      uptime++;
    } else {
      printf("[DEBUG] Got message of length %d!\n\r", msg->length);
      if (msg->length == 0) break;
      uptime = 0;
      int i;
      printf("[DEBUG] Msg: ");
      for (i = 0; i < msg->length; i++) {
        printf("%c", msg->data[i]);
      }
      printf("\n");
      cc->msg = msg;
      pthread_create(&read_thread, NULL, read_client,(void*) cc);
      pthread_create(&send_thread, NULL, handle_msg, (void*) cc);
    }

    ms_sleep(50);
  }

  printf("[INFO] Client '%s' timed out!\n\r", inet_ntoa(c_data->c_addr.sin_addr));
  int s = pthread_cancel(read_thread);
  if (s != 0) printf("[WARNING] Could not cancel connection handler thread\n\r");
  s = pthread_join(read_thread, (void*)r);
  if (s != 0) printf("[WARNING] Could no join with terminated thread!\n\r");

  free(cc);
  free(msg);
  free(c_data);
  r = malloc(sizeof(int));
  *r = c_data->c_fd;
  close(c_data->c_fd);
  pthread_exit(r);
}

void *read_client(void* cc) {
  client_con* c_con = (client_con*)cc;
  char buffer[VS_SERVER_READ_BUFFER_SIZE];
  vs_message* msg = malloc(sizeof(vs_message));
  memset(msg, 0, sizeof(vs_message));
  memset(buffer, 0, VS_SERVER_READ_BUFFER_SIZE-1);
  int l = 0;
  while (l == 0) l = read_socket(c_con->c_fd, buffer);
  if (l > 0) {
    msg->data = calloc(l, sizeof(char));
    strncat(msg->data, buffer, l);
    msg->length = l;
  }
  pthread_exit(msg);
}

void *handle_msg(void* cc) {
  client_con* c_con = (client_con*)cc;
  int* cmd = malloc(sizeof(int));
  *cmd = c_con->msg->data[0] - '0';
  printf("[DEBUG] MSG-CODE: %d\n", *cmd);

  switch(*cmd) {
    case VS_SHUTDOWN_COMMAND:
    case VS_EXIT_COMMAND:
      c_con->msg->data = VS_OK_ANSWER;
      break;
    case VS_UPPER_COMMAND: {
                             char* t = (c_con->msg->data+2);
                             c_con->msg->data = malloc(c_con->msg->length -2);
                             int i;
                             for(i = 0; i < c_con->msg->length -2; i++) {
                               c_con->msg->data[i] = toupper(t[i]);
                             }
                           } break;
    case VS_LOWER_COMMAND: {
                             char* t = (c_con->msg->data+2);
                             c_con->msg->data = malloc(c_con->msg->length -2);
                             int i;
                             for(i = 0; i < c_con->msg->length -2; i++) {
                               c_con->msg->data[i] = tolower(t[i]);
                             }
                           } break;
    default:
                           c_con->msg->data = VS_UNKNOWN_COMMAND;
                           break;
  }

  printf("[DEBUG] Sending: %s\n", c_con->msg->data);

  int s = write(c_con->c_fd, c_con->msg->data, c_con->msg->length);
  if( s < 0) handle_error(-1, "write");
  else if(s == 0) printf("[WARNING] Nothing was sent!\n");
  pthread_exit(cmd);
}


void ctrl_c_handler(int sig) {
  int s = close(sock);
  if (s < 0) handle_error(s, "emergency close");
  exit(1);
}

void vs_shutdown(pthread_t* clients) {
  int *r, i;
  for(i = 0; i < MAX_CLIENT_COUNT; i++) {
    if (clients[i]) {
      int s = pthread_cancel(clients[i]);
      if (s != 0) printf("[WARNING] Could not cancel connection handler thread\n\r");
      s = pthread_join(clients[i], (void*)r);
      if (s != 0) printf("[WARNING] Could no join with terminated thread!\n\r");
    }
  }
  close(sock);
  exit(0);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("[ERROR] Not enough arguments!\n\r");
    print_usage(argv[0]);
    handle_error(EINVAL, "not_enough_args");
  }

  signal(SIGINT, ctrl_c_handler);

  // Parse port
  int port = atoi(argv[1]);
  // Define a streaming ipv4 socket with no specific protocol implementation
  sock = socket(AF_INET, SOCK_STREAM, VS_PROTOCOL);
  if (sock == -1) handle_error(sock, "create_socket");

  // =========================================================================================================
  // Preparation of the socket communication stuff
  struct sockaddr_in socket_address;
  // Set everything inside the memory area to 0
  memset(&socket_address, 0, sizeof(struct sockaddr_in));
  // Define listening socket by specifiying it as an IPv4 socket that listens on `port`
  socket_address.sin_family = AF_INET;
  socket_address.sin_port = htons(port);
  socket_address.sin_addr.s_addr = INADDR_ANY;

  // Finally apply the theoretical structures from above
  if(bind(sock, (struct sockaddr*) &socket_address, sizeof(socket_address)) < 0) handle_error(-1, "bind");
  // Allow incoming requests with a max queue length defined by MAX_CLIENT_QUEUE_LENGTH
  listen(sock, MAX_CLIENT_QUEUE_LENGTH);

  // ========================================================================================================
  // Main Loop start
  printf("Waiting for client requests...\n\r");
  pthread_t c_handlers[MAX_CLIENT_COUNT];
  // Temporary way for handling clients without overstacking
  // Could be improved by using an dynamic list
  int client_count = 0;

  // Handle client requests
  while(1) {
    int i, *cmd;

    // Check for terminated threads
    for(i = 0; i < MAX_CLIENT_COUNT && client_count > 0; i++) {
      int s = pthread_tryjoin_np(c_handlers[i], (void*)&cmd);
      if (s != EBUSY ) {
        if(*cmd == VS_SHUTDOWN_COMMAND) vs_shutdown(c_handlers);
        memset(&c_handlers[i], 0, sizeof(pthread_t));
        if(client_count > 0) client_count--;
      }
    }

    struct sockaddr_in client_address;
    socklen_t client_length = sizeof(client_address);
    int client = accept(sock, (struct sockaddr*) &client_address, &client_length);
    if (client < 0) handle_error(-1, "accept");

    printf("[INFO] Client connected from %s\n\r", inet_ntoa(client_address.sin_addr));

    // Define a custom struct that contains all required information for handling the client inside a thread
    if (client_count < MAX_CLIENT_COUNT) {
      client_data* cd = malloc(sizeof(client_data));
      cd->c_fd = client;
      cd->c_addr = client_address;
      cd->c_len = (int)client_length;
      // Finally start a thread that handles the client
      for(i = 0; i < MAX_CLIENT_COUNT; i++) {
        if(!c_handlers[i]) {
          pthread_create(&c_handlers[client_count], NULL, handle_client,(void*) cd);
          break;
        }
      }
      // Increase the amount of handled clients
      client_count++;
    }
  }

  return EXIT_SUCCESS;
}
