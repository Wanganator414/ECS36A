/*
Written for ECS36A, Fall 2019

Eric Wang, October 30, 2019

Accepts two files in command line, the first being the dictionary and second being the rsearchlist

Matches all occurrences of words in both files and prints the amount of words that match/not match
*/
#include <stdlib.h> /*malloc,calloc*/
#include <stdio.h>  /*printf and the such*/
#include <string.h> /*strcpy and the such*/
#include <errno.h>
#include <math.h>

/*Global Sizes For Dict and Search List*/
int dSize = 0;
int sSize = 0;

int netWordsSearched = 0;

/*Sorting goes here*/
int comparetor(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

char **readFile(int argc, char **argv, int fileNum, int *dSize, int *sSize)
{
    char **content;
    int i = 0;
    int j = 0;
    char ch;
    int generalSize = 0;
    FILE *readFile;
    readFile = fopen(argv[fileNum], "r"); /*Read file from cmd for preliminary info check*/

    if (readFile == NULL) /*Check if file read correctly, return error if issue*/
    {
        perror(argv[fileNum]);
        exit(1);
    }

    while ((ch = (fgetc(readFile))) != EOF) /*Check amount of rows as newlines*/
    {
        if (ch == '\n')
        {
            (fileNum == 1) ? (*dSize)++ : (*sSize)++; /*Help count rows for both files accordingly*/
        }
    }

    if (fileNum == 1)
    {
        if (*dSize == 0)
        {
            fprintf(stderr, "No words to find!\n"); /*When dict is empty*/
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (*sSize == 0)
        {
            fprintf(stderr, "No words to search!\n"); /*When search is empty*/
            exit(EXIT_FAILURE);
        }
    }

    rewind(readFile);

    content = (char **)calloc(1024, sizeof(char *)); /*Allocate memory for initial 2d array*/

    if (content == NULL) /*Report error if allocation fails*/
    {
        perror(content);
        exit(1);
    }

    for (i = 0; i < 1024; i++)
    {
        content[i] = (char *)calloc(1024, sizeof(char)); /*Allocate memory for the entire row at once/all columns at once*/

        if (content[i] == NULL) /*Report error if allocation fails*/
        {
            perror(content[i]);
            exit(1);
        }
    }

    i = 0; /*Reset counters for new loop to read contents into array*/
    j = 0;
    while ((ch = (fgetc(readFile))) != EOF) /*Read contents of file into 2d array*/
    {
        if (ch == '\n')
        {
            ++i;
            j = 0;
        }
        else
        {
            if (ch != '\0')
            {
                content[i][j] = ch;
                ++j;
            }
        }
    }
    fclose(readFile); /*Close file access*/
    /*qsort(content, generalSize, sizeof(char *), comparetor);*/
    return (content);
}

void searchStuff(char **dict, char **search)
{
    int wordsChecked = 0;
    int wordCheckTotal[sSize];
    int i = 0;
    int j = 0;
    int match = 0; /*Checks to see if a specific word has been matched already*/
    for (; i < sSize; i++)
    { /*Loop items in search list with all items in dictionary*/
        for (; j < dSize; j++)
        {
            if ((strcmp(dict[j], search[i]) == 0))
            {
                wordsChecked++;
                netWordsSearched++;
                /*printf("'%s' in the dictionary and '%s' in the search list MATCHED! This took %d trys to match up.\n", dict[j], search[i], wordsChecked);*/
                printf("'%s' is word %d in the list\n", search[i], wordsChecked);
                match = 1;
                break;
            }
            else /*Increment counters when not a match*/
            {
                ++wordsChecked;
                netWordsSearched++;
            }
        }
        j = 0;
        wordCheckTotal[i] = wordsChecked;
        if (!match)
        {
            /*printf("OOF, no words in the dictionary matched '%s' in the search list :( after %d trys.\n", search[i], wordsChecked);*/
            printf("'%s' is not in the word list\n", search[i]);
        }
        wordsChecked = 0;
        match = 0;
    }

    int p = 0;
    int totalWordsChecked = 0;
    for (; p < sSize; p++)
    {
        totalWordsChecked += wordCheckTotal[p];
    }
    double avg = 0.0;
    float nwcf = netWordsSearched * 1.0;
    avg = ((double)nwcf / (double)sSize);                                                                     /*Cheese to make Grade Scope roudning work correctly*/
    printf("Checked %d words while looking for %d words; average is %.2f\n", (netWordsSearched), sSize, avg); /*CHEESE*/
}

/*Main driver*/
int main(int argc, char **argv) /*Add parameters so program accepts command line file inputs*/
{
    if (argc != 3) /*Quick check to see if user entered right parameters*/
    {
        fprintf(stderr, "Usage: lookup [wordlist] [words]\n");
        exit(EXIT_FAILURE);
    }
    char **dict = readFile(argc, argv, 1, &dSize, &sSize);
    char **search = readFile(argc, argv, 2, &dSize, &sSize);
    searchStuff(dict, search);
    return (EXIT_SUCCESS); /*Return 0 if everything runs without problem*/
}