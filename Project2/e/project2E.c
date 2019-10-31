#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Jacob Rammer
Project 2e
Please excuse the mess, i thought this was due
Thursday, not Wednesday.
*/

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

    fseek(fName, 0, SEEK_END);
    int numBytes = ftell(fName);
    // printf("Number of bytes in fName is %d\n", numBytes);
    unsigned char *buff = malloc(numBytes);
    fseek(fName, 0, SEEK_SET);
    fread(buff, sizeof(unsigned char), numBytes, fName);
    fclose(fName);

    arguments = argc - 1;
    char * args;
    for (int args = 2; args != argc; args++)
    {
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
                matchedChars ++;
                argIndex ++;
                offset ++;
                if ((matchedChars == strlen(argv[args])) && (buff[q + 1] == ' ' || buff[q + 1] == '\0' || buff[q + 1] == '\n' 
                || buff[q + 1] == '.' || buff[q + 1] == ','))
                {
                    if ((q - 1) != 0)
                    {
                        if (buff[q - offset] == ' ' || buff[q - offset] == '\n' || buff[q - offset] == '\0')
                        {
                            matchingWords++;
                            counts[countsInd] ++;
                            argIndex = 0;
                            matchedChars = 0;
                            offset = 0;
                        }
                    }
                    if ((q - 1) == 0)
                    {
                        if (buff[q + 1] == ' ' || buff[q + 1] == '\0' || buff[q + 1] == '\n' || buff[q + 1] == '.'
                            || buff[q + 1] == ',')
                        {
                            matchingWords++;
                            counts[countsInd] ++;
                            argIndex = 0;
                            matchedChars = 0;
                        }
                    }
                }
            }
            if (buff[q] == ' ' || buff[q+1] == '\n' || buff[q+1] == '\0' || buff[q] == '\n')
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