#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Jacob Rammer
Project 2e
Please excuse the mess, i thought this was due
Thursday, not Wednesday
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

    // for (int i = 0; i <= numBytes; i++)
    //     printf("test: %c\n", buff[i]);

    // char test[6] = "hello";
    // for(int j = 0; j < 5; j ++)
    //     printf("test[j] is: %c\n", test[j]);

    arguments = argc - 1;
    char * args;
    // printf("# of arguments is: %d\n", arguments);
    // for (int k = 2; k <= arguments; k++)
    // {
    //     printf("argv is : %s\n", argv[k]);
    //     int comp = strcmp("test", argv[k]);
    //     if (comp == 0)
    //         // printf("Strings test and %s are the same\n", argv[k]);
    //         printf("test:%c\n", argv[k][0]);  // will print the first character of argv
    // }

/*
need to have arg[v] index logic
*/
    // printf("len of argv[2] is: %lu\n", strlen(argv[2]));
    // int tempvar3 = strlen(argv[]);
    // printf("tempvar3 is: %d, numbytes is: %d\n", tempvar3, numBytes);
    // printf("argv[2][0] is: %c\n", argv[2][0]);
    for (int args = 2; args != argc; args++)
    {
        // printf("argv %s\n", argv[args]);
        argIndex = 0;
        int maxArgIndex = strlen(argv[args]);
        // printf("arg lengh is: %d\n", maxArgIndex);
        for (int q = 0; q < numBytes; q++)
        {
            // printf("buff q is:%c, argv is %c\n", buff[q], argv[args][argIndex]);
            if (argIndex > maxArgIndex)
                argIndex = 0;
            if (buff[q] == argv[args][argIndex])
            {
                // printf(" %c\n", argv[args][argIndex]);
                // printf("Matched char %c to %c.\n", buff[q], argv[args][argIndex]);
                matchedChars ++;
                argIndex ++;
                offset ++;
                // printf("matched number of chars is: %d\n", matchedChars);
                if ((matchedChars == strlen(argv[args])) && (buff[q + 1] == ' ' || buff[q + 1] == '\0' || buff[q + 1] == '\n' 
                || buff[q + 1] == '.' || buff[q + 1] == ','))
                {
                    if ((q - 1) != 0)
                    {
                        if (buff[q - offset] == ' ' || buff[q - offset] == '\n' || buff[q - offset] == '\0')
                        {
                            // printf("Matched char %c to %c\n", buff[q], argv[args][argIndex]);
                            // printf("matched number of chars is: %d\n", matchedChars);
                            matchingWords++;
                            // printf("! Index is %d\n", countsInd);
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
                            // printf("Matched char %c to %c\n", buff[q], argv[args][argIndex]);
                            // printf("matched number of chars is: %d\n", matchedChars);
                            matchingWords++;
                            // printf("? Index is %d\n", countsInd);
                            counts[countsInd] ++;
                            argIndex = 0;
                            matchedChars = 0;
                        }
                    }
                }
            }
            // if ((matchedChars == tempvar3) && (buff[q+1] == ' ' || buff[q+1] == '\0'|| buff[q+1] == '\n' || buff[q+1] == '.'))
            // {
            //     printf("Matched char %c to %c\n", buff[q], argv[args][argIndex]);
            //     printf("matched number of chars is: %d\n", matchedChars);
            //     matchingWords++;
            //     argIndex = 0;
            //     matchedChars = 0;
            // }
            if (buff[q] == ' ' || buff[q+1] == '\n' || buff[q+1] == '\0' || buff[q] == '\n')
            {
                matchedChars = 0;
                argIndex = 0;
                offset = 0;
            }
        }
        // printf("The word \"%s\" occurs %d times.\n", argv[args], matchingWords);
        countsInd++;
    }

    // counts[1] = 1;
    countsInd = 0;
    // printf("the strlen of buff is: %d\n", numBytes);
    for (int idk= 2; idk < argc; idk++)
    {
        printf("The word \"%s\" occurs %d times.\n", argv[idk], counts[countsInd]);
        countsInd++;
    }

    // printf("matching words: %d\n", matchingWords);
    free(buff);
    free(counts);
    return 0;
}