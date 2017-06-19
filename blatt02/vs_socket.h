/* Sourcecode by David Schwarzmann, Fabian Vetter - 27.04.2017 */
#ifndef _VS_GUARD_H_
#define _VS_GUARD_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define VS_PROTOCOL 0
#define VS_MESSAGE_DELIMITOR '\0'

/*
 * Declare/Define commands
 * Command Palette:
 *
 *   CMD    Description
 *    0     Exit
 *    1     Uppercase
 *    2     Lowercase
 *    3     RESERVED
 *    4     RESERVED
 *    5     RESERVED
 *    6     RESERVED
 *    7     RESERVED
 *    8     RESERVED
 *    9     Shutdown
 */

#define VS_EXIT_COMMAND 0
#define VS_UPPER_COMMAND 1
#define VS_LOWER_COMMAND 2
#define VS_SHUTDOWN_COMMAND 9

#define VS_UNKNOWN_COMMAND "WAT?"

/*
 * Sending pattern is the following
 *    CMD,MSG\0
 * where CMD is one of the above defined commands
 * and MSG is a string that is terminated with \0
 */

#define VS_MSG_FORMAT_STRING "%d,%s"

/* Each command results in an answer from the server.
 * The mapping which answer by the server is expected
 * is defined in the following overview:
 *
 *    CMD     ANSWER
 *     0      OK\0
 *     1      <RESULT>\0
 *     2      <RESULT>\0
 *     3
 *     4
 *     5
 *     6
 *     7
 *     8
 *     9      OK\0
 *
 * Note: <RESULT> is the transformed MSG
 */

#define VS_OK_ANSWER "OK"

/*
 * ==================[ Timeouts ]=========================
 *
 * There are different possible occurences for timeouts:
 *    Client:
 *      - client cannot connect to server
 *      - client gets no answer in time window
 *      - client timeouts after "doing nothing" for too long
 *
 *    Server:
 *      - server tries to send a msg to a non existing client
 *      - server is waiting for client finish command
 *
 * To remove the need of sending healthcheck/heartbeat messages
 * the server side timeouts are handled by itself.
 * The server starts an internal timer beginning on the last
 * msg it recieved from the client. Each further msg from the
 * client resets this internal timer back to 0.
 *
 * NOTE: Each timeout below is in ms.
 */

#define VS_CLIENT_CONNECTION_TIMEOUT 10000
#define VS_CLIENT_ANSWER_TIMEOUT 10000
#define VS_CLIENT_NOP_TIMEOUT 3600000

#define VS_SERVER_SEND_TIMEOUT 10000
#define VS_SERVER_WAIT_TIMEOUT 30000

#define VS_SERVER_TIMEOUT_MSG "BYE"


/*
 * ==================[ Miscellaneous ]=========================
 */

#define VS_SERVER_READ_BUFFER_SIZE 256

/*
 * ==================[ Custom types ]=========================
 */

typedef struct {
  char* data;
  int length;
} vs_message;

/*
 * ==================[ Common Methods ]=========================
 */

void handle_error(int, const char*);
int read_socket(int, char*);
vs_message* read_message(int);

void ms_sleep(int);

#endif
