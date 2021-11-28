
#include <xinu.h>

#define 	N	16

extern char frame_buffer[N][N];  /* shared buffer */
//extern int frame_head, frame_tail; /* for buffer used as queue */
//extern int frame_mutex;


devcall	fbgetc (
	  struct dentry *devptr		/* Entry in device switch table */
	)
{
	/*
	char n;

        wait(frame_mutex);

        n = frame_buffer[frame_tail++];          
        if (frame_tail >= N)          
            frame_tail = 0;           
        signal(frame_mutex);

	return n;
	*/
 return OK;

}
