#include <xinu.h>

#define N 16
extern char frame_buffer[N][N];
extern int frame_cursor;

devcall	fbflush (
	 //struct dentry	*devptr,	/* Entry in device switch table	*/
	)
{
	int i, j;
	for(i=0; i<N; i++){
	  for(j=0; j<N; j++){
		putc(CONSOLE, frame_buffer[i][j]);
	  }
	  putc(CONSOLE, '\n');	
	}
	return OK;
}
