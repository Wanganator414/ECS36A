/*
 * a set of functions implemented recursively
 */
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/* find the length of a string */
int rec_strlen(char *s)
{
	/* base case: empty string has length 0 */
	if (*s == '\0')
		return(0);

	/* now express the length as involving */
	/* the length of a shorter string      */
	return(1 + rec_strlen(s+1));
}

/* 1 is the argument is composed of letters *only*; 0 otherwise */
int rec_isonlyalpha(char *s)
{
	/*  base case: empty string is trivally composed of letters */
	if (*s == '\0')
		return(0);

	/*  now see if the first is alphabetic */
	if (!isalpha(*s))
		return(0);

	/* it is; check the rest of the string */
	return(rec_isonlyalpha(s+1));
}

/* find maximum element of an array */
int largest(int nums[], int numnums)
{
	int largest_rest;	/* largest number of rest of list */

	/* base case: list of 1 element, return that element */
	if (numnums == 1)
		return(nums[0]);

	/* now return the larger of the first */
	/* element and the largest element in */
	/* the rest of the array              */
    	largest_rest = largest(nums+1, numnums-1);
    	if (largest_rest < nums[0])
		return(nums[0]);
	
	return(largest_rest);
}

/* reverse a string */
void revstr(char *b, char *e)
{
	char tmp;	/* used t swap characters */

	/* base case: empty list gives same reverse */
    	if (b >= e)
		return;
	
	/* swap the first and last elements, then */
	/* the string up to but not including the */
	/* last element                           */
	tmp = *b;
	*b = *e;
	*e = tmp;
	revstr(b+1, e-1);
}

