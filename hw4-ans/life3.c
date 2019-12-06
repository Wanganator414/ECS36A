/*
 * 2nd part of a game of life
 *
 * Draw the board
 *
 * Eric Wang, ECS 36A, Fall 2019
 * Answer to homework 3, question 4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int DBUG = 0;

/* board dimensions */
int cols = 100;
int rows = 100;

/*file info*/
int fileCols = 0;
int fileRows = 0;

/*global pattern record*/
char pattern[100][100];

/*temp pattern record*/
char tempPattern[100][100]; /*Set to max potential size*/

void copyPattern() /*Copy current pattern into temp pattern*/
{
    int r = 0, c = 0;
    if (DBUG)
    {
        printf("Copy from pattern to temp:\n");
    }
    for (; r < fileRows; r++)
    {
        for (; c < fileCols; c++)
        {
            if (DBUG)
            {
                printf("Temp:%c", tempPattern[r][c]);
            }
            tempPattern[r][c] = pattern[r][c];
            if (DBUG)
            {
                printf(" <-- Pat:%c ", pattern[r][c]);
                printf("\n");
            }
        }

        c = 0; /*Reset col index to front*/
    }
}

void copyTemp() /*Copy temp pattern into current pattern*/
{
    int r = 0, c = 0;
    if (DBUG)
    {
        printf("Copy from temp to pattern:\n");
    }
    for (; r < fileRows; r++)
    {
        for (; c < fileCols; c++)
        {
            if (DBUG)
            {
                printf("Pat:%c", pattern[r][c]);
            }
            pattern[r][c] = tempPattern[r][c];
            if (DBUG)
            {
                printf(" <-- Temp:%c ", tempPattern[r][c]);
                printf("\n");
            }
        }

        c = 0; /*Reset col index to front*/
    }
}

void checkCells(int row, int col)
{
    int top = 0, bot = 0, left = 0, right = 0;
    int topLeft = 0, topRight = 0, botLeft = 0, botRight = 0; /*These values are only truethy when both criteria are valid*/
    int liveCount = 0;

    /*Check if Cardinal directions have cells that exist MAYBE also CHECK FOR LIVE CELLS*/
    if (col - 1 >= 0) /*Check cell to the left to see if it is within bounds*/
    {
        left = 1;
        if (pattern[row][col - 1] == 'O')
        {
            ++liveCount;
            if (DBUG)
            {
                printf("L_POP: %d ", liveCount);
            }
        }
    }

    if (col + 1 <= fileCols - 1) /*Check cell to the right to see if in range of column size*/
    {
        right = 1;
        if (pattern[row][col + 1] == 'O')
        {
            ++liveCount;
            if (DBUG)
            {
                printf("R_POP: %d ", liveCount);
            }
        }
    }

    if (row - 1 >= 0)
    { /*Check cell on top to see if it is within bounds*/
        top = 1;
        if (pattern[row - 1][col] == 'O')
        {
            ++liveCount;
            if (DBUG)
            {
                printf("T_POP: %d ", liveCount);
            }
        }
    }

    if (row + 1 <= fileRows - 1)
    { /*Check if next row is exists or not*/
        bot = 1;
        if (pattern[row + 1][col] == 'O')
        {
            ++liveCount;
            if (DBUG)
            {
                printf("B_POP: %d ", liveCount);
            }
        }
    }

    topLeft = (top && left); /*Verrtical and horizontal criteria must be satisfied for the diagonal cells to be valid*/
    topRight = (top && right);
    botLeft = (bot && left);
    botRight = (bot && right);

    /*Once intercardinal directions are checked, look at their values*/
    if (topLeft)
    {
        if (pattern[row - 1][col - 1] == 'O')
        {
            ++liveCount;
            if (DBUG)
            {
                printf("TL_POP: %d ", liveCount);
            }
        }
    }

    if (topRight)
    {
        if (pattern[row - 1][col + 1] == 'O')
        {
            ++liveCount;
            if (DBUG)
            {
                printf("TR_POP: %d ", liveCount);
            }
        }
    }

    if (botLeft)
    {
        if (pattern[row + 1][col - 1] == 'O')
        {
            ++liveCount;
            if (DBUG)
            {
                printf("BL_POP: %d ", liveCount);
            }
        }
    }

    if (botRight)
    {
        if (pattern[row + 1][col + 1] == 'O')
        {
            ++liveCount;
            if (DBUG)
            {
                printf("BR_POP: %d ", liveCount);
            }
        }
    }
    if (DBUG)
    {
        printf("Cords (%d,%d):\t[%c]\tT:%d\tR:%d\tB:%d\tL:%d\ttR:%d\ttL:%d\tbL:%d\tbR:%d\tLiveCount: %d\n", row, col, pattern[row][col], top, right, bot, left, topRight, topLeft, botLeft, botRight, liveCount);
    }

    /* Add different choices for target cell if alive or dead*/

    if (pattern[row][col] == 'O') /*Check status if cell is populated*/
    {
        if ((liveCount < 2) || (liveCount > 3))
        { /*Swap value if too many or less live cells nearby */
            tempPattern[row][col] = 'X';
        }
        else if ((liveCount == 2) || (liveCount == 3))
        { /*If not, stay alive*/
            tempPattern[row][col] = 'O';
        }
        else
        {
            tempPattern[row][col] = 'X';
        }
    }

    if (pattern[row][col] == 'X') /*Check status if cell is not populated*/
    {
        if (liveCount == 3)
        { /*If dead cell is near exactly 3 live cells, swap it to be alive*/
            tempPattern[row][col] = 'O';
        }
        else
        { /*If not, stay dead*/
            tempPattern[row][col] = 'X';
        }
    }
}

void changeGen()
{
    int r = 0, c = 0;
    for (; r < fileRows; r++)
    {
        for (; c < fileCols; c++)
        {
            checkCells(r, c);
        }
        c = 0; /*Reset column index to front*/
    }
}

void prboard(int fileRows, int fileCols) /* draw the outline of the board*/
{
    int i = 0; /* counters in for loops */
    int x = 0; /*Cords for interior*/
    /* top border */
    for (i = 0; i < fileCols + 2; i++)
    {
        putchar('-');
    }
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
    {
        putchar('-');
    }
    putchar('\n');
}

void checkPattern(int argc, char **argv, int *fileRows, int *fileCols)
{
    /*Read pattern file from command line*/
    FILE *patternFile;
    int i = 0, j = 0, x = 0, y = 0;
    int curCharCount = 0;
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
            fprintf(stderr, "%s: bad character '%c' in line %d\n", argv[1], ch, *fileRows + 1);
            exit(EXIT_FAILURE);
        }
        else
        {
            if (ch == '\n')
            { /*Check how many rows in file, as denoted by newline*/
                *fileRows += 1;
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
    for (; k < *fileRows; k++)
    {
        /*printf("%d ", rowCharCount[k]);*/
        if (rowCharCount[k] != l) /*Report error if prev vs current row counts do not match up*/
        {
            fprintf(stderr, "%s: line %d is wrong length\n", argv[1], k + 1);
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

    /*Print Gen0-50 with 5 Gen gap*/
    int i = 0;
    for (; i <= 50; i++)
    {
        if (i % 5 == 0)
        {
            printf("Generation %d:\n", i);
            prboard(fileRows, fileCols); /*Print out current generation*/
        }
        copyPattern(); /*Copy over main pattern to temp pattern*/
        changeGen();   /*Advance new generation and change temp pattern*/
        copyTemp();    /*Copy over modified temp pattern back to main pattern*/
    }

    /* done! */
    return (0);
}
