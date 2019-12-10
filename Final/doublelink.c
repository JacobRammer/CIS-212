#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ll_node
{
    struct ll_node *next;
    struct ll_node *prev;
    char           *value;
};

struct ll_node *ll_insert(char *v, struct ll_node *cur_head)
{
    struct ll_node *rv = malloc(sizeof(struct ll_node));
    rv->value = v;
    rv->next = cur_head;
    if (cur_head != NULL)
        cur_head->prev = rv;
    rv->prev = NULL;
    return rv;
}

struct ll_node *ll_remove(char *v, struct ll_node *cur_head)
{
    if (cur_head == NULL)
        return NULL;

    /* special case for cur_head matching v */
    if (strcmp(cur_head->value, v) == 0)
    {
        cur_head->next->prev = NULL;
        struct ll_node *rv = cur_head->next;
        free(cur_head);
        return rv;
    }

    struct ll_node *curr = cur_head->next;
    while (curr != NULL)
    {
        if (strcmp(curr->value, v) == 0)
        {
            curr->prev->next = curr->next;
            if (curr->next != NULL)
                curr->next->prev = curr->prev;
            free(curr);
            return cur_head;
        }
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
        char *next_val = "null";
        if (curr->next != NULL)
            next_val = curr->next->value;
        char *prev_val = "null";
        if (curr->prev != NULL)
            prev_val = curr->prev->value;
        printf("\t%d: %s, prev=%s, next=%s\n", counter++, curr->value, prev_val, next_val);
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
