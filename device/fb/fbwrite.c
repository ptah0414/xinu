#include <xinu.h>
#define 	N	16

extern char frame_buffer[N][N];
extern int frame_cursor;


devcall	fbwrite (
	  struct dentry *devptr,	/* Entry in device switch table */
	  char	*buff,			/* Buffer holding data to write	*/
	  int32	count			/* Number of bytes to write	*/
	)
{
	int i;
	for(i=0; i<count; i++){
	  int x = frame_cursor / N;
	  int y = frame_cursor % N;
	  frame_buffer[x][y] = buff[i];

	  if( x < N && y < N) {frame_cursor++;}
	  else{return SYSERR;}
	}

	return OK;
}
