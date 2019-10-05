#include <stdio.h>

int main() {
    printf("Hello world!\n");
    ex2();
    ex3();
    
}

int ex2(){
    int x = 0;
    while (x < 8)
        x += 5;
        x += 2;

    printf("X is %d\n", x);
}

int ex3()
{
    int x = 0;
    while (x < 8) {
    x += 5;
    x += 2;
    }

    printf("X is %d\n", x);
}