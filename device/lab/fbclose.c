
#include <xinu.h>

devcall	fbclose (
	  struct dentry *devptr		/* Entry in device switch table */
	)
{
	return OK;
}
