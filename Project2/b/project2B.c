/*
Jacob Rammer
Project 2b
*/

#include <stdio.h>

int main()
{
    int A[3] = { 252, 657, 268};
    
    // Using bubble sort

    int index, sorted;
    int size = sizeof(A) / 4;  // 4 bytes to int

    while(1)
    {
        sorted = 0;
        for(index = 0; index < (size - 1); index++)
        {
            if(A[index] > A[index + 1])
            {
                int tempVal = A[index];
                int newVal = A[index + 1];
                A[index] = newVal;
                A[index + 1] = tempVal;
                sorted = 1;
            }
        }
        if(sorted == 0)
        {
            break;
        }
    }

    for(int i = 0; i != size; i++)
    {
        printf("\t%d", A[i]);
        if((i + 1) % 10 == 0) // Arrays start at 0
        {
            printf("\n");
        }
    }
}
