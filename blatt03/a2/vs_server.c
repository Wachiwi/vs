#include <dirent.h>

#include "vs.h"

quad_array * vs_quad_1_svc(int *argp, struct svc_req *rqstp) {
	static quad_array *result = malloc(sizeof(quad_array));

	return &result;
}

return_twice * vs_twice_1_svc(char **argp, struct svc_req *rqstp) {
	static return_twice  result = malloc(sizeof(return_twice));
	result.str1 = argp;
	result.str2 = calloc(strlen(*argp), sizeof(char));
	strcpy(result, argp->str1);
	strcat(result, argp->str2);
	return &result;
}

char ** vs_readdir_1_svc(char **argp, struct svc_req *rqstp) {
	static char * result;

	struct dirent* cwd = readdir(".");
	int i;
	for(i = 0; cwd[i] < '\0'; i++) {
		d_name
	}

	return &result;
}

void * vs_shutdown_1_svc(void *argp, struct svc_req *rqstp) {
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}
