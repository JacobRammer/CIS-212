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
    double decimalPlace = .1;
    double fromStr = 0.0;
    // printf("string length of decimal is: %li\n", strlen(decimalStr));
    // printf("previous index is: %c\n", decimalStr[previousIndex]);
    // for (previousIndex; previousIndex < strlen(decimalStr); previousIndex++)
    while (decimalStr[previousIndex]  != '\0')
    {
        double convertDouble = (decimalStr[previousIndex] - '0') * decimalPlace;
        // printf("convertDouble is: %f\n", convertDouble);
        fromStr = (convertDouble * 10) + fromStr;
        previousIndex += 1;
        decimalPlace *= .1;
    }
    fromStr *= .1;
    // fromStr = convertDouble * .10;

    // printf("fromStr is: %f\n", fromStr);


    return fromStr;
}

double strToInt(char *str)
{
    double fromStr = 0.0;
    int negSign = 0; // 0 if false, 1 if true
    int i = 0;


    if (strlen(str) > 10)  // to large for data type
    {
        issueError();
    }

    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == '-')  // check for negative sign
        {
            negSign = 1;
            break;
        }

        if(str[i] > '9' || str[i] < '0')  // check for digits according to ascii val
        {
            
        }

        if (str[i] != '.')
        {
        int convertDouble = str[i] - '0';
        fromStr = (fromStr * 10) + convertDouble;
        }

        if (str[i] == '.')
        {
            double frac = convertFraction(i, str);
            // printf("!frac is :%f\n", frac);
            fromStr += frac;
            break;
        }
    }

    if (negSign == 1)
    {
        fromStr *= -1;
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
    printf("%.03f\n", intFromStr);
    return 0;
}