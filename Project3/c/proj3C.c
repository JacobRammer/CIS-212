
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 30 // change back to 10

typedef struct
{
    int back;
    int front;
    int priority;
    char* elements[QUEUE_SIZE];
} Queue;

void InitializeQueue(Queue *q)
{
    for(int i = 0; i < QUEUE_SIZE; i++)
        q->elements[i] = NULL;
    q->front = 0;
    q->back = 0;
    q->priority = 0;

}

void Enqueue(Queue *q, char* val)
{
    if (q->back + 1 >= QUEUE_SIZE)
    {
        printf("Enqueue failed\n");
        exit(EXIT_FAILURE);
    }
    q->elements[q->back] = val;
    q->back++;
    q->priority++;
}

char* Dequeue(Queue *q)
{
    if (q->front < 0)
    {
        printf("At beginning of queue\n");
        return 0;
    }
    char* beforeDequeue = q->elements[q->front];
    q->front++;
    q->priority = 0;
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



void PrettyPrintQueue(Queue *q, char *type)
{
    if (q->front == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
        while ((s = Dequeue(q)))
        {
            printf("%s\n", s);
        }
    }
}


char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len+1);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}




void placeInCorrectQueue(char* line, Queue *md, Queue *mr, Queue *fd, Queue *fr, Queue *h)
{
    if (line[0] == 'R'  && line[2] == 'F')  // recipient
    {
        Enqueue(fr, line + 4);
    }
    if (line[0] == 'D'  && line[2] == 'F')  // donor
    {
        Enqueue(fd, line + 4);
    }
    if (line[0] == 'R'  && line[2] == 'M')
    {
        Enqueue(mr, line + 4);
    }
    if (line[0] == 'D'  && line[2] == 'M')
    {
        Enqueue(md, line + 4);
    }
    if (line[0] == 'H')
    {
        Enqueue(h, line + 2);
    }
}

void dequeInOrder(const char* line, Queue *md, Queue *mr, Queue *fd, Queue *fr, Queue *h)
{
    if((line[2] == 'F' && line[0] == 'R')  || (line[2] == 'F' && line[0] == 'D'))  // dequeue females
    {
        if((h->front) == (h->back) || (fd->front) == (fd->back) || (fr->front) == (fr->back)) {
            return;
        }else{
            printf("MATCH: %s donates to %s at hospital %s\n", Dequeue(fd), Dequeue(fr), Dequeue(h));
        }
    }

    if((line[2] == 'M' && line[0] == 'R') || (line[2] == 'M' && line[0] == 'D'))  // dequeue males
    {
        if((h->front) == (h->back) || (md->front) == (md->back) || (mr->front) == (mr->back)) {
            return;
        }else{
            printf("MATCH: %s donates to %s at hospital %s\n", Dequeue(md), Dequeue(mr), Dequeue(h));
        }
    }
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


    char line[256];  //array that holds each line
    int lineNum = 0;  // the present line in the file stream
    int setLines = 0;  // will be the total number of lines in the file

    Queue maleDonors;
    Queue maleRecipients;
    Queue femaleDonors;
    Queue femaleRecipients;
    Queue hospital;
    InitializeQueue(&maleDonors);
    InitializeQueue(&maleRecipients);
    InitializeQueue(&femaleDonors);
    InitializeQueue(&femaleRecipients);
    InitializeQueue(&hospital);


    if (argc < 2)
    {
        printf("Invalid number of inputs.\n");
        exit(EXIT_FAILURE);
    }

    FILE *donorList = fopen(argv[1], "r");
    if (donorList == NULL)
    {
       printf("%s is not a valid file", argv[1]);
       exit(EXIT_FAILURE);
    }
    /*
     Dynamically find number of lines
     */
    while(fgets(line, 256, donorList))
        setLines++;
    char *buff[setLines];  // you have to set this after the loop ya derp


    fseek(donorList, 0, SEEK_SET);

    while(fgets(line, 256, donorList))
    {
        buff[lineNum] = NewString(line);
//        printf("buff[%d] is %s\n", lineNum, buff[lineNum]);
        lineNum++;
    }

    /*
     * Start queue
     */
    for (int i = 0; i < setLines; i++)
    {
        placeInCorrectQueue(buff[i], &maleDonors, &maleRecipients, &femaleDonors, &femaleRecipients, &hospital);


    }


    for(int i = 0; i < setLines; i++) {
        if(buff[i][0] == 'H')
        {
            i++;
            dequeInOrder(buff[i], &maleDonors, &maleRecipients, &femaleDonors, &femaleRecipients, &hospital);
        }else{
            dequeInOrder(buff[i], &maleDonors, &maleRecipients, &femaleDonors, &femaleRecipients, &hospital);

        }
    }


//
//    PrintQueue(&maleDonors);
//    PrintQueue(&maleRecipients);
//    PrintQueue(&femaleDonors);
//    PrintQueue(&femaleRecipients);
//    PrintQueue(&hospital);

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
    PrettyPrintQueue(&male_donors, "maleDonors donors");
    PrettyPrintQueue(&male_recipients, "maleDonors recipients");
    PrettyPrintQueue(&hospitals, "hospitals");
 *
 */
}
