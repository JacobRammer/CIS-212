#include <stdlib.h>
#include <stdio.h>

/*
Jacob Rammer
Project 2g
*/

int main(int argc, char *argv[])
{
    int r = 0;
    int seekIndex = 0;
    if (argc < 3)
    {
        printf("File(s) not provided.\n");
        exit(EXIT_FAILURE);
    }

    FILE *binFile = fopen(argv[1], "rb");
    if (binFile == NULL)
    {
        printf("%s is not a valid file", argv[1]);
    }

    FILE *txtFile = fopen(argv[2], "w+");
    if (txtFile == NULL)
    {
        printf("%s is not a valid file name.\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    while (seekIndex <= 36)
    {
        for (int i = 0; i < 4; i++)
        {
            fread(&r, sizeof(int), 1, binFile);
            fprintf(txtFile, "%d\n", r);
        }
        seekIndex += 12;
        fseek(binFile, sizeof(int) * seekIndex, SEEK_SET);
    }

    fclose(txtFile);
    fclose(binFile);
    return 0;
}