
#include <xinu.h>

#define 	N	16
extern char frame_buffer[N][N];  /* shared buffer */


devcall	fbread (
	  struct dentry *devptr,	/* Entry in device switch table */
	  char	*buff,			/* Buffer to hold bytes		*/
	  int32	count			/* Max bytes to read		*/
	)
{
/*
	struct ttycblk *typtr
	int32 avail;
	int32 nread;
	int32 firstch;
	char  ch;
*/

	return OK;
}
