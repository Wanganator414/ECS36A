#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 0 /*General purpose debug switch*/

int returnIndex = 0;  /*Global variable for keeping track of how many individual elements are found in a compound*/
int invalidInput = 0; /*Global variable boolean to keep track if a user input is invalid or not*/

struct chemical /*Data structure to store info on an element's atomic weight*/
{
    double weight;
    char symbol[2];
};

struct chemArray /*Data structure to store information on all 118 elements*/
{
    struct chemical elements[118];
};

struct element /*Custom structure to hold an individual element and its amount occurrence in a compound*/
{
    int count;
    char symbol[2];
};

struct compoundStruct /*Custom structure to hold a lot of elements and the amounts by which they appear, symbolizes a compound*/
{
    struct element elements[118];
};

struct chemArray getInput(int argc, char **argv)    /*Method to process user input and organize the information into previously declared structs*/
{
    struct chemArray arr;

    FILE *fileStream;

    int line = 0;
    int tempNum = 0;

    fileStream = fopen(argv[argc - 1], "rw");

    if (fileStream == NULL) /*Error opening file by filename, return 1 as error*/
    {
        perror(argv[argc - 1]);
        exit(EXIT_FAILURE);
    }

    while ((tempNum = fscanf(fileStream, "%lf\t%s\t%*s", &arr.elements[line].weight, &arr.elements[line].symbol)) != EOF) /*'%*s' ignores last item in input and moves file pointer forward*/
    {
        if (tempNum == 0) /*If the line for the element in the element file is malformed, print the following*/
        {
            /*printf("Items in the line: %d\n", tempNum);*/
            fprintf(stderr, "%s: malformed line %d\n", argv[argc - 1], line);
            exit(EXIT_FAILURE);
        }

        ++line;
    }

    if (line == 0)
    { /*File is empty, return error code 1*/
        fprintf(stderr, "%s: no atomic weights there!\n", argv[argc - 1]);
        exit(EXIT_FAILURE);
    }

    fclose(fileStream);
    return arr;
}

struct compoundStruct breakDown(struct chemArray dict, char *compound)  /*Method to take */
{
    struct compoundStruct returnValue;
    int i;
    int len;
    /*strtok()*/
    i = 0;
    len = strlen(compound); /*Length of compound not adjusted for index*/

    if (DEBUG)
    {
        printf("Len of Comp:%d\n", len);
        printf("Compound %s is consisted of:\n", compound);
    }
    while (i < len)
    {
        if (DEBUG)
        {
            printf("%d->%c\n", i, compound[i]);
        }

        if ((i - 1 >= 0) && isdigit(compound[i - 1]) && islower(compound[i]))
        {
            printf("Invalid Input!\n");
            invalidInput = 1;
            break;
        }

        if ((i - 1 >= 0) && islower(compound[i]) && islower(compound[i - 1]))
        {
            printf("Invalid Input!\n");
            invalidInput = 1;
            break;
        }

        if ((i + 2 >= 0) && isdigit(compound[i]) && isdigit(compound[i + 1]) && isdigit(compound[i + 2]))
        {
            printf("Invalid Input!\n");
            invalidInput = 1;
            break;
        }
        if (isdigit(compound[0]))
        {
            printf("Invalid Input!\n");
            invalidInput = 1;
            break;
        }

        if (isalpha(compound[i]) && isupper(compound[i])) /*Caps letter found, at least single letter element found*/
        {
            if ((i + 1 < len) && isalpha(compound[i + 1]) && (islower(compound[i + 1]))) /*Next letter is lowercase, so double letter at least*/
            {

                if ((i + 4 < len) && isdigit(compound[i + 4]) && isdigit(compound[i + 3]) && isdigit(compound[i + 2])) /*If double letter and has 3rd digit #*/
                {
                    returnValue.elements[returnIndex].symbol[0] = compound[i];
                    returnValue.elements[returnIndex].symbol[1] = compound[i + 1];
                    returnValue.elements[returnIndex].symbol[2] = '\0'; /*Make sure we don't get weird memory leftovers from prior use*/
                    if (DEBUG)
                        printf("D3 %s\n", returnValue.elements[returnIndex].symbol);
                    char temp[3];
                    temp[0] = compound[i + 2];
                    temp[1] = compound[i + 3];
                    temp[2] = compound[i + 4];
                    returnValue.elements[returnIndex].count = atoi(temp);
                    /*printf("DIGITS: %d\n", atoi(temp));*/
                    ++returnIndex;
                    i += 5; /*Increment search*/
                }

                else if ((i + 3 < len) && isdigit(compound[i + 3]) && isdigit(compound[i + 2])) /*Double letter with 2 follow up digits*/
                {
                    returnValue.elements[returnIndex].symbol[0] = compound[i];
                    returnValue.elements[returnIndex].symbol[1] = compound[i + 1];
                    returnValue.elements[returnIndex].symbol[2] = '\0'; /*Make sure we don't get weird memory leftovers from prior use*/
                    if (DEBUG)
                        printf("D2 %s\n", returnValue.elements[returnIndex].symbol);
                    char temp[2];
                    temp[0] = compound[i + 2];
                    temp[1] = compound[i + 3];
                    returnValue.elements[returnIndex].count = atoi(temp);
                    ++returnIndex;
                    i += 4; /*Increment search*/
                }

                else if ((i + 2 < len) && isdigit(compound[i + 2])) /*Double letter with 1 followup digit*/
                {
                    returnValue.elements[returnIndex].symbol[0] = compound[i];
                    returnValue.elements[returnIndex].symbol[1] = compound[i + 1];
                    returnValue.elements[returnIndex].symbol[2] = '\0'; /*Make sure we don't get weird memory leftovers from prior use*/
                    returnValue.elements[returnIndex].count = compound[i + 2] - '0';
                    if (DEBUG)
                        printf("D1 %s\n", returnValue.elements[returnIndex].symbol);
                    ++returnIndex;
                    i += 3; /*Increment search*/
                }
                else /*Double letter element with no followup number*/
                {
                    returnValue.elements[returnIndex].symbol[0] = compound[i];
                    returnValue.elements[returnIndex].symbol[1] = compound[i + 1];
                    returnValue.elements[returnIndex].symbol[2] = '\0'; /*Make sure we don't get weird memory leftovers from prior use*/
                    if (DEBUG)
                        printf("D0 %s\n", returnValue.elements[returnIndex].symbol);
                    returnValue.elements[returnIndex].count = 1;
                    ++returnIndex;
                    i += 2; /*Increment element length*/
                }
            }

            else if ((i + 3 < len) && isdigit(compound[i + 3]) && isdigit(compound[i + 2]) && isdigit(compound[i + 1])) /*If SINGLE letter and has TRIPLE digit #*/
            {
                returnValue.elements[returnIndex].symbol[0] = compound[i];
                returnValue.elements[returnIndex].symbol[1] = '\0';
                if (DEBUG)
                    printf("S3 %s\n", returnValue.elements[returnIndex].symbol);
                char temp[3];
                temp[0] = compound[i + 1];
                temp[1] = compound[i + 2];
                temp[2] = compound[i + 3];
                returnValue.elements[returnIndex].count = atoi(temp);
                /*printf("DIGITS: %d\n", atoi(temp));*/
                ++returnIndex;
                i += 4; /*Increment search*/
            }
            else if ((i + 2 < len) && isdigit(compound[i + 2]) && isdigit(compound[i + 1])) /*SINGLE letter element with DOUBLE follow up #s*/
            {
                returnValue.elements[returnIndex].symbol[0] = compound[i];
                returnValue.elements[returnIndex].symbol[1] = '\0';
                if (DEBUG)
                    printf("S2 %s\n", returnValue.elements[returnIndex].symbol);
                char temp[2];
                temp[0] = compound[i + 1];
                temp[1] = compound[i + 2];
                returnValue.elements[returnIndex].count = atoi(temp);
                /*printf("DIGITS: %d\n", atoi(temp));*/
                ++returnIndex;
                i += 3; /*Increment search*/
            }

            else if ((i + 1 < len) && isdigit(compound[i + 1])) /*SINGLE letter, SINGLE number follow up*/
            {
                returnValue.elements[returnIndex].symbol[0] = compound[i];
                returnValue.elements[returnIndex].symbol[1] = '\0';
                if (DEBUG)
                    printf("S1 %s\n", returnValue.elements[returnIndex].symbol);
                returnValue.elements[returnIndex].count = compound[i + 1] - '0';
                /*printf("DIGITS: %d\n", compound[i + 1] - '0');*/
                ++returnIndex;
                i += 2; /*Increment search*/
            }
            else /*A single NO follow up element is found*/
            {
                returnValue.elements[returnIndex].symbol[0] = compound[i];
                returnValue.elements[returnIndex].symbol[1] = '\0';
                if (DEBUG)
                    printf("S0 %s\n", returnValue.elements[returnIndex].symbol);
                returnValue.elements[returnIndex].count = 1;
                ++returnIndex;
                i += 1; /*Increment by single letter*/
            }
        }
        else
        {
            printf("%s Invalid Input\n", compound[0]);
            exit(EXIT_FAILURE);
        }
    }
    return returnValue;
}


