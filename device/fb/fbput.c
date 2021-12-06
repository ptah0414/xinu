#include <xinu.h>

#define 	N	16

extern char frame_buffer[N][N];  /* shared buffer */
extern int frame_cursor;


devcall	fbputc (
	  struct dentry *devptr,	/* Entry in device switch table */
	  char		ch		/* Character (byte) to write	*/
	)
{

	int x = frame_cursor / N;
	int y = frame_cursor % N;
	frame_buffer[x][y] = ch;

	if( x < N && y < N) {frame_cursor++;}

	else{return SYSERR;}


	return OK;
}
