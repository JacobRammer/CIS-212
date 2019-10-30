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

    if (argc < 2)  // file name and at least 1 word not provided
    {
        printf("File and word(s) not provided");
        exit(EXIT_FAILURE);
    }

    FILE *fName = fopen(argv[1], "r");
    if (fName == NULL)  // error catch on invalid file
    {
        printf("<\"%s\"> is not a valid file", argv[1]);
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

    char test[6] = "hello";
    for(int j = 0; j < 5; j ++)
        printf("test[j] is: %c\n", test[j]);

    arguments = argc - 1;
    char * args;
    printf("# of of arguments is: %d\n", arguments);
    for (int k = 2; k <= arguments; k++)
    {
        // printf("argv is : %s\n", argv[k]);
        int comp = strcmp("test", argv[k]);
        if (comp == 0)
            printf("Strings test and %s are the same\n", argv[k]);
            printf("test:%c\n", argv[k][0]);  // will print the first character of argv
    }


    free(buff);
    return 0;
}