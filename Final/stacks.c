#include <stdio.h>
#define MAX_SIZE = 10
typedef struct
{
    int index;
    unsigned capacity;
    double* data;

}Stack;

Stack* initialize(unsigned capacity)
{
    Stack* stack = (Stack*)(malloc(sizeof(Stack)));
    stack->capacity = capacity;
    stack->index = -1;
    stack->data = (double*)(malloc(stack->capacity * sizeof(double)));
    return stack;
}

int isFull(Stack *s)
{
    return (s->index == (s->capacity) -1);
}

int isEmpty(Stack *s)
{
    return s->index = -1;
}

void push(Stack *s, double value)
{
    if(isFull(s))
    {
       printf("Stack is full.\n");
       return;
    }
    s->index++;
    s->data[s->index] = value;
}

double pop(Stack *s)
{
    return s->data[s->index--];
}

int main()
{
    Stack *s;
    s = initialize(15);
    push(s, 10);
    printf("Stack %d is %f\n", s->index, s->data[s->index]);
    push(s, 30);
    printf("Stack %d is %f\n", s->index, s->data[s->index]);
    printf("I should be popping 30: %f\n", pop(s));
    printf("I should be popping 10: %f\n", pop(s));
    return 0;
}