void getWeight(struct compoundStruct compound, struct chemArray info, char **compoundName)  /*Takes in custom struct and calculates weight value based on quantity of individual elements in a compound*/
{
    if (invalidInput)
    {
        exit;
    }
    int i = 0;
    int j = 0;
    double totalWeight = 0.00;
    int indLeng = returnIndex;
    int validElement = 0;
    for (; i < indLeng; i++)    /*Keep checking until the amount of individual elements in the compound runs out*/
    {
        if (DEBUG)
        {
            printf("Element: %s Count: %d\n", compound.elements[i].symbol, compound.elements[i].count);
        }
        validElement = 0;
        for (; j < 118; j++)
        {
            if (strcmp(info.elements[j].symbol, compound.elements[i].symbol) == 0)
            {
                if (DEBUG)
                {
                    printf("Data %s\t|\tInput %s\n", (info.elements[j].symbol), (compound.elements[i].symbol));
                    printf("Added weight: %lf X %lf=%lf\n", info.elements[j].weight, (double)(compound.elements[i].count), (info.elements[j].weight) * (compound.elements[i].count));
                }
                totalWeight += ((info.elements[j].weight) * (double)(compound.elements[i].count));
                validElement = 1;
                if (DEBUG)
                {
                    printf("Element Validity of %s: %d\n", compound.elements[i].symbol, validElement);
                }
            }
        }

        if (validElement == 0) /*If invalid character/element/input found, end loop and prompt user for next compound*/
        {
            fprintf(stderr, "%s: no such element\n", compound.elements[i].symbol);
            fprintf(stderr, "%s: not a valid compound\n", compoundName);
            validElement = 0;
            break;
        }
        j = 0;
    }
    if (strlen(compoundName) != 0 && validElement && invalidInput == 0)
    {
        printf("The atomic weight of %s is %0.2f\n", compoundName, totalWeight);
    }
    invalidInput = 0;
    returnIndex = 0;
}

int main(int argc, char **argv) /*Main driver to call previously created functions*/
{
    int bufsize;
    char *compound;
    struct chemArray info;
    bufsize = 100;
    compound = (char *)malloc(bufsize);
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s weightsfile\n", argv[argc - 1]);
        exit(EXIT_FAILURE);
    }
    if (compound == NULL)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    info = getInput(argc, argv); /*Read in file with info about each atomic weight*/

    printf("Chemical composition? ");
    while (fgets(compound, bufsize, stdin)) /*Keep doing the user's bidding until EOF signal*/
    {
        int len = strlen(compound);           /* get buf length */
        if (len && compound[len - 1] == '\n') /* check last char is '\n' */
        {
            compound[--len] = 0; /* overwrite with nul-character */
        }

        getWeight(breakDown(info, compound), info, compound); /*Break down user input to managable portions*/

        printf("Chemical composition? ");
    }
    printf("\n");

    return 0;
}
