
#include <xinu.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 16
/* Note that this simple queue is meant to be used with semaphores--
 * on its own, it doesn't know if it's empty or full!  Both cases
 * have head == tail.  One semaphore is enough to keep track of this.
 * Two semaphores are needed for control of both producer and consumer.
 */
char frame_buffer[N][N];  /* shared buffer */
int frame_cursor;

devcall	fbinit (
	  struct dentry *devptr		/* Entry in device switch table */
	)
{

	return OK;
}
