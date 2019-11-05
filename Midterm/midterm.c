#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stringCopy()
{
    char str[12] = "hello world";
    char str2[6], str3[7];
    strcpy(str2, str+strlen("hello "));
    strncpy(str3, str, strlen("hello "));
    printf("%s, %s\n", str2, str3);
}


void fileRead()
{
    FILE *fIn = fopen("testFile.txt", "a+"); // append starts pointer at end of file a+ starts at beginning
    fseek(fIn, 0, SEEK_END);
    int numBytes = ftell(fIn);
    unsigned char *buffer = malloc(numBytes);
    char *newStr = "\nThis is the new string";
    fseek(fIn, 0, SEEK_SET);

    fread(buffer, sizeof(unsigned char), numBytes, fIn);
    printf("The number of bytes in fIn is: %d\n", numBytes);
    printf("The whole file string is: %s.\n", buffer);

    // now going to re-write the file
    fwrite(newStr, sizeof(char), strlen(newStr), fIn);
    fclose(fIn);
    free(buffer);

    FILE *fInNew = fopen("testFile.txt", "r");
    fseek(fInNew, 0, SEEK_END);
    int numBytesNew = ftell(fInNew);
    unsigned char *bufferNew = malloc(numBytesNew);
    fseek(fInNew, 0, SEEK_SET);
    fread(bufferNew, sizeof(unsigned char), (numBytesNew + strlen(newStr)), fInNew);
    printf("the size of buffernew is %d\n", numBytesNew);

    // read the elements of the buffer
    printf("\nFile contents by iteration\n");
    for (int i = 0; i < (numBytes + strlen(newStr)); i++)
        printf("%c", bufferNew[i]);

    fclose(fInNew);
    free(bufferNew);
    char test = 'b';
    printf("\nsize of unsigned chars are %lu\n", sizeof(unsigned char));
    printf("size of chars are %lu\n", sizeof(char));
    printf("test is %c", test);
}


int main()
{
    // fileRead();
    stringCopy();
    return 0;
}