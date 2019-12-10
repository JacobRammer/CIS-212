/*
 * I believe I have completed:
 *  Map based on linked lists: yes/no
 *  Double hashing: yes/no
 *  Performance study: yes/no
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define A 31L
#define HASHTABLESIZE 7

typedef struct
{
    char    *symbol;
    char    *name;
    float    lastSale;
    float    marketCap;
    int      IPOyear;
} Company;

typedef struct Node {
    char *key;
    struct Company *company;
    struct Node *next;
} Node;

typedef struct {
    Node **entries;
}Hashtable;

long myHash(char* key, long n)
{
    unsigned long sum = 0L;
    char* p;
    for(p = key; *p != '\0'; p++)
        sum = A * sum + (unsigned long)(*p);
    return (long)(sum % HASHTABLESIZE);
}

Hashtable *createHashTable()
{
    Hashtable *ht = malloc(sizeof(Hashtable));
    ht->entries = malloc(sizeof(Node*) * HASHTABLESIZE);
    int i = 0;
    for (; i < HASHTABLESIZE; ++i) {
        ht->entries[i] = NULL;
    }
    return ht;
}

Node *pairValues(char *key, char *value)
{
    Node *entry = malloc(sizeof(Node));
    entry->key = malloc(strlen(key) + 1);
    entry->company = malloc(strlen(value) + 1);

    strcpy(entry->key, key);
    strcpy(entry->company, value);

    entry->next = NULL;

    return entry;
}

void placeInHashTable(Hashtable *ht, Company *key, Company *value) {
    unsigned int slot = myHash(key->symbol, HASHTABLESIZE);
    Node *entry = ht->entries[slot];
    if (entry == NULL) {
        ht->entries[slot] = pairValues(key->symbol, value->symbol);
        return;
    }
    Node *prev;

    while (entry != NULL) {
        if (strcmp(entry->key, key->symbol) == 0) {
            free(entry->value);
            entry->value = malloc(strlen(value->symbol) + 1);
            strcpy(entry->value, value->symbol);
            return;
        }

        prev = entry;
        entry = prev->next;
    }

    prev->next = pairValues(key->symbol, value->symbol);
}

char *getFromMyHash(Hashtable *ht, char *key)
{
    unsigned int slot = myHash(key, HASHTABLESIZE);

    Node *entry = ht->entries[slot];
    if (entry == NULL)
        return NULL;
    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
            return entry->value;

        entry = entry->next;
    }

    return NULL;
}

void printMyHashTable(Hashtable *ht)
{
    for (int i = 0; i < HASHTABLESIZE; ++i) {
        Node *entry = ht->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("I =  %d: ", i);

        for(;;) {
            printf("%s=%s ", entry->key, entry->value);
            if (entry->next == NULL)
                break;
            entry = entry->next;
        }
        printf("\n");
    }
}






















//NOT MY STUFF

void PrintCompany(Company *c)
{
    printf("%s:\n", c->name);
    printf("\tSymbol: %s\n", c->symbol);
    /* .2f: only print two digits after the period. */
    printf("\tLast Sale: %.2f\n", c->lastSale);
    printf("\tMarket Capitalization: %.2f\n", c->marketCap);
    printf("\tYear of Initial Public Offering: %d\n", c->IPOyear);
}


