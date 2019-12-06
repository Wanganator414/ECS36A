/*
 * getbit -- a program for obtaining a bit from an integer
 *
 * History
 * 1.0		Matt Bishop; original version
 * 
 * Eric Wang added changes.
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * the main routine -- does it all
 *
 * Entered by:	no parameters; takes input from stdin
 *
 * Exits with:	nothing
 *
 * Exceptions:	bit position must be between 0 and 32"
 *			-- invalid bit position entered
 */
int main(void)
{
	int n;			/* number to get bits from */
	int bpos;			/* bit position we want */
	int i;		/* number of numbers read */
	char buf[1024];
	
	/*
	 * loop reading numbers and printing bit positions
	 */
	while(printf("integer bitnumber> "),
			fgets(buf, 1024, stdin) != NULL){
		/* now scan in the numbers */
		i = sscanf(buf, "%d %d", &n, &bpos);
		/* first check the numbers input for errors */
		if (i == 0){
			/* nothing entered -- reprompt */
			continue;
		}
		if (i == 1){
			/* number entered -- go for bit number */
			printf("bit number>> ");
			/* on eof, exit */
			if ((i = scanf("%d", &bpos)) == -1)
				exit(0);
			/* if just a return, ask for number again */
			if (i == 0)
				continue;
		}
		/* is bit position too big? */
		if (bpos > (sizeof(n) * 8 - 1)){
			printf("bit position must be between 0 and %ld\n",
					sizeof(n) * 8 - 1);
			continue;
		}
		/* print the result */
		printf("%d\n", (n>>bpos)&1);	/*Original code printed entire new right shifted number, rather than the desired bit. By adding binary '&' operator with 1, you can get the desired bit*/
	}

	/*
	 * put out a newline, so shell prompt is on the next line
	 */
	putchar('\n');

	/*
	 * fare thee well!
	 */
	exit(0);
}
