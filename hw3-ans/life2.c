/*
 * 2nd part of a game of life
 *
 * Draw the board
 *
 * Eric Wang, ECS 36A, Fall 2019
 * Answer to homework 2, question 4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* board dimensions */
int cols = 100;
int rows = 100;

/*file info*/
int fileCols = 0;
int fileRows = 0;

/*global pattern record*/
char pattern[100][100];

/*
 * draw the outline of the board
 */
void prboard(int fileRows, int fileCols)
{
    int i = 0; /* counters in for loops */
    int x = 0; /*Cords for interior*/
    /* top border */
    for (i = 0; i < fileCols + 2; i++)
        putchar('-');
    putchar('\n');

    /* now the rows */
    for (i = 1; i < fileRows + 1; i++)
    {
        putchar('|');
        printf("%s", pattern[x]);
        putchar('|');
        putchar('\n');
        x += 1;
    }

    /* bottom border */
    for (i = 0; i < fileCols + 2; i++)
        putchar('-');
    putchar('\n');
}

void checkPattern(int argc, char **argv, int *fileRows, int *fileCols)
{
    /*Read pattern file from command line*/
    FILE *patternFile;
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    int curCharCount = 0;
    int prevCharCount = 0;
    int totalChars = 0;
    int rowCharCount[100];
    char ch;
    patternFile = fopen(argv[1], "r");
    if (patternFile == NULL)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(patternFile)) != EOF)
    { /*Check each character in file and print them out*/

        if ((ch != 'X') && (ch != 'O') && (ch != '\n')) /*Report error if they are neither X or O or newline*/
        {
            fprintf(stderr, "%s: bad character '%c' in line %d\n", argv[1], ch, *fileRows+1);
            exit(EXIT_FAILURE);
        }
        else
        {
            if (ch == '\n')
            { /*Check how many rows in file, as denoted by newline*/
                *fileRows += 1;
                prevCharCount = curCharCount;
                x += 1; /*Increment to new row*/
                y = 0;  /*Reset char counter for new row*/
            }
            else if (ch != '\0')
            { /*Only increase char count if char is not NULL*/
                y += 1;
                rowCharCount[x] = y;
                ++curCharCount;
                ++totalChars;
            }
        }
    }
    /*Checks pattern dimensions*/
    int k = 0;
    int l = rowCharCount[0]; /*Start by comparing to first row*/
    /*printf("Row Dimensions:\n");*/
    for (k; k < *fileRows; k++)
    {
        /*printf("%d ", rowCharCount[k]);*/
        if (rowCharCount[k] != l) /*Report error if prev vs current row counts do not match up*/
        {
            fprintf(stderr, "%s: line %d is wrong length\n", argv[1], k+1);
            /*printf("\nPrev Row %d VS Current Row %d | Invalid pattern dimensions, try again!\n", l, rowCharCount[k]);*/
            exit(EXIT_FAILURE);
        }
        l = rowCharCount[k]; /*Increment base case check to current row count*/
    }

    /**All clear, proceed with other stuff*/

    *fileCols = (totalChars / *fileRows); /*Divide by rows to get amount of chars per row*/

    /*printf("General INFO:  Row:%d ,Col:%d\n", *fileRows, *fileCols);*/

    fseek(patternFile, 0, SEEK_SET); /*Move pointer back to start of file*/

    while ((ch = fgetc(patternFile)) != EOF) /*While there's still chars left to scan, scan them all one by one*/
    {
        if (ch == '\n') /*Increment line if new line char found*/
        {
            i += 1; /*Increment row*/
            j = 0;  /*Reset column to 0 in prep for new row*/
        }
        else
        { /*If not null, add to array*/
            if (ch != '\0')
            {
                ((pattern[i][j])) = ch;
                j += 1;
            }
        }
    }
    fclose(patternFile); /*Close file after done reading*/
    /*printf("%s\n", pattern[2]);*/
}
/*
 * main routine
 */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s board_pattern\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    checkPattern(argc, argv, &fileRows, &fileCols);
    /*printf("%s\n", pattern[1]);*/
    int n = 0; /* number of numbers read */

    /*
	 * print the board
	 */

    prboard(fileRows, fileCols);

    /* done! */
    return (0);
}
