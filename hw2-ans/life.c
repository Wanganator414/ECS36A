/*
Written for ECS36A, Fall 2019

Eric Wang, October 19, 2019

Part 1 of Game of Life Program, take user inputs and prints game grid as required
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define HOR '-' 
#define VERT '|'

bool checkValidity(char *val) /*Checks if entered values are valid or not*/
{
    int i;
    for (i = 0; i < strlen(val); i++)
    {
        if (val[i] == '-' || isdigit(val[i]) == false)
        {                      /*Check if character is negative or a letter*/
            if (val[i] != 'x') /*Ignore lower case 'x'*/
            {

                printf("Invalid input, please try again.\n");
                return false;
            }
            else
            {
                continue; /*Continue if lower case x*/
            }
        }
        return true;
    }
}
/*Function to strip white spaces before,after, and between the input charcater sequence*/
char *stripSpace(char *input)
{
    int i, j;
    char *output = input;
    for (i = 0, j = 0; i < strlen(input); i++, j++) /*Place characters in new array if they are not empty spaces*/
    {
        if (input[i] != ' ')
            output[j] = input[i];
        else
            j--;
    }
    output[j] = 0;
    return output;
}

/*Function to print horizontal borders*/
void printH(int lines)
{
    int i;
    printf("-");
    for (i = lines; i > 0; i--)
    {
        printf("%c", HOR);
    }
    printf("-");
    printf("\n");
}

/*Function to print vertical borders*/
void printV(int lines, int gap)
{
    int i, j;
    for (i = lines; i > 0; i--)
    {
        printf("%c", VERT);
        for (j = gap; j > 0; j--)
        {
            printf(" "); /*Print horizontal gaps*/
        }
        printf("%c\n", VERT);
    }
}

void printBoard()
{
    char input2[100];
    fgets(input2, 100, stdin);
    char input[100];
    strcpy(input, stripSpace(&input2)); /*Strip and filter white spaces from input*/
    printf("\nOriginal: %s\n", input2);
    printf("STRIPED: %s\n", input);
    int index = strchr(input, 'x') - input; /*Get index of concurrance of 'x'*/
    int i, j;
    char hArr[10];
    char vArr[10];
    bool notPrinted = true;                 /*Checker to activate while loop*/
    if (checkValidity(input) && notPrinted) /*Will run once as long as entered values are valid*/
    {
        for (i = 0; i < index; i++) /*Populate horizontal length info from input string*/
        {
            hArr[i] = input[i];
        }

        for (j = (index + 1), i = 0; j < strlen(input); j++, i++) /*Populate vertical length info from input string*/
        {
            vArr[i] = input[j];
        }
        int hor;
        int ver;
        sscanf(hArr, "%d", &hor);
        sscanf(vArr, "%d", &ver);
        printf("Board size is: %dby%d\n", hor, ver);
        printH(hor);        /*Print top horizontal borders first*/
        printV(ver, hor);   /*Print both vertical borders*/
        printH(hor);        /*Print bottom horizontal borders*/
        notPrinted = false; /*Set checker to end while loop*/
    }
}

int main()
{
    printBoard();   /*Run the printing method*/
    return 0;
}