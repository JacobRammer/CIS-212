#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Jacob Rammer
Project 2e
*/

int main (int argc, char *argv[])
{
    int arguments = 0; // will be used to count how mnay words we're finding
    int counter = 0;  // will check to see if matched charaters are same length
    int matchingWords = 0;  // Matched words with argv
    int matchedChars = 0; //  the number of matched chars. will compart to strlen

    if (argc < 2)  // file name and at least 1 word not provided
    {
        printf("File and word(s) not provided");
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
    printf("Number of bytes in fName is %d\n", numBytes);
    unsigned char *buff = malloc(numBytes);
    fseek(fName, 0, SEEK_SET);
    fread(buff, sizeof(unsigned char), numBytes, fName);

    // for (int i = 0; i <= numBytes; i++)
    //     printf("test: %c\n", buff[i]);

    // char test[6] = "hello";
    // for(int j = 0; j < 5; j ++)
    //     printf("test[j] is: %c\n", test[j]);

    arguments = argc - 1;
    char * args;
    printf("# of of arguments is: %d\n", arguments);
    for (int k = 2; k <= arguments; k++)
    {
        // printf("argv is : %s\n", argv[k]);
        int comp = strcmp("test", argv[k]);
        if (comp == 0)
            // printf("Strings test and %s are the same\n", argv[k]);
            printf("test:%c\n", argv[k][0]);  // will print the first character of argv
    }

    // printf("len of argv[2] is: %lu\n", strlen(argv[2]));

    char test1[5] = "test";
    for (int q = 0; q != numBytes; q++)
    {
        char tempvar1 = buff[q];
        char tempvar2 = argv[2][q];
        int tempvar3 = strlen(argv[2]) - 1;
        if (test1[q] == argv[2][q])
        {
            printf("Matched char %c to %c.\n", buff[q], argv[2][q]);
            matchedChars ++;
        }else
        {
            // printf("Strings don't match. Test is: %s, argv is: %s\n", test1, argv[2]);
            matchedChars = 0;
            counter = 0;
        }
        if (buff[q] == '\n'&& matchedChars == 4)
        {
            matchingWords ++;
            printf("matching words: %d\n", matchingWords);
        }
    }

    // printf("the strlen of buff is: %d\n", numBytes);


    free(buff);
    return 0;
}