void ReadFile(const char *filename, Company **companies_rv, int *numCompanies_rv)
{
    int  i, j;

    if (filename == NULL)
    {
        fprintf(stderr, "No filename specified!\n");
        exit(EXIT_FAILURE);
    }
    FILE *f_in = fopen(filename, "r");
    if (f_in == NULL)
    {
        fprintf(stderr, "Unable to open file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f_in, 0, SEEK_END);
    int numChars = ftell(f_in);
    // printf("The number of characters is %d\n", numChars);
    fseek(f_in, 0, SEEK_SET);

    char *file_contents = malloc(sizeof(char)*numChars+1);
    fread(file_contents, sizeof(char), numChars, f_in);
    file_contents[numChars] = '\0';
    fclose(f_in);
    /* Note: the memory for this array is used to populate
     * the fields of the companies.  If it is freed, then
     * the company structs all become invalid.  For the
     * context of this program, this array should not be
     * freed. */

    // Find out how many lines there are
    int numLines = 0;
    for (i = 0 ; i < numChars ; i++)
        if (file_contents[i] == '\n')
            numLines++;
    // printf("Number of lines is %d\n", numLines);

    int      numCompanies = numLines-1; // first line is header info
    Company *companies    = malloc(sizeof(Company)*numCompanies);

    /* strtok will parse the file_contents array.
     * The first time we call it, it will replace every '"' with '\0'.
     * It will also return the first word before a
     */
    int numColumns = 9;
    int numberOfQuotesPerColumn = 2;
    strtok(file_contents, "\"");
    for (i = 0 ; i < numberOfQuotesPerColumn*numColumns-1 ; i++)
        strtok(NULL, "\"");
    for (i = 0 ; i < numCompanies ; i++)
    {
        companies[i].symbol = strtok(NULL, "\"");
        strtok(NULL, "\"");
        companies[i].name = strtok(NULL, "\"");
        strtok(NULL, "\"");
        companies[i].lastSale = atof(strtok(NULL, "\""));
        strtok(NULL, "\"");
        companies[i].marketCap = atof(strtok(NULL, "\""));
        strtok(NULL, "\"");

        /* Skip ADR TSO */
        strtok(NULL, "\"");
        strtok(NULL, "\"");

        companies[i].IPOyear = atoi(strtok(NULL, "\""));
        strtok(NULL, "\"");

        /* Skip Sector, Industry, Summary Quote */
        for (j = 0 ; j < 6 ; j++)
            strtok(NULL, "\"");

        //PrintCompany(companies+i);
    }

    /* Set parameters to have output values */
    *companies_rv    = companies;
    *numCompanies_rv = numCompanies;
}

int hash(char *name, long array_size)
{
    int hashval = 0;
    char *p = name;
    while (*p != '\0')
    {
        hashval = 31*hashval + *p;
        p++;
    }

    return hashval%array_size;
}

typedef struct
{
    int         numElements;
    char      **keys;
    Company    *companies;
} MapBasedOnHashTable;

void InitializeMapBasedOnHashTable(MapBasedOnHashTable *map, int numElements)
{
    map->numElements = numElements;
    map->keys = malloc(sizeof(char *)*numElements);
    map->companies = malloc(sizeof(Company)*numElements);
    for (int i = 0 ; i < numElements ; i++)
        map->keys[i] = NULL;
}

void StoreTo_MapBasedOnHashTable(MapBasedOnHashTable *map, Company *c)
{
    int hashval = hash(c->symbol, map->numElements);
    long newHash = myHash(c->symbol, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval+i * newHash)%(map->numElements);
        if (idx < 0) idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            map->keys[idx]      = c->symbol;
            map->companies[idx] = *c;
            return;
        }
    }
}

Company *
FetchFrom_MapBasedOnHashTable(MapBasedOnHashTable *map, char *key)
{
    int hashval = hash(key, map->numElements);
    long newHash = myHash(key, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval+i * newHash)%(map->numElements);
        if (idx < 0) idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            return NULL;
        }

        if (strcmp(map->keys[idx], key) == 0)
        {
            return &(map->companies[idx]);
        }
    }

    return NULL;
}

void FetchAndPrint(MapBasedOnHashTable *mfht, char *key)
{
    Company *c = FetchFrom_MapBasedOnHashTable(mfht, key);
    if (c == NULL)
    {
        printf("Key %s has no corresponding company\n", key);
    }
    else
    {
        PrintCompany(c);
    }

}

int main(int argc, char *argv[])
{
    Company *companies = NULL;
    int      numCompanies;
    ReadFile(argv[1], &companies, &numCompanies);
    MapBasedOnHashTable mfht;
    printf("num companies is %d\n", numCompanies);
    InitializeMapBasedOnHashTable(&mfht, numCompanies*2);
    time_t t = time(NULL);
    for (int i = 0 ; i < numCompanies ; i++)
    {
        StoreTo_MapBasedOnHashTable(&mfht, &companies[i]);
    }

    FetchAndPrint(&mfht, "ZNWAA");
    FetchAndPrint(&mfht, "Z");
    FetchAndPrint(&mfht, "ZIOP");
    FetchAndPrint(&mfht, "ZIOQ");
    FetchAndPrint(&mfht, "YIOQ");
    FetchAndPrint(&mfht, "QIOQ");
    FetchAndPrint(&mfht, "WIOQ");
    FetchAndPrint(&mfht, "XIOQ");
    FetchAndPrint(&mfht, "TIOQ");
    FetchAndPrint(&mfht, "UIOQ");
    FetchAndPrint(&mfht, "VIOQ");

    Hashtable *ht = createHashTable();
    for (int i = 0 ; i < numCompanies ; i++)
    {
        placeInHashTable(ht, &companies[i], &companies[i]);
    }

//    placeInHashTable(ht, "name1", "em");
//    placeInHashTable(ht, "name2", "russian");
//    placeInHashTable(ht, "name3", "pizza");
//    placeInHashTable(ht, "name4", "doge");
//    placeInHashTable(ht, "name5", "pyro");
//    placeInHashTable(ht, "name6", "joost");
//    placeInHashTable(ht, "name7", "kalix");

    printMyHashTable(ht);

}

/* YOUR PERFORMANCE STUDY WRITEUP GOES HERE:

 */