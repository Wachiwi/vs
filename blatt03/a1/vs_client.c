/* Sourcecode by David Schwarzmann, 29.05.17 */
#include <time.h>
#include <stdlib.h>

#include "vs.h"

int nrnd() {
	return rand() % 10 + 1;
}

void vs11server_1(char *host) {
	CLIENT *clnt;
	long  *result_1;
	long vs_square_1_arg = nrnd();
	long  *result_2;
	add_params vs_add_1_arg = {nrnd(), nrnd()};
	char * *result_3;
	concat_params vs_concat_1_arg = {"abc", "def"};
	split_return  *result_4;
	char * vs_split_1_arg = "abc def";
	void  *result_5;
	long vs_increment_1_arg = nrnd();
	void  *result_6;
	char *vs_shutdown_1_arg = NULL;

	#ifndef DEBUG
		clnt = clnt_create (host, VS11SERVER, VSSERVERVERS, "tcp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif /* DEBUG */

	result_1 = vs_square_1(&vs_square_1_arg, clnt);
	if (result_1 == (long *) NULL) {
		clnt_perror (clnt, "vs_square call failed");
	}
	printf("square(%li) = %li\n", vs_square_1_arg, *result_1);

	result_2 = vs_add_1(&vs_add_1_arg, clnt);
	if (result_2 == (long *) NULL) {
		clnt_perror (clnt, "vs_add call failed");
	}
	printf("vs_add({%li, %li}) = %li\n", vs_add_1_arg.p1, vs_add_1_arg.p2, *result_2);

	result_3 = vs_concat_1(&vs_concat_1_arg, clnt);
	if (result_3 == (char **) NULL) {
		clnt_perror (clnt, "vs_concat call failed");
	}
	printf("vs_concat({\"%s\", \"%s\"}) = \"%s\"\n", vs_concat_1_arg.str1, vs_concat_1_arg.str2, *result_3);

	result_4 = vs_split_1(&vs_split_1_arg, clnt);
	if (result_4 == (split_return *) NULL) {
		clnt_perror (clnt, "vs_split call failed");
	}
	printf("vs_split(\"%s\") = {\"%s\", \"%s\"}\n", vs_split_1_arg, result_4->pre, result_4->post);

	result_5 = vs_increment_1(&vs_increment_1_arg, clnt);
	if (result_5 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("vs_increment(%li)\n", vs_increment_1_arg);

	result_6 = vs_shutdown_1((void*)&vs_shutdown_1_arg, clnt);
	if (result_6 == (void *) NULL) {
		printf("vs_shutdown seemed to work\n");
	}

	#ifndef DEBUG
		clnt_destroy (clnt);
	#endif  /* DEBUG */
}


int main (int argc, char *argv[]) {
	srand(time(NULL));
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	vs11server_1 (host);
	exit (0);
}
