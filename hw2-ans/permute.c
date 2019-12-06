/*
Written for ECS36A, Fall 2019

Eric Wang, October 19, 2019

Recursively prints all combinations of entered string input
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

/*Helper function to swap characters at their pointer locations*/
void swap(char *a, char *b)
{
    char temp = *a; /*Temperary variable to hold*/
    temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *input, int start, int end)
{
    int i;
    /*Base case checker*/
    if (start == end)
    {
        printf("%s", input);
    }
    else
    {
        for (i = start; i <= end; i++)
        {
            swap((input + start), (input + i));
            permute(input, (start + 1), end); /*Run permutation*/
            swap((input + start), (input + i)); /*Backtrack to switch back to previous config*/
        }
    }
}

int main()
{
    char input[SIZE];
    while (*input != NULL && *input != '\n') /*While user does not enter a blank line or control-d EOF command, keep running program*/
    {
        printf("$>$ ");
        fgets(input, SIZE, stdin); /*Array won't take more than 60 chars, extras are truncated*/
        int len = strlen(input);
        permute(input, 0, len - 2); /*Account for \0*/
    }
    return 0;
}