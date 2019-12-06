/*
 * Program to count using a for loop, a while loop, and a do...while loop
 * this is the framework;
 * 
 * --> This is for homework 1, question 3, for ECS 36A Fall 2019
 *
 * Eric Wang, ECS 36A
 * version 1	September 26, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

/*
 * the "for" loop routine
 * m is the starting number
 * n is the ending number
 */
void do_for(int m, int n)
{
	/* Checks if starting num is smaller than ending num*/
	if (m < n)
	{
		/* Loop print until starting num is same as ending num*/
		int i;
		for (i = m; i <= n; i++)
		{
			printf("%d\n", i);
		}
	}
	/* Check if starting num is larger than ending num*/
	else if (m > n)
	{
		/* Loop print until starting is same as ending num*/
		int i;
		for (i = m; i >= n; i--)
		{
			printf("%d\n", i);
		}
	}
	/* Print starting num if starting num and ending num are the same*/
	else
	{
		printf("%d\n", m);
	}
}

/*
 * the "while" loop routine
 * m is the starting number
 * n is the ending number
 */
void do_while(int m, int n)
{
	/* Check is starting num and ending num are same, if so, do not run the while loops*/
	if (m == n)
	{
		printf("%d\n", m);
	}
	/*Keep printing incrementally until starting num is same as ending num*/
	while (m < n && m != n)
	{
		printf("%d\n", m);
		m = m + 1;
		if (m == n)
		{
			printf("%d\n", m);
		}
	}
	/*Keep printing decrementally until starting num is same as ending num*/
	while (m > n && m != n)
	{
		printf("%d\n", m);
		m = m - 1;
		if (m == n)
		{
			printf("%d\n", m);
		}
	}
}

/*
 * the "do . . . while" loop routine
 * m is the starting number
 * n is the ending number
 */
void do_do(int m, int n)
{
	/*While starting num is greater than ending num, print starting num once and keep on decreasing until equalized*/
	if (m > n)
	{
		do
		{
			printf("%d\n", m);
			m = m - 1;
		} while (m > n);
		printf("%d", m);
	}
	/*While starting num is less than than ending num, print starting num once and keep on increasing until equalized*/
	else if (m < n)
	{
		do
		{
			printf("%d\n", m);
			m = m + 1;
		} while (m < n);
		printf("%d", m);
	}
	else
	{
		printf("%d\n", m);
	}
}


/*
 * getint -- get an integer
 *
 * in parameters:
 * char *str	the string to be converted to an integer
 * int *error	location for integer error code
 *
 * out parameters:
 * int *error	1 if there is an error, 0 otherwise
 *
 * return value:
 * on success, integer resulting from converting str
 * on failure, -1; *error is set to 1 and error message is printed
 */
int getint(char *str, int *error)
{
	long m;			/* holds value of number in str */
	char *mend = str;	/* points to char beyond end of number */

	/*
 	 * initialize error codes
	 */
	error = 0;
	errno = 0;

	/*
	 * convert the string to a number
	 */
	m = strtol(str, &mend, 10);
	/* possible error 1: non-0integer char in string */
	if (*mend != '\0' || str == mend){
		fprintf(stderr, "%s is not an integer\n", str);
		*error = 1;
		return(-1);
	}
	/* it's a number but is too big or small to be an int */
	if (errno == ERANGE &&
		((m > 0 && m > INT_MAX) ||
			(m < 0 && m < INT_MIN))){
		fprintf(stderr, "%s is too big or small\n", str);
		*error = 1;
		return(-1);
	}

	/* okay, it's a valid integer; convert it and return */
	return((int) m);
}

/*
 * the main return
 */
int main(int argc, char *argv[])
{
	int m;		/* starting point */
	int n;		/* ending point */
	int err;	/* place for error code */


	/*
	 * check that you got 2 arguments,
	 * the starting point and the ending point
	 */
	if (argc != 3){
		fprintf(stderr, "Usage: %s m n\n", argv[0]);
		return(1);
	}

	/* get the starting point */
	if ((m = getint(argv[1], &err)) == -1 && err)
		return(1);

	/* get the ending point */
	if ((n = getint(argv[2], &err)) == -1 && err)
		return(1);
	
	/*
	 * do the loops
	 */
	/* announce the for loop and do it */
	printf("for loop:\n");
	do_for(m, n);

	/* announce the while loop and do it */
	printf("while loop:\n");
	do_while(m, n);

	/* announce the do ... while loop and do it */
	printf("do ... while loop:\n");
	do_do(m, n);

	/*
	 * all done -- give good exit code
	 */
	return(0);
}