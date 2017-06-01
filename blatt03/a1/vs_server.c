/* Sourcecode by David Schwarzmann, 29.05.17 */
#include "vs.h"
#include <rpc/pmap_clnt.h>

	long *
vs_square_1_svc(long *argp, struct svc_req *rqstp)
{
	long  *result = malloc(sizeof(long));

	*result = *argp * *argp;

	return result;
}

	long *
vs_add_1_svc(add_params *argp, struct svc_req *rqstp)
{
	long  *result = malloc(sizeof(long));

	*result = argp->p1 + argp->p2;

	return result;
}

	char **
vs_concat_1_svc(concat_params *argp, struct svc_req *rqstp)
{
	static char * result;

	result = malloc(strlen(argp->str1)+strlen(argp->str2)+1);

	strcpy(result, argp->str1);
	strcat(result, argp->str2);

	return &result;
}

	split_return *
vs_split_1_svc(char **argp, struct svc_req *rqstp)
{
	static split_return result;

        int pre, post = 0;
        for(pre = 0; (*argp)[pre] != '\0'; pre++) {
                if ((*argp)[pre] == ' ' ||
                    (*argp)[pre] == '\t' ||
                    (*argp)[pre] == '\r' ||
                    (*argp)[pre] == '\n')
                         break;
        }

        for(post = pre; (*argp)[post] != '\0'; post++) {}

        result.pre = calloc(pre, sizeof(char));
        result.post = calloc(post, sizeof(char));

        int i;
        for(i = 0; i < pre; i++) {
                result.pre[i] = (*argp)[i];
        }

        for(i = 0; i < post; i++) {
                result.post[i] = (*argp)[pre + i];
        }

	return &result;
}

	void *
vs_increment_1_svc(long *argp, struct svc_req *rqstp)
{
	static long v = 0;
	v += *argp;
	return NULL;
}

	void *
vs_shutdown_1_svc(void *argp, struct svc_req *rqstp)
{
	pmap_unset (VS11SERVER, VSSERVERVERS);
	return NULL;
}
