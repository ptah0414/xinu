/* xsh_ps.c - xsh_ps */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void lab_main()
{
  int i;
  init(FB);
  open(FB,"FB","0");
  
  control(FB,0,0,0);
  printf("[PRINT DEMO]");
  char art[16][16] = {
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', '-', '.', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ',', '\'', '/', ' ', '/', '/', '\\', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', '/', '/', '/', ' ', ' ', '/', '/', '/', ')' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', '/', '/', '/', ' ', ' ', ' /', ' /', '/', '/', '|' },
	{ ' ', ' ', ' ', ' ', ' ', '/', '/', '/', ' ', ' ', '/', '/', ' ', '/', '/', '/' },
	{ ' ', ' ', ' ', ' ', '/', '/', '/', ' ', ' ', '/', '/', ' ', '/', '/', '/', ' ' },
	{ ' ', ' ', ' ', '(', '`', ':', ' ', '/', '/', ' ', '/', '/', '/', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', '`', ';', '`', ':', ' ', '/', '/', '/', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' /', ' ', '/', ':', '`', ':', '/', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', '/', ' ', '/', ' ', '`', '\'', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '/', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', '/', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ '(', '_', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' } };
  int art_size = 16;
  for(i=0; i<art_size; i++){
    write(FB, art[i], art_size);
  }
  
  control(FB,100,0,0); //flush
  //control(FB,0,0,0);
}

void lab_modi(int cursor, char* c){

  control(FB,1,cursor,0); //change cursor
  write(FB, c, strlen(c));

  control(FB,100,0,0); //flush

}


/*------------------------------------------------------------------------
 * xsh_ps - shell command to print the process table
 *------------------------------------------------------------------------
 */
shellcmd xsh_ps(int nargs, char *args[])
{
	struct	procent	*prptr;		/* pointer to process		*/
	int32	i;			/* index into proctabl		*/
	char *pstate[]	= {		/* names for process states	*/
		"free ", "curr ", "ready", "recv ", "sleep", "susp ",
		"wait ", "rtime"};

	/* For argument '--help', emit help about the 'ps' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tDisplays information about running processes\n");
		printf("Options:\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	} else if (nargs == 2 && strncmp(args[1],"ice",4) == 0) {
		lab_main();
		//ring();
		return 0;
	}else if (nargs == 4 && strncmp(args[1],"modi",5) == 0) {
		int cursor = atoi(args[2]);
		lab_modi(cursor, args[3]);
		//ring();
		return 0;
	}

	/* Check for valid number of arguments */

	if (nargs > 1) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
				args[0]);
		return 1;
	}

	/* Print header for items from the process table */

	printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
		   "Pid", "Name", "State", "Prio", "Ppid", "Stack Base",
		   "Stack Ptr", "Stack Size");

	printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
		   "---", "----------------", "-----", "----", "----",
		   "----------", "----------", "----------");

	/* Output information for each process */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		if (prptr->prstate == PR_FREE) {  /* skip unused slots	*/
			continue;
		}
		printf("%3d %-16s %s %4d %4d 0x%08X 0x%08X %8d\n",
			i, prptr->prname, pstate[(int)prptr->prstate],
			prptr->prprio, prptr->prparent, prptr->prstkbase,
			prptr->prstkptr, prptr->prstklen);
	}
	return 0;
}
