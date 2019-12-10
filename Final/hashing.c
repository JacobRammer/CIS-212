#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLESIZE 5

typedef struct entry_t {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node **entries;
} Hashtable;

unsigned int hash(const char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // do several rounds of multiplication
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    // make sure value is 0 <= value < HASHTABLESIZE
    value = value % HASHTABLESIZE;

    return value;
}

Node *ht_pair(const char *key, const char *value) {
    // allocate the entry
    Node *entry = malloc(sizeof(Node) * 1);
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    // copy the key and value in place
    strcpy(entry->key, key);
    strcpy(entry->value, value);

    // next starts out null but may be set later on
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

void ht_set(Hashtable *hashtable, const char *key, const char *value) {
    unsigned int slot = hash(key);

    // try to look up an entry set
    Node *entry = hashtable->entries[slot];

    // no entry means slot empty, insert immediately
    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair(key, value);
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
    prev->next = ht_pair(key, value);
}

char *ht_get(Hashtable *hashtable, const char *key) {
    unsigned int slot = hash(key);

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

void ht_del(Hashtable *hashtable, const char *key) {
    unsigned int bucket = hash(key);

    // try to find a valid bucket
    Node *entry = hashtable->entries[bucket];

    // no bucket means no entry
    if (entry == NULL) {
        return;
    }

    Node *prev;
    int idx = 0;

    // walk through each entry until either the end is reached or a matching key is found
    while (entry != NULL) {
        // check key
        if (strcmp(entry->key, key) == 0) {
            // first item and no next entry
            if (entry->next == NULL && idx == 0) {
                hashtable->entries[bucket] = NULL;
            }

            // first item with a next entry
            if (entry->next != NULL && idx == 0) {
                hashtable->entries[bucket] = entry->next;
            }

            // last item
            if (entry->next == NULL && idx != 0) {
                prev->next = NULL;
            }

            // middle item
            if (entry->next != NULL && idx != 0) {
                prev->next = entry->next;
            }

            // free the deleted entry
            free(entry->key);
            free(entry->value);
            free(entry);

            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;

        ++idx;
    }
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
    ht_set(ht, "name2", "russian");
    ht_set(ht, "name3", "pizza");
    ht_set(ht, "name4", "doge");
    ht_set(ht, "name5", "pyro");
    ht_set(ht, "name6", "joost");
    ht_set(ht, "name7", "kalix");

    ht_dump(ht);

    return 0;
}
