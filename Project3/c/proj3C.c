
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

typedef struct
{
    int back;
    int front;
    char* elements[QUEUE_SIZE];
} Queue;

void InitializeQueue(Queue *q)
{
    q->front = 0;
    q->back = 0;
}

void Enqueue(Queue *q, char* val)
{
    if (q->back + 1 >= QUEUE_SIZE)
        exit(EXIT_FAILURE);
    q->elements[q->back] = val;
    q->back++;
}

char* Dequeue(Queue *q)
{
    if (q->front < 0)
        exit(EXIT_FAILURE);
    char* beforeDequeue = q->elements[q->front];
    q->front++;
    return beforeDequeue;
}



void PrintQueue(Queue *q)
{
    int i;
    printf("Printing queue %p\n", q);
    printf("\tThe back for the front of the queue is %d\n", q->front);
    printf("\tThe back for the back of the queue is %d\n", q->back);
    if (q->front == q->back)
    {
        printf("\tThe queue is empty.\n");
        return;
    }
    int back = q->back;
    if (q->back < q->front)
    {
        // wrapped around, so modify indexing 
        back += QUEUE_SIZE;
    }

    for (i = q->front ; i < back ; i++)
    {
        printf("\t\tEntry[%d] = \"%s\"\n", i%QUEUE_SIZE, q->elements[i%QUEUE_SIZE]);
    }
}



//void
//PrettyPrintQueue(Queue *q, char *type)
//{
//    if (Front(q) == NULL)
//    {
//        printf("No unmatched entries for %s\n", type);
//    }
//    else
//    {
//        char *s;
//        printf("Unmatched %s:\n", type);
//        while ((s = Dequeue(q)))
//        {
//            printf("%s\n", s);
//        }
//    }
//}


char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len+1);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}



int main(int argc, char *argv[])
{
/***  STEP #1: Test your queue code.  ***/


//    Queue q;
//    InitializeQueue(&q);
//    PrintQueue(&q);
//    Enqueue(&q, "hello");
//    PrintQueue(&q);
//    Enqueue(&q, "world");
//    PrintQueue(&q);
//    printf("Dequeue: %s\n", Dequeue(&q));
//    PrintQueue(&q);

    if (argc < 2)
    {
        printf("Invalid number of inputs.\n");
        exit(EXIT_FAILURE);
    }
    printf("argv1 is %s\n", argv[1]);

    FILE *donorList = fopen(argv[1], "r");
    if (donorList == NULL)
    {
       printf("%s is not a valid file", argv[1]);
       exit(EXIT_FAILURE);
    }

    fseek(donorList, 0, SEEK_END);
    long numBytes = ftell(donorList);
    char *buff = malloc(numBytes);
    fseek(donorList, 0, SEEK_SET);
    fread(buff, sizeof(
            unsigned char), numBytes, donorList);
    fclose(donorList);

    char *testTwo = NewString(buff);

    printf("buff is: %s\n", testTwo);

/* Gives this output (with different pointers):
Printing queue 0x7fff5e6878a8
	The back for the front of the queue is 0
	The back for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The back for the front of the queue is 0
	The back for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The back for the front of the queue is 0
	The back for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The back for the front of the queue is 1
	The back for the back of the queue is 2
		Entry[1] = "world"
 */

/*** STEP #2: read in from the input file (argc/argv stuff). 
     NewString is likely helpful here.
 ***/

/*** STEP #3: *after* your queue code works and *after* you can read the file, 
     implement the prompt ***/
/* Here are some helpful lines of code:
 *
 *  My print statement for a match:
 *
    printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
 *
 *
 *  My print statements for the contents of the queues at the end:
 *
    PrettyPrintQueue(&female_donors, "female donors");
    PrettyPrintQueue(&female_recipients, "female recipients");
    PrettyPrintQueue(&male_donors, "male donors");
    PrettyPrintQueue(&male_recipients, "male recipients");
    PrettyPrintQueue(&hospitals, "hospitals");
 *
 */
}
