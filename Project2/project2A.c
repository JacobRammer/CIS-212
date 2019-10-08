/*
Jacob Rammer 
Project 2a
*/

#include <stdio.h>

int main() {
    int value, div;
    int max_val = 500;
    // int max_val = 2;

    for (value = 10; value <= max_val; value++) 
    {
        for (div = 2; div < value; div++)
        {
                if ((value % div == 0) && (value % 2 == 1))
                {
                    printf("%d is a composite number.\n", value);
                }
        }
    }
}