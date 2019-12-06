/*
 * First part of a game of life
 *
 * Draw the board
 *
 * Matt Bishop, ECS 36A, Fall 2019
 * Answer to homework 2, question 4
 */
#include <stdio.h>
#include <string.h>

/*
 * macrios
 */
#define	MAXCOLS	1000
#define MAXROWS	1000

/* board dimensions */
int cols = MAXCOLS;
int rows = MAXROWS;

/* the board -- big enough to hold any reasonable size */
char board[MAXROWS][MAXCOLS];

/*
 * draw the outline of the board
 */
void prboard(void)
{
	int i, j;	/* counters in for loops */

	/* top border */
	for(i = 0; i < cols+2; i++)
		putchar('-');
	putchar('\n');

	/* now the rows */
	for(i = 0; i < rows; i++){
		putchar('|');
		for(j = 0; j < cols; j++)
			putchar(board[i][j]);
		putchar('|');
		putchar('\n');
	}

	/* bottom border */
	for(i = 0; i < cols+2; i++)
		putchar('-');
	putchar('\n');
}

/*
 * 
*/

/*
 * main routine
 */
int main(int argc, char *argv[])
{
	int n;		/* number of numbers read */
	FILE *inpf;

	/*
	 * the argument is th input file
	 */
	if (argc != 2){
		fprintf(stderr, "Usage: %s board_pattern\n", argv[0]);
		return(1);
	}

	/*
	 * open the file
	 */
	if ((inpf = fopen(argv[1], "r")) == NULL){
		perror(argv[1]);
		return(1);
	}

	/*
	 * read in the board
	 */
	for(rows = 0; fgets(board[rows], MAXCOLS, inpf) != NULL; rows++){
		n = strlen(board[rows]);
		if (board[rows][n-1] == '\n'){
			board[rows][n-1] = '\0';
			n -= 1;
		}
		if (rows == 0){
			/* set the number of columns */
			cols = n;
		}
		else{
			/* check that the row length is right */
			if (n != cols){
				fprintf(stderr, "%s: line %d is wrong length\n", argv[1], rows+1);
				return(1);
			}
		}
		/* now check everything is 'X' or 'O' */
		for(n = 0; n < cols; n++)
			if (board[rows][n] != 'X' && board[rows][n] != 'O'){
				fprintf(stderr, "%s: bad character '%c' in line %d\n",
								argv[1], board[rows][n], rows+1);
				return(1);
			}
	}

	/*
	 * print the board
	 */
	prboard();

	/* done! */
	return(0);
}
