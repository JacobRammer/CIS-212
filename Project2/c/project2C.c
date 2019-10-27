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
    while (decimalStr[previousIndex]  != '\0')
    {
        if (decimalStr[previousIndex] >= '0' && decimalStr[previousIndex] <= '9')
        {   
        double convertDouble = (decimalStr[previousIndex] - '0') * decimalPlace;
        fromStr = (convertDouble * 10) + fromStr;
        previousIndex += 1;
        decimalPlace *= .1;
        }else
        {
            issueError();
        }
    }
    fromStr *= .1;
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
    {        if (str[0] == '-')  // check for negative sign
        {
            negSign = 1;
        }
        int convertDouble = str[i] - '0';
        if((convertDouble >= 0 && convertDouble<= 10) || str[i] == '.' || str[i] == '-') 
        {
            if (str[i] != '.')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    {
                        
                        fromStr = (fromStr * 10) + convertDouble;
                    }         
            } 
            if (str[i] == '.')
            {
                double frac = convertFraction(i, str);
                fromStr += frac;
                break;
            }
        }else
        {
            issueError();
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
    double intFromStr = strToInt(argv[1]);
    printf("%.03f\n", intFromStr);
    return 0;
}
