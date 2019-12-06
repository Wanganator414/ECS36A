/*
 * program to count using a for loop, a while loop, and a do...while loop
 * with an increment
 * this is the framework; the counting is done in functions to be supplied
 * in another file
 * 
 * this is for homework 1, extra credit question 1, for ECS 36A Fall 2019
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
 * d is the increment
 */
void do_for(int m, int n, int d)
{
    /* Checks if starting num is smaller than ending num, also if d is valid*/
    if (m < n && d > 0)
    {
        /* Loop up and print until starting num is same as ending num*/
        int i;
        for (i = m; i <= n; i += d)
        {
            /*Print standard int instead of comma when at last number*/
            if (n - i <= 0)
            {
                printf("%d", i);
            }
            else
            {
                printf("%d,", i);
            }
        }
    }
    /* Check if starting num is larger than ending num, also if d is valid*/
    else if (m > n && d > 0)
    {
        /* Loop down and print until starting num is same as ending num*/
        int i;
        for (i = m; i >= n; i -= d)
        {
            /*Print standard int instead of comma when at last number*/
            if (n - i >= 0)
            {
                printf("%d", i);
                break;
            }
            else
            {
                printf("%d,", i);
            }
        }
    }
    /* Print starting num if starting num and ending num are the same*/
    else if (m == n && d > 0)
    {
        printf("%d\n", m);
    }
    else
    {

        printf("Error:invalid increment %d\n", d);
    }
}

/*
 * the "while" loop routine
 * m is the starting number
 * n is the ending number
 */
void do_while(int m, int n, int d)
{
    /*If m==n, and d is valid. Print m*/
    if (m == n && d > 0)
    {
        printf("%d\n", m);
    }
    /*If d is less than or equal to 0, print error message*/
    if (d<=0)
    {
        printf("Error: invalid increment %d\n", d);
    }
    /*Keep printing incrementally until starting num is same as ending num*/
    while (m < n && m != n && d > 0)
    {
        /*Check if a number is the last one to print, if so, print without commas*/
        if ((m + d) <= n)
        {
            printf("%d,", m);
        }
        else
        {
            printf("%d", m);
            break;
        }
        m = m + d;
        if (m == n)
        {
            printf("%d", m);
        }
    }
    /*Keep printing decrementally until starting num is same as ending num*/
    while (m > n && m != n && d > 0)
    {
        /*Check if a number is the last one to print, if so, print without commas*/
        if ((m - d) >= n)
        {
            printf("%d,", m);
        }
        else
        {
            printf("%d", m);
            break;
        }
        m = m - d;
        if (m == n)
        {
            printf("%d", m);
        }
    }
}
/*
 * the "do . . . while" loop routine
 * m is the starting number
 * n is the ending number
 */
void do_do(int m, int n, int d)
{
    /*While starting num is greater than ending num, print starting num once and keep on decreasing until equalized*/
    if (m > n && m != n)
    {
        do
        {
            /*If d is less than or equal to 0, break out fo loop and print error message*/
            if (d <= 0)
            {
                printf("Error:invalid increment %d\n", d);
                break;
            }
            /*Print one more time before m==n*/
            if (m > n)
            {
                printf("%d,", m);
            }
            else
            {
                printf("%d\n", m);
            }
            /*Decrement m as it gets closer to n*/
            m = m - d;
            /*Keep going through the loop until m==n*/
        } while (m >= n);
    }

    /*While starting num is less than than ending num, print starting num once and keep on increasing until equalized*/
    else if (m < n && m != n)
    {
        do
        {
            /*If invalid d value, break out of loop and print error*/
            if (d <= 0)
            {
                printf("Error:invalid increment %d\n", d);
                break;
            }
            /*Print m one more time before m==n*/
            if (m < n)
            {
                printf("%d,", m);
            }
            else
            {
                printf("%d\n", m);
            }
            /*Increment m as it gets closer to n*/
            m = m + d;
        } while (m <= n); /*Keep going through the loop until m==n*/
    }
    /*Handle when m==n, print out m*/
    else if (m == n)
    {
        /*If invalid d, print out error message*/
        if (d <= 0)
        {
            printf("Error: invalid increment %d\n", d);
        }
        else
        {
            printf("%d", m);
        }
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
    long m;           /* holds value of number in str */
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
    printf("\nwhile loop:\n");
    do_while(m, n, d);
    /* announce the do ... while loop and do it */
    printf("\ndo ... while loop:\n");
    do_do(m, n, d);

    /*
	 * all done -- give good exit code
	 */
    return (0);
}
