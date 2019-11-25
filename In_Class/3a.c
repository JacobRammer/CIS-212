#include <stdio.h>
#include <stdlib.h>

double RectangleGetArea()
{
    return -1;
}


typedef struct
{
    double (*GetArea)(void);

}Shape;


int main()
{
    Shape s;
    s.GetArea = RectangleGetArea;
    double (*function_ptr )(void)= NULL;
    function_ptr = s.GetArea;

    int Y;
    printf("The area is %f\n", function_ptr());
    printf("The area is %f\n", s.GetArea());
}