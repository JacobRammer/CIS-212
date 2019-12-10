#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int index, capacity;
    int* data;
}Stack;

Stack* createStack(int capacity)
{
    Stack *s = (Stack*)(malloc(sizeof(Stack)));
    s->index = 0;
    s->capacity = capacity;
    s->data = (int*)(malloc(sizeof(int) * capacity));
    return s;
}

int isFull(Stack *s)
{
    return s->index == s->capacity - 1;
}

int isEmpty(Stack *s)
{
    return s->index< 0;
}

void push(Stack *s, int value)
{
    if(isFull(s))
        return;
    s->data[s->index] = value;
    s->index++;
}

int pop(Stack *s)
{
    if(isEmpty(s))
        exit(EXIT_FAILURE);
    s->index--;
    return s->data[s->index];
}


int main()
{
    Stack *myStack = createStack(10);
    push(myStack, 10);
    push(myStack, 15);
    printf("Popping %d from stack\n", pop(myStack));
    printf("Popping %d from stack\n", pop(myStack));

}