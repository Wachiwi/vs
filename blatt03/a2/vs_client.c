#include "vs.h"


void vs11server_1(char *host) {
	CLIENT *clnt;
	quad_array  *result_1;
	int  vs_quad_1_arg;
	return_twice  *result_2;
	char * vs_twice_1_arg;
	char * *result_3;
	char * vs_readdir_1_arg;
	void  *result_4;
	char *vs_shutdown_1_arg;

	#ifndef	DEBUG
		clnt = clnt_create (host, VS11SERVER, VS11SERVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

	result_1 = vs_quad_1(&vs_quad_1_arg, clnt);
	if (result_1 == (quad_array *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = vs_twice_1(&vs_twice_1_arg, clnt);
	if (result_2 == (return_twice *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = vs_readdir_1(&vs_readdir_1_arg, clnt);
	if (result_3 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = vs_shutdown_1((void*)&vs_shutdown_1_arg, clnt);
	if (result_4 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}


int main (int argc, char *argv[]) {
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	vs11server_1 (host);
	exit (0);
}
