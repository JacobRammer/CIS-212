/*
Jacob Rammer
Project 2b
*/

#include <stdio.h>

int main()
{
    int A[100] = { 252, 657, 268, 402, 950, 66, 391, 285, 133, 577, 649, 166, 987, 314, 
    954, 214, 920, 230, 904, 801, 40, 552, 369, 682, 202, 712, 395, 517, 755, 
    603, 134, 385, 428, 941, 443, 477, 95, 647, 687, 737, 673, 19, 325, 697, 
    577, 181, 45, 964, 267, 600, 858, 145, 780, 760, 949, 508, 673, 717, 446, 
    634, 635, 679, 466, 474, 916, 855, 216, 899, 804, 159, 237, 625, 963, 
    388, 437, 682, 821, 325, 805, 876, 968, 414, 190, 434, 902, 794, 752, 
    729, 77, 243, 705, 953, 765, 637, 765, 158, 166, 599, 70, 927 };
    
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
                A[index] = A[index + 1];
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
