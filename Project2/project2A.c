/*
Jacob Rammer 
Project 2
*/

#include <stdio.h>

int main() {
    int a, b;
    int target = 50;
    int max_val = 2;

    for (a = 2; a <= target; a++) {
        for (b = 2; b < a; b++) {
            if (a * b > target) {
                /*
                    It's probably very easy to exclude everything less than 10
                    rather than using this if overly chained if statement, 
                    but I can't think of anything currently.
                */
                break;
            }
            if ((a * b % b) == 0)
            {
                if ((a * b % 2) == 1)
                {
                    printf("\n%d is a composite number", (a * b));
                }
            }
        }

            // max_val ++;
        }
}