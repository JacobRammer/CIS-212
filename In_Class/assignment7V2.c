#include <stdio.h>

int main()
{
    int array[21] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610
                    , 987, 1597, 2584, 4181, 6765};
    int *a = &array[0];
    int *b[3] = {a, (a + 7), (a + 14)};

    printf("a is %p\n", a);
    printf("*a is %d\n", *a);
    printf("*b[0] is :%p\n", b[0]);
}