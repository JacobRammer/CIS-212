/*
Jacob Rammer
*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

void issueError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}

double strToInt(char *str)
{
    double fromStr = 0.0;
    int negSign = 0; // 0 if false, 1 if true
    int i = 0;

    if (str[0] == '-')  // check for negative sign
    {
        negSign = 1;
    }

    if (strlen(str) > 10)
    {
        issueError();
    }

    for (i = 0; i < strlen(str); i++)
    {
        int tenVal = 1;
        printf("str[%d] is: %c\n", i, str[i]);
        int test = str[i] - '0';
        printf("test is %d\n", test * 1);
        printf("test 2 is %d\n", test * tenVal);
        tenVal *= 10;
        fromStr = (fromStr * 10) + test;
        printf("fromStr is: %f\n", fromStr);
    }

    return fromStr;
}
int main(int argc, char *argv[]) 
{
    // int test = strlen(argv[1]);
    // printf("main is %d", test);
    if (argv[1] == '\0')
    {
        issueError();
    }
    double intFromStr = strToInt(argv[1]);
    // printf("%.03f\n", intFromStr);
    return 0;
}