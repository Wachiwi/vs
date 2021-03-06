/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _VS_H_RPCGEN
#define _VS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct add_params {
	long p1;
	long p2;
};
typedef struct add_params add_params;

struct concat_params {
	char *str1;
	char *str2;
};
typedef struct concat_params concat_params;

struct split_return {
	char *pre;
	char *post;
};
typedef struct split_return split_return;

#define VS11SERVER 0x20004123
#define VSSERVERVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define vs_square 1
extern  long * vs_square_1(long *, CLIENT *);
extern  long * vs_square_1_svc(long *, struct svc_req *);
#define vs_add 2
extern  long * vs_add_1(add_params *, CLIENT *);
extern  long * vs_add_1_svc(add_params *, struct svc_req *);
#define vs_concat 3
extern  char ** vs_concat_1(concat_params *, CLIENT *);
extern  char ** vs_concat_1_svc(concat_params *, struct svc_req *);
#define vs_split 4
extern  split_return * vs_split_1(char **, CLIENT *);
extern  split_return * vs_split_1_svc(char **, struct svc_req *);
#define vs_increment 5
extern  void * vs_increment_1(long *, CLIENT *);
extern  void * vs_increment_1_svc(long *, struct svc_req *);
#define vs_Shutdown 6
extern  void * vs_shutdown_1(void *, CLIENT *);
extern  void * vs_shutdown_1_svc(void *, struct svc_req *);
extern int vs11server_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define vs_square 1
extern  long * vs_square_1();
extern  long * vs_square_1_svc();
#define vs_add 2
extern  long * vs_add_1();
extern  long * vs_add_1_svc();
#define vs_concat 3
extern  char ** vs_concat_1();
extern  char ** vs_concat_1_svc();
#define vs_split 4
extern  split_return * vs_split_1();
extern  split_return * vs_split_1_svc();
#define vs_increment 5
extern  void * vs_increment_1();
extern  void * vs_increment_1_svc();
#define vs_Shutdown 6
extern  void * vs_shutdown_1();
extern  void * vs_shutdown_1_svc();
extern int vs11server_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_add_params (XDR *, add_params*);
extern  bool_t xdr_concat_params (XDR *, concat_params*);
extern  bool_t xdr_split_return (XDR *, split_return*);

#else /* K&R C */
extern bool_t xdr_add_params ();
extern bool_t xdr_concat_params ();
extern bool_t xdr_split_return ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_VS_H_RPCGEN */
