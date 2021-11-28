/* xsh_ps.c - xsh_ps */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/* app on ring buffer source code */

/*----------------------------------------------------------------------------
 *    prod2   --
 *----------------------------------------------------------------------------
 */
void prod2(void)
{
    int i;

/*
    char c = 'a';


    for( i=1; i<=200; i++ )  {
        putc(LAB14, c);
        if(++c == 'z')
                c = 'a';
        sleep(2);
    }
*/

  char dog[7][30]={
	".....|\\_/|...................",
	".....| @ @ . Woof! ..........",
	".....|   <> .................",
	".....|  _/\\------____ ((| |))",
	".....|               `--' |..",
	" ____|_       ___|   |___.'..",
	"/_/_____/____/_______|......."
  };
  int j;
  for(i=0;i<7;i++){
    putc(FB,'\n'); sleep(1);
    for(j=0;j<30;j++){
	putc(FB, dog[i][j]);
	sleep(1);
    }
  }
  for(i=0;i<10;i++){
    putc(FB,NULL);
    sleep(1);
  }

}

/*----------------------------------------------------------------------------
 *  cons2 --
 *----------------------------------------------------------------------------
 */
void cons2()
{
    int i;
    char c;
/*
    for( i=1;  i<=200; i++ )  {
        c = getc(LAB14);
        printf("%c-", c);
        sleep(1);
    }
*/

  for(i=0;i<300;i++){
	c = getc(FB);
        printf("%c", c);
        sleep(1);
  }

 
}


/*--------------------------------------------------------------------------
 *    ring --  producer and consumer process synchronized with semaphores
 *--------------------------------------------------------------------------
*/
void ring()
{
  resume( create(cons2, 1000, 20, "cons", 0, NULL));
  resume( create(prod2, 1000, 20, "prod", 0, NULL));
}

void lab_main()
{
  init(FB);
  open(FB,"FB","0");
  
  control(FB,0,0,0);
  printf("[This is fbputc]\n");
  char input[7] = "HELLO";
  int  input_size = 7;
  int i;
  for(i=0; i<input_size; i++){
	putc(FB, input[i]);
  }
  fbflush();

  control(FB,0,0,0);
  printf("\n\n\n[This if fbwrite]\n");
  char input2[] = "12345678901234561234567890";
  input_size = strlen(input2);
  write(FB,input2,input_size);
  fbflush();

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
  fbflush();
  
  control(FB,0,0,0);
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
	} else if (nargs == 2) {
		lab_main();
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
