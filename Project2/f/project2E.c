#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Jacob Rammer
Project 2e
Please excuse the mess, i thought this was due
Thursday, not Wednesday.
*/

int allowedChars( int index, unsigned char *buff)
{
    /*
    An attempt to clean up the nasty chained if statements
    and just maybe fix my valgrind issues. But I don't have much confidence 
    Check the index for punctuation, new lines or null characters. 
    This verifies that the matched word is isolated
    */

    index ++;  // to check char ahead
    if (buff[index] == ' ' || buff[index] == '\0' || buff[index] == '\n' 
        || buff[index] == '.' || buff[index] == ',')
    {
         // printf("char at %d is: %c\n", index, buff[index]);
        return 1;
    }
    return 0;
}

int main (int argc, char *argv[])
{
    int arguments = 0; // will be used to count how mnay words we're finding
    int matchingWords = 0;  // Matched words with argv
    int matchedChars = 0; //  the number of matched chars. will compart to strlen
    int numArgs = argc - 2;
    int argIndex = 0;  // argv[0][argIndex]
    int offset = 1; // offset of checking previous char
    int *counts = malloc(numArgs * sizeof(int));
    int countsInd = 0;
    int lengthStr = 0;


    if (argc < 3)  // file name and at least 1 word not provided
    {
        printf("File and or word(s) not provided");
        exit(EXIT_FAILURE);
    }

    FILE *fName = fopen(argv[1], "r");
    if (fName == NULL)  // error catch on invalid file
    {
        printf("\"<%s>\" is not a valid file", argv[1]);
        exit(EXIT_FAILURE);
    }

    fseek(fName, 0, SEEK_END);  // set pointer to end of the file
    int numBytes = (ftell(fName) + 1);  // see how much the pointer has moved
    // printf("Number of bytes in fName is %d\n", numBytes);
    unsigned char *buff = malloc(numBytes);  // will be the value of how much the pointer moved
    fseek(fName, 0, SEEK_SET);  // set pointer to the beginning of the file
    fread(buff, sizeof(unsigned char), numBytes, fName);  // where to store, size of data, how much, from?
    fclose(fName);

    arguments = argc - 1;
    char * args;
    for (int args = 2; args != argc; args++)
    {
        lengthStr = strlen(argv[args]);
        // printf("argv %s\n", argv[args]);
        argIndex = 0;
        int maxArgIndex = strlen(argv[args]);
        // printf("arg lengh is: %d\n", maxArgIndex);
        for (int q = 0; q < numBytes; q++)
        {
            if (argIndex > maxArgIndex)
                argIndex = 0;
            if (buff[q] == argv[args][argIndex])
            {
                // allowedChars(q, buff);
                matchedChars ++;
                argIndex ++;
                offset ++;
                if ((matchedChars == lengthStr) && (allowedChars(q, buff) == 1))
                {
                    if ((q - 1) != 0)
                    { 
                        if (allowedChars((q - offset) -1, buff) == 1)  // -1 for incrimenting in allowedchars
                        {
                            matchingWords++;
                            counts[countsInd] ++;
                            argIndex = 0;
                            matchedChars = 0;
                            offset = 0;
                            if (q == numBytes - 1)
                                break;
                        }
                    }
                    if ((q - 1) == 0)
                    {
                        if (allowedChars(q, buff))
                        {
                            matchingWords++;
                            counts[countsInd] ++;
                            argIndex = 0;
                            matchedChars = 0;
                            if (q == numBytes - 1)
                                break;
                        }
                    }
                }
            }
            if (allowedChars(q - 1, buff) == 1 || allowedChars(q, buff) == 1)
            {
                matchedChars = 0;
                argIndex = 0;
                offset = 0;
            }
        }
        countsInd++;
    }

    countsInd = 0;
    for (int idk= 2; idk < argc; idk++)
    {
        printf("The word \"%s\" occurs %d times.\n", argv[idk], counts[countsInd]);
        countsInd++;
    }

    free(buff);
    free(counts);
    return 0;
}