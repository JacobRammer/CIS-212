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

double convertFraction(int previousIndex, char *decimalStr)
{
    previousIndex += 1;
    double fromStr = 0.0;
    // printf("string length of decimal is: %li\n", strlen(decimalStr));
    // printf("previous index is: %c\n", decimalStr[previousIndex]);
    // for (previousIndex; previousIndex < strlen(decimalStr); previousIndex++)
    while (decimalStr[previousIndex]  != '\0')
    {
        double convertDouble = decimalStr[previousIndex] - '0';
        printf("convertDouble is: %f\n", convertDouble);
        previousIndex += 1;
    }
    // fromStr = convertDouble * .10;

    printf("fromStr is: %f\n", fromStr);


    return fromStr;
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

    if (strlen(str) > 10)  // to large for data type
    {
        issueError();
    }

    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] != '.')
        {
        int convertDouble = str[i] - '0';
        fromStr = (fromStr * 10) + convertDouble;
        }

        if (str[i] == '.')
        {
            double frac = convertFraction(i, str);
            fromStr += frac;
            // printf("frac is :%f\n", frac);
            break;
        }
    }

    return fromStr;
}
int main(int argc, char *argv[]) 
{
    if (argv[1] == '\0')  // check for empty string
    {
        issueError();
    }

    double intFromStr = strToInt(argv[1]);
    // printf("%.03f\n", intFromStr);
    return 0;
}