/*
Jacob Rammer
*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

#define MAX 15
typedef struct
{
    int top;
    double stack[MAX];

}Stack;

void initialize(Stack *s)
{
    s->top = 0;
}

void Push(Stack *s, double x)
{
    
        s->stack[s->top] = x;
        s->top++;
        // printf("pushing %d\n", x)
}

double pop(Stack *s)
{
    // return s->stack[s->top--];  //This doesnt work???!
    (s->top)--;
    return s->stack[s->top];
}

void issueError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}

int isOperation(char operation)
{
    return (operation == '+' || operation == '-' || operation == '/' || operation =='x');
}


double doOperation(double intOne, double intTwo, char sign)
{
    // printf("1: %f, 2: %f\n", intOne, intTwo);
    // printf("sign is %c\n", sign);
    if (sign == '+')
    {
        // printf("plus return value:%f\n", intOne + intTwo);
        return (intOne + intTwo);
    }
    if (sign == '-')
    {
        // printf("Minus return value:%f\n", intOne - intTwo);
        return (intOne - intTwo);
    }
    if (sign == '/')
    {
        // printf("divide return value:%f\n", intOne / intTwo);
        return (intOne / intTwo);
    }
    if (sign == 'x')
    {
        // printf("times return value:%f\n", intOne * intTwo);
        return (intOne * intTwo);
    }
    return -1;
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
    Stack s;
    initialize(&s);
    double total = 0;
    double num = 0;
    double intOne = 0;
    double intTwo = 0;
    int i = 0;

    for(i = 1; i < argc; i++)
    {
        if(isOperation(*argv[i]))
        {
            intTwo = pop(&s);
            intOne = pop(&s);

            // calculate
            total = doOperation(intOne, intTwo, *argv[i]);
            // printf("after return %f\n", total);
            Push(&s, total);
        }else
        {
            num = strToInt(argv[i]);
            Push(&s, num);
        }
        
    }
    printf("The total is %.03f\n", total);
    return 0;
}
 