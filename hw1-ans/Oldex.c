/*
 * Program to count using a for loop, a while loop, and a do...while loop
 * Now with 3rd input to determine incremantation rates
 * --> This is for homework 1, question 3, for ECS 36A Fall 2019
 *
 * Eric Wang, ECS 36A
 * version 1	September 26, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

/* Take starting/ending number and increment:m,n,icr*/
void do_for(int m, int n, int icr)
{
    /* Checks if starting num is smaller than ending num, also if icr is valid*/
    if (m < n && icr > 0)
    {
        /* Loop up and print until starting num is same as ending num*/
        int i;
        for (i = m; i <= n; i += icr)
        {
            printf("%d\n", i);
        }
    }
    /* Check if starting num is larger than ending num, also if icr is valid*/
    else if (m > n && icr < 0)
    {
        /* Loop down and print until starting is same as ending num*/
        int i;
        for (i = m; i >= n; i += icr)
        {
            printf("%d\n", i);
        }
    }
    /* Print starting num if starting num and ending num are the same*/
    else if (m == n)
    {
        printf("%d\n", m);
    }
    else
    {
        printf("Error:invalid increment %d\n", icr);
    }
}

/* Take starting and ending number:m,n*/
void do_while(int m, int n, int icr)
{
    /* Check is starting num and ending num are same, if so, do not run the while loops*/
    if (m == n)
    {
        printf("%d\n", m);
    }
    /*Keep printing incrementally until starting num is same as ending num*/
    while (m < n && m != n)
    {
        if (icr <= 0)
        {
            printf("Error:invalid increment %d\n", icr);
            break;
        }
        printf("%d\n", m);
        m = m + icr;
        if (m == n)
        {
            printf("%d\n", m);
        }
    }

    /*Keep printing decrementally until starting num is same as ending num*/
    while (m > n && m != n)
    {
        if (icr >= 0)
        {
            printf("Error:invalid increment %d\n", icr);
            break;
        }
        printf("%d\n", m);
        m = m + icr;
        if (m == n)
        {
            printf("%d\n", m);
        }
    }
}

/* Take starting and ending number:m,n*/
void do_do(int m, int n, int icr)
{
    /*While starting num is greater than ending num, print starting num once and keep on decreasing until equalized*/
    if (m > n && m != n)
    {
        do
        {
            if (icr >= 0)
            {
                printf("Error:invalid increment %d\n", icr);
                break;
            }
            if (m >= n)
            {
                printf("%d\n", m);
            }
            m = m + icr;
        } while (m >= n);
    }

    /*While starting num is less than than ending num, print starting num once and keep on increasing until equalized*/
    else if (m < n && m != n)
    {
        do
        {
            if (icr <= 0)
            {
                printf("Error:invalid increment %d\n", icr);
                break;
            }
            if (m <= n)
            {
                printf("%d\n", m);
            }
            m = m + icr;
        } while (m <= n);
    }
    else if (m == n)
    {
        printf("%d\n", m);
    }
}

int getint(char *str, int *error)
{
	long m;			/* holds value of number in str */
char *mend = str; /* points to char beyond end of number */

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
if (*mend != '\0' || str == mend)
{
    fprintf(stderr, "%s is not an integer\n", str);
    *error = 1;
    return (-1);
}
/* it's a number but is too big or small to be an int */
if (errno == ERANGE &&
    ((m > 0 && m > INT_MAX) ||
     (m < 0 && m < INT_MIN)))
{
    fprintf(stderr, "%s is too big or small\n", str);
    *error = 1;
    return (-1);
}

/* okay, it's a valid integer; convert it and return */
return ((int)m);
}

/*
 * the main return
 */
int main(int argc, char *argv[])
{
    int m;   /* starting point */
    int n;   /* ending point */
    int d;   /* increment */
    int err; /* place for error code */

    /*
	 * check that you got 3 arguments,
	 * the starting point, the ending point,
	 * and the increment
	 */
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s m n\n", argv[0]);
        return (1);
    }

    /* get the starting point */
    if ((m = getint(argv[1], &err)) == -1 && err)
        return (1);

    /* get the ending point */
    if ((n = getint(argv[2], &err)) == -1 && err)
        return (1);

    /* get the increment */
    if ((d = getint(argv[3], &err)) == -1 && err)
        return (1);

    /*
	 * do the loops
	 */
    /* announce the for loop and do it */
    printf("for loop:\n");
    do_for(m, n, d);

    /* announce the while loop and do it */
    printf("while loop:\n");
    do_while(m, n, d);

    /* announce the do ... while loop and do it */
    printf("do ... while loop:\n");
    do_do(m, n, d);

    /*
	 * all done -- give good exit code
	 */
    return (0);
}
