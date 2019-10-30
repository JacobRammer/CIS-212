#include <stdio.h>
#include <stdio.h>

int main()
{
    FILE * fName;
    fName = fopen("read", "r");

    char singleLine[150];

    while (!feof(fName))
    {
        fgets(singleLine, 150, fName);
        puts(singleLine);
    }

    fclose(fName);
    return 0;
}