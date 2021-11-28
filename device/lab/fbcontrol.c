#include <xinu.h>

#define N 16
extern char frame_buffer[N][N];
extern int frame_cursor;

devcall	fbcontrol (
	 struct dentry	*devptr,	/* Entry in device switch table	*/
	 int32	func,			/* A control function		*/
	 int32	arg1,			/* Argument #1			*/
	 int32	arg2			/* Argument #2			*/
	)
{
	frame_cursor = 0;
	int i, j;	
	for(i=0;i<N;i++){
	  for(j=0;j<N;j++){
	    frame_buffer[i][j] = '\0';
	  }	
	}
	return OK;
}
