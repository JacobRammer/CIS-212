#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ll_node
{
    struct ll_node *next;
    char           *value;
};

struct ll_node *ll_insert(char *v, struct ll_node *cur_head)
{
    struct ll_node *rv = malloc(sizeof(struct ll_node));
    rv->value = v;
    rv->next = cur_head;
    return rv;
}

struct ll_node *ll_remove(char *v, struct ll_node *cur_head)
{
    if (cur_head == NULL)
        return NULL;

    /* special case for cur_head matching v */
    if (strcmp(cur_head->value, v) == 0)
        return cur_head->next;

    struct ll_node *prev = cur_head;
    struct ll_node *curr = cur_head->next;
    while (curr != NULL)
    {
        if (strcmp(curr->value, v) == 0)
        {
            prev->next = curr->next;
            free(curr);
            return cur_head;
        }
        prev = curr;
        curr = curr->next;
    }
    return cur_head; /* nothing removed */
}

void ll_print(struct ll_node *head)
{
    int counter = 0;
    struct ll_node *curr = head;
    while (curr != NULL)
    {
        printf("\t%d: %s\n", counter++, curr->value);
        curr = curr->next;
    }
}

int main()
{
    struct ll_node *cur_head = NULL;
    cur_head = ll_insert("University of Oregon", cur_head);
    cur_head = ll_insert("Oregon State University", cur_head);
    cur_head = ll_insert("Portland State University", cur_head);
    cur_head = ll_insert("Oregon Institute of Technology", cur_head);
    cur_head = ll_insert("Western Oregon University", cur_head);
    cur_head = ll_insert("Southern Oregon University", cur_head);
    cur_head = ll_insert("Eastern Oregon University", cur_head);
    printf("All 7:\n");
    ll_print(cur_head);
    ll_remove("Oregon Institute of Technology", cur_head);
    printf("With OIT removed:\n");
    ll_print(cur_head);
}
