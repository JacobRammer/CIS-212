#include <stdio.h>
# include <stdlib.h>

int main()
{
    /* 
    buffer overflow
    */
    int A[3];  // Array of size 3
    int B[3];

    printf("A is at %p\n", A);
    printf("&A is at: %p\n", &A);
    printf("A[0] is at %p\n", &(A[0]));
    printf("A[1] is at %p\n", &(A[1]));
    printf("A[2] is at %p\n", &(A[2]));
    printf("A[3] is at %p\n", &(A[3]));  // not a valid array location
    printf("B is at %p\n", B);

    B[0] = 6;
    B[1] = 7;
    B[2] = 8;
    A[0] = 60;
    A[1] = 70;
    A[2] = 80;
    A[3] = 90;  // reassigns b[1]

    printf("A = %d %d %d and B = %d %d %d\n", A[0], A[1], A[2], 
    B[0], B[1], B[2]);
    

    /*
    Dereferencing
    

    int x;
    int *y = &x;  // create a pointer that points to x
    x = 5;
    printf("The address of &x = %p, &y = %p\n", &x, &y);
    printf("Value of x = %d, value of y = %p\n", x, y);
    printf("*y = %d\n", *y);
    printf("y[0] is %d\n", y[0]);
    *y = 8;  // will change the value of x
    printf("The value of x is %d\n", x);
    */

   /* 
   array and pointer arithmetic
   
    char str[17] = "hello world";
    printf("str is at %p\n", str);
    for (int i = 0; i < 17; i++)
        printf("str[%d] is at %p\n", i, &(str[i]));

    int *p = malloc(sizeof(int) * 2);
    p[0] = 4;
    p[1] = 5;
    printf("p[0] is at %p and p[1] is at %p\n", &(p[0]), &(p[1]));
    printf("p[0] is at %p and p[1] is at %p\n", p + 0, p + 1);  // go over 1 integer (data type of array)
    */

    /* 
   Pointers to pointers
   

    int x1 = 10;
    int x2 = 20;
    int *y1 = &x1;
    int *y2 = &x2;
    int **z = &y1; // pointer to a pointer

    printf("x1 is at %p and the value of x1 is %d\n", &x1, x1);
    printf("x2 is at %p and the value of x1 is %d\n", &x2, x2);
    printf("y1 is at %p and the value of x1 is %p\n", &y1, y1);
    printf("y2 is at %p and the value of x1 is %p\n", &y2, y2);
    printf("z is at %p and the value of x1 is %p\n", &z, z);
    printf("*z = %p\n", *z);
    printf("**z = %d\n", **z);

    char s1[6] = "hello";
    char s2[6] = "world";
    char s3[5] = "from";
    char s4[6] = "jacob";
    char s5[7] = "rammer";
    char **list = malloc(sizeof(char *) * 5);
    list[0] = s1;
    list[1] = s2;
    list[2] = s3;
    list[3] = s4;
    list[4] = s5;

    for (int i = 0; i < 5; i++)
        printf("%s ", list[i]);

    */
}
