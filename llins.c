/*
 * builds a linked list
 * -- insertion done recursively
 * -- printing done recursively
 *
 * Matt Bishop, ECS 36A, Fall 2019
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * macros
 */
#define BUFFERSIZE 1024		/* max line length */

/*
 * structure of a node
 */
struct list_elt {
	int val;		/* value */
	int count;		/* how many times it occurs */
	struct list_elt *next;	/* points to next element in list */
};

/*
 * create a new node
 */
struct list_elt *newnode(int val)
{
	struct list_elt *rval;		/* pointer to new space */

	/* allocate space, and complain if it fails */
	if ((rval = malloc(sizeof(struct list_elt))) == NULL){
		perror("cannot allocate new node");
		return(NULL);
	}

	/* fill in the fields */
	rval->val = val;
	rval->count = 1;
	rval->next = NULL;

	/* now return it */
	return(rval);
}

/*
 * insert new node into list
 * tjhis is recursive
 *	-- base case: list is empty (this becomes new head)
 *	   or it goes before the current head
 *	-- recurse: otherwise, recurse to get the (possibly new)
 *	   head, point the current head's next field to it, and return
 */
struct list_elt *insert(struct list_elt *head, struct list_elt *elt)
{
	/* base case: list empty */
	if (head == NULL)
		return(elt);

	/* now compare to the first element */
	if (head->val == elt->val){
		/* increment count */
		head->count++;
		free(elt);
		return(head);
	}
	if (head->val > elt->val){
		/* it goes in front of the head */
		/* becoming the new head */
		elt->next = head;
		return(elt);
	}

	/* it goes later, so recurse */
	head->next = insert(head->next, elt);

	/* return the (possibly new) head */
	return(head);
}

/*
 * print the list
 * this is recursive
 *	-- base case: list is empty; just return
 *	-- recursion: print head, then print tail (recursion)
 */
void printlist(struct list_elt *head)
{
	/* if list empty, do nothing */
	if (head == NULL)
		return;

	/* print the current elemnent */
	printf("%d(%d) ", head->val, head->count);

	/* now print the rest */
	printlist(head->next);
}

/*
 * the main routine
 */
int main(int argc, char *argv[])
{
	int n;			/* integer from stdin */
	char buf[BUFFERSIZE];	/* input buffer */
	struct list_elt *head = NULL;	/* head of list */
	struct list_elt *e;	/* element to be added to list */

	/*
	 * loop, reading until EOF
	 */
	while(printf("> "), fgets(buf, BUFFERSIZE, stdin) != NULL){
		if (sscanf(buf, "%d", &n) == 1){
			/* got a number! stick it in a node */
			if ((e = newnode(n)) == NULL)
				return(1);
			/* put it in the list */
			head = insert(head, e);
			/* and print the list for veriffication */
			printf("Current list: ");
			printlist(head);
			putchar('\n');
		}
		else{
			/* oops . . . didn't get an integer */
			printf("Need an integer!\n");
		}
	}

	/*
	 * done -- print final list and quit
	 */
	printf("\nFinal list: ");
	printlist(head);
	putchar('\n');

	/* all's well */
	return(0);
}
			
