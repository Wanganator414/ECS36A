/*
 * First part of a game of life
 *
 * Draw the board
 *
 * Matt Bishop, ECS 36A, Fall 2019
 * Answer to homework 2, question 4
 */
#include <stdio.h>

/* board dimensions */
int cols = 78;
int rows = 10;

/*
 * draw the outline of the board
 */
void prboard(int rows, int cols)
{
	int i, j;	/* counters in for loops */

	/* top border */
	for(i = 0; i < cols+2; i++)
		putchar('-');
	putchar('\n');

	/* now the rows */
	for(i = 1; i < rows+1; i++){
		putchar('|');
		for(j = 1; j < cols+1; j++)
			putchar(' ');
		putchar('|');
		putchar('\n');
	}

	/* bottom border */
	for(i = 0; i < cols+2; i++)
		putchar('-');
	putchar('\n');
}

/*
 * main routine
 */
int main(void)
{
	int n;		/* number of numbers read */

	/*
	 * read in board dimensions
	 */
	printf("rows x columns> ");
	if ((n = scanf("%d x %d", &rows, &cols)) == EOF)
		return(0);
	if (n != 2){
		fprintf(stderr, "Input format: rxc with r, c positive integers\n");
		return(1);
	}
	if (rows < 1 || cols < 1){
		fprintf(stderr, "Positive numbers only, please!\n");
		return(1);
	}

	/*
	 * print the board
	 */
	prboard(rows, cols);

	/* done! */
	return(0);
}
