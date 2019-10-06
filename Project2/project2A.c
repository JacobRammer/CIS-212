/*
Jacob Rammer 
Project 2a
*/

#include <stdio.h>

int main() {
    int value, div_one, div_two;
    int max_val = 500;
    // int max_val = 2;

    for (value = 15; value <= max_val; value++) 
    {
        for (div_one = 1; div_one <= value; div_one++)
        {
            for (div_two = 2; div_two <= div_one; div_two++)
            {
                if (div_one * div_two == value) 
                {
                    if (value % 2 == 1) // if it's odd
                    {
                        printf("%d is a composite number.\n", value);
                        value ++;
                    }
                }
            }
        }
    }
}