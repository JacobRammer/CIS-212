#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int front, rear, size;
    int capacity;
    int* array;

}Queue;

Queue* createQueue(int capacity)
{
    Queue* queue = (Queue*)(malloc(sizeof(Queue)));
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)(malloc(sizeof(int) * capacity));
    return queue;
}

int isFull(Queue *queue)
{
    return queue->size == queue->capacity;
}

int isEmpty(Queue *queue)
{
    return queue->size == 0;
}

void enqueue(Queue *queue, int item)
{
    if(isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;  // this will allow wraparounds
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue *queue)
{
    if(!isEmpty(queue))
    {
        int item = queue->array[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;  // this will allow wraparounds
        queue->size--;
        return item;
    }
    printf("Queue is empty\n");
    exit(EXIT_FAILURE);
}

int main()
{
    Queue *q = createQueue(10);
    enqueue(q, 10);
    enqueue(q, 1000);
    printf("dequeue %d\n", dequeue(q));
    printf("dequeue %d\n", dequeue(q));
    printf("dequeue %d\n", dequeue(q));

    return 0;
}