#include <stdio.h>
#include <stdlib.h>

void dereference()
{
    int x;
    int *y = &x;
    x = 5;
    printf("&x = %p, &y = %p\n", &x, &y);
    printf("value of x = %d, value of y = %p\n", x, y);
    printf("*y = %d\n", *y);
    printf("*y = %d\n", y[0]);
}

void array()
{
    char str[16] = "hello world";

    printf("str is %p\n", str);
    printf("str[0] is at %p\n", &(str[0]));
    printf("str[1] is at %p\n", &(str[1]));
    printf("str[15] is at %p\n", &(str[15]));
}

void arrayV2()
{
    int *p = malloc(sizeof(int) * 2);
    p[0] = 4;
    p[1] = 4;
    printf("p[0] is at %p and p[1] is at %p\n", &(p[0]), &(p[1]));
    printf("p[0] is at %p and p[1] is at %p\n", p + 0, p + 1);
}

void pointers()
{
    int x1 = 10;
    int x2 = 20;
    int *y1 = &x1;
    int *y2 = &x2;
    int **z = &y1;

    printf("x1 is at %p and the value of x1 is %d\n", &x1, x1);
    printf("x2 is at %p and the value of xx is %d\n", &x2, x2);
    printf("y1 is at %p and the value of y1 is %p\n", &y1, y1);
    printf("y2 is at %p and the value of y2 is %p\n", &y2, y2);
    printf("z is at %p and the value of z is %p\n", &z, z);
    printf("**z = %d\n", **z);

    z = &y2;
    *y2 = 21;
    printf("x2, *y2, **z = %d, %d, %d\n", x2, *y2, **z);
}

void pointerToString()
{
    int i;
    char s1[16] = "hello";
    char s2[16] = "world";
    char s3[5] = "from";
    char s4[6] = "jacob";
    char s5[7] = "rammer";
    char **list = malloc(sizeof(char *) * 5);
    list[0] = s1;
    list[1] = s2;
    list[2] = s3;
    list[3] = s4;
    list[4] = s5;

    for (i = 0; i < 5; i++)
    {
        printf("%s ", list[i]);
    }
    printf("\n");
}

int main()
{
    // dereference();
    // array();
    // arrayV2();
    // pointers();
    pointerToString();
}

