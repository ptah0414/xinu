#include <xinu.h>

#include <stdio.h>
#include <string.h>

#define N 16

extern char frame_buffer[N][N];  /* shared buffer */
extern int frame_cursor;

devcall	fbopen (
	  struct dentry *devptr,	/* Entry in device switch table */
	  char		*name,		/* Name to use, if any		*/
	  char		*mode		/* Mode for device, if any	*/
	)
{
	frame_cursor = 0;
	//Erase Screen
	putchar('\033'); putchar('['); putchar('2'); putchar('J');
	//Cursor Home
	putchar('\033');putchar('[');putchar(';');putchar('H');
	return OK;
}
