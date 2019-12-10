#include <stdio.h>
#include <stdlib.h>

#define HASHTABLESIZE 11


typedef struct node
{
    int value;
    struct node* next;
}node;

void insertNode(node** head, int value)
{
    node* newNode = (node*)(malloc(sizeof(node)));
    newNode->value = value;
    newNode->next = NULL;

    if (*head == NULL)
        *head = newNode;
    else
    {
        node* current = *head;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

int getLocation(new_value)
{
    if(new_value < 0)
        new_value *= -1;
    return new_value % HASHTABLESIZE;
}

void insertIntoTable(node** hashTable, int newValue)
{
    int location = getLocation(newValue);
    if(hashTable[location] == NULL)
    {
        hashTable[location] = malloc(sizeof(node*));
        node* head = NULL;
        insertNode(&head, newValue);
        hashTable[location] = head;
    } else{
        node* head = hashTable[location];
        insertNode(&head, newValue);
        hashTable[location] = head;
    }
}

void displayTable(node** hashTable)
{
    for(int i = 0; i < HASHTABLESIZE; i++)
    {
        node* head = hashTable[i];

        if (head == NULL)
            printf("NULL.\n");
        else{
            node* current= head;
            while(current != NULL)
            {
                printf("i = %d current->value = %d \n", i, current->value);
                current = current->next;
            }
        }
    }
}

node** getHashTable()
{
    node** hashTable = calloc(HASHTABLESIZE, sizeof(node*));
    return hashTable;
}

int main()
{
    node** table = getHashTable();
    insertIntoTable(table, 0);
    insertIntoTable(table, 6);
    insertIntoTable(table, 8);
    insertIntoTable(table, 8);
    insertIntoTable(table, 8);

    displayTable(table);

    return 0;
}