/*
Jacob Rammer 
Project 2
*/

#include <stdio.h>

int main() {
    int a, b;
    int target = 50;

    for (a = 2; a <= target; a++) {
        for (b = 2; b < a; b++) {
            if (a * b > target) {
                break;
            }
            if ((a * b % b) == 0){
                if ((a * b % 2) == 1) {
                    printf("\n%d is a composite number", (a * b));
                }
            }
        }
    }
  
}