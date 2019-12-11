#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLESIZE 5

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node **entries;
}Hashtable;
#define A 31L


long myhash(char* key)
{
    unsigned long sum = 0L;
    char* p;
    for(p = key; *p != '\0'; p++)
        sum = A * sum + (unsigned long)(*p);
    return (long)(sum % HASHTABLESIZE);
}


Node *pairValues(char *key, char *value)
{
    Node *entry = malloc(sizeof(Node));
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    strcpy(entry->key, key);
    strcpy(entry->value, value);

    entry->next = NULL;

    return entry;
}

Hashtable *createHashTable(void) {
    // allocate table
    Hashtable *hashtable = malloc(sizeof(Hashtable) * 1);

    // allocate table node
    hashtable->entries = malloc(sizeof(Node*) * HASHTABLESIZE);

    // set each to null (needed for proper operation)
    int i = 0;
    for (; i < HASHTABLESIZE; ++i) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set(Hashtable *hashtable, char *key, char *value) {
    unsigned int slot = mySmyhash(key);

    // try to look up an entry set
    Node *entry = hashtable->entries[slot];

    // no entry means slot empty, insert immediately
    if (entry == NULL) {
        hashtable->entries[slot] = pairValues(key, value);
        return;
    }

    Node *prev;

    // walk through each entry until either the end is
    // reached or a matching key is found
    while (entry != NULL) {
        // check key
        if (strcmp(entry->key, key) == 0) {
            // match found, replace value
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;
    }

    // end of chain reached without a match, add new
    prev->next = pairValues(key, value);
}

char *ht_get(Hashtable *hashtable, char *key) {
    unsigned int slot = myhash(key);

    // try to find a valid slot
    Node *entry = hashtable->entries[slot];

    // no slot means no entry
    if (entry == NULL) {
        return NULL;
    }

    // walk through each entry in the slot, which could just be a single thing
    while (entry != NULL) {
        // return value if found
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }

        // proceed to next key if available
        entry = entry->next;
    }

    // reaching here means there were >= 1 node but no key match
    return NULL;
}


void ht_dump(Hashtable *hashtable) {
    for (int i = 0; i < HASHTABLESIZE; ++i) {
        Node *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        for(;;) {
            printf("%s=%s ", entry->key, entry->value);

            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}

int main(int argc, char **argv) {
    Hashtable *ht = createHashTable();

    ht_set(ht, "name1", "em");
//    ht_set(ht, "name2", "russian");
//    ht_set(ht, "name3", "pizza");
//    ht_set(ht, "name4", "doge");
//    ht_set(ht, "name5", "pyro");
//    ht_set(ht, "name6", "joost");
//    ht_set(ht, "name7", "kalix");

    ht_dump(ht);

    return 0;
}