#include <stdio.h>

typedef struct
{
    int data;
    struct Node* next;
}Node;

void printLinkedList(Node *ll)
{
    while(ll != NULL)
    {
        printf("%d\n", ll->data);
        ll = (Node *) ll->next;
    }
}


int main()
{
    Node* head = NULL;
    Node* second = NULL;
    Node* third = NULL;
    Node* newSecond = NULL;

    head = (Node*)(malloc(sizeof(Node)));
    second = (Node*)(malloc(sizeof(Node)));
    third = (Node*)(malloc(sizeof(Node)));
    newSecond = (Node*)(malloc(sizeof(Node)));

    head->data = 1;
    head->next = (struct Node *) second;
    second->data = 3;
    second->next = (struct Node *) third;
    third->data = 4;
    third->next = NULL;
    head->next = (struct Node*) newSecond;
    newSecond->data = 2;
    newSecond->next = (struct Node *) second;


    printf("head 1 data is: %d\n", head->data);
    printf("Head 1 pointer is to: %p\n", head->next);
    printf("Head 2 location is %p\n", &second);

    printLinkedList(head);


    return 0;
}