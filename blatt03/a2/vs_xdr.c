/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "vs.h"

bool_t
xdr_return_twice (XDR *xdrs, return_twice *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->str1, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->str2, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_dir_node (XDR *xdrs, dir_node *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->desc, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->type, ~0))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->next, sizeof (dir_node), (xdrproc_t) xdr_dir_node))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_quad_array (XDR *xdrs, quad_array *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->size))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->elements.elements_val, (u_int *) &objp->elements.elements_len, ~0,
		sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	return TRUE;
}
