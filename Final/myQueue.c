#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int front, back, size, capacity;
    int* data;
}Queue;

Queue* initializeQueue(int capacity)
{
    Queue *q = (Queue*)(malloc(sizeof(Queue)));
    q->front = 0;
    q->capacity = capacity;
    q->size = 0;
    q->back = capacity -1;
    q->data = (int*)(malloc(sizeof(int) * capacity));
    return q;
}

int isFull(Queue *q)
{
    return q->size == q->capacity;
}

void enqueue(Queue *q, int value)
{
    if(isFull(q))
        return;
    q->back = (q->back + 1) % q->capacity;
    q->data[q->back] = value;
    q->size++;
}

int isEmpty(Queue *q)
{
    return q->size == 0;
}

int dequeue(Queue *q)
{
    if(!isEmpty(q))
    {
        int item = q->data[q->front];
        q->front = (q->front + 1) % q->capacity;
        q->size--;
        return item;
    }
    printf("Queue is empty. Returning 0. ");
    return 0;
}

int main()
{
    Queue *myQueue = initializeQueue(10);
    enqueue(myQueue, 5);
    printf("myQueue front is %d, back is %d, size of %d, capacity %d\n", myQueue->front, myQueue->back, myQueue->size, myQueue->capacity);
    printf("Value of q0 is %d\n", myQueue->data[myQueue->front]);
    printf("Deque: %d\n", dequeue(myQueue));
    printf("Deque: %d\n", dequeue(myQueue));


    return 0;
}