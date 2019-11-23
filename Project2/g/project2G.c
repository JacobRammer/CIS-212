#include <stdlib.h>
#include <stdio.h>

/*
Jacob Rammer
Project 2g
*/

int readRow(int index, int *buff, FILE *txtFile)
{
    for(int i = 0; i < 4; i++)
    {
        fprintf(txtFile, "%d\n", buff[index]);
        index ++;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    int *buff = malloc(sizeof(int) * 48);  // don't need to read the whole thing
   int index = 0;
   if (argc < 3)
    {
        printf("File(s) not provided.\n");
        exit(EXIT_FAILURE);
    }

    FILE *binFile = fopen(argv[1], "rb");
    if (binFile == NULL)
    {
        printf("%s is not a valid file", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE *txtFile = fopen(argv[2], "w+");
    fread(buff, sizeof(int), 49, binFile);
    
    for(int i = 0; i < 4; i++)
    {
        readRow(index, buff, txtFile);
        index += 12;
    }

    free(buff);
    fclose(txtFile);
    fclose(binFile);
    return 0;
}