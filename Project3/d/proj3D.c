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
#include <sys/time.h>

#define A 31L
#define B 5
#define HASHTABLESIZE 3500

typedef struct
{
    char    *symbol;
    char    *name;
    float    lastSale;
    float    marketCap;
    int      IPOyear;
} Company;

typedef struct Node {
    char* key;
    Company *company;
    struct Node *next;
} Node;

typedef struct {
    Node **entries;
}Hashtable;

typedef struct
{
    int         numElements;
    char      **keys;
    Company    *companies;
} MapBasedOnHashTable;

long myHash(char* key, long n)
{
    unsigned long sum = 0L;
    char* p;
    for(p = key; *p != '\0'; p++)
        sum = A * sum + (unsigned long)(*p);
    return (long)(sum % HASHTABLESIZE);
}

unsigned long rotate(unsigned long value)
{
    static int bits = 8 * sizeof(unsigned long);
    unsigned long ans = value;

    if(B != 0)
        ans = (value << B) | (value >> (bits - B));
    return ans;
}

long mySecondHash(char* key)
{
    unsigned long sum = 0L;
    char* p;
    for(p = key; *p != '\0'; p++)
        sum = rotate(sum) + (unsigned long)*p;
    return (long)(sum % HASHTABLESIZE);
}

Hashtable *createHashTable()
{
    Hashtable *ht = malloc(sizeof(Hashtable));
    ht->entries = malloc(sizeof(Node*) * HASHTABLESIZE);
    for(int i = 0; i < HASHTABLESIZE; i++)
        ht->entries[i] = NULL;
    return ht;
}

Node *pairValues(char *key, Company *c)
{
    Node *entry = malloc(sizeof(Node));
    entry->key = malloc(strlen(key) + 1);
    entry->company = malloc(sizeof(Company));

    entry->key = key;
    entry->company = c;

    entry->next = NULL;

    return entry;
}

void placeInHashTable(Hashtable *ht, Company *c)
{
    unsigned int slot = mySecondHash(c->symbol);
//    printf("hash is %d\n", slot);
    Node *entry = ht->entries[slot];
    if (entry == NULL)
    {
        ht->entries[slot] = pairValues(c->symbol, c);
        return;
    }
    Node *prev;

    while (entry != NULL) {
        if (strcmp(entry->company->symbol, c->symbol) == 0) {
            entry->key = malloc(strlen(c->symbol) + 1);
            return;
        }

        prev = entry;
        entry = prev->next;
    }

    prev->next = pairValues(c->symbol, c);
}

Company* getFromMyHash(Hashtable *ht, Company *c)
{
//    printf("c symbol is %s\n", c->symbol);
    unsigned int slot = mySecondHash(c->symbol);

    Node *entry = ht->entries[slot];
    if (entry == NULL)
        return NULL;
    while (entry != NULL)
    {
        if (strcmp(entry->company->symbol, c->symbol) == 0)
        {
//            printf("key is %s, name is %s, last sale: %f\n", entry->key, entry->company->name, entry->company->lastSale);
            return entry->company;
        }

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

        for(int j = 0; j < HASHTABLESIZE; j++)
        {
            printf("Symbol: %s, Name: %s, lastSale: %f, marketCap: %f, ipoyear: %d\n", entry->company->symbol,
                   entry->company->name, entry->company->lastSale, entry->company->marketCap, entry->company->IPOyear);
            if (entry->next == NULL)
                break;
            entry = entry->next;
        }
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
    long newHash = mySecondHash(c->symbol);
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
    long newHash = mySecondHash(key);
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
//    clock_t t;
//    t = clock();
    struct timeval proj3d;
    gettimeofday(&proj3d, 0);
    for (int i = 0 ; i < numCompanies ; i++)
    {
        StoreTo_MapBasedOnHashTable(&mfht, companies+i);
    }

//    FetchAndPrint(&mfht, "ZNWAA");
//    FetchAndPrint(&mfht, "Z");
//    FetchAndPrint(&mfht, "ZIOP");
//    FetchAndPrint(&mfht, "ZIOQ");
//    FetchAndPrint(&mfht, "YIOQ");
//    FetchAndPrint(&mfht, "QIOQ");
//    FetchAndPrint(&mfht, "WIOQ");
//    FetchAndPrint(&mfht, "XIOQ");
//    FetchAndPrint(&mfht, "TIOQ");
//    FetchAndPrint(&mfht, "UIOQ");
//    FetchAndPrint(&mfht, "VIOQ");
//    FetchAndPrint(&mfht, "ZNGA");
    for(int i = 0; i <numCompanies; i++)
        FetchFrom_MapBasedOnHashTable(&mfht, companies[i].symbol);

    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double proj3dSec = (double)(endTime.tv_sec - proj3d.tv_sec) + (double)(endTime.tv_usec - proj3d.tv_usec) / 1000000;
    printf("3d time: %f\n", proj3dSec);
//    t = clock() - t;
//    double timeTaken = ((double) t) / CLOCKS_PER_SEC;
//    printf("another test %f\n", timeTaken);
    Hashtable *ht = createHashTable();

    struct timeval myTime;
    gettimeofday(&myTime, 0);

//    clock_t myCLock;
//    myCLock = clock();

    for (int i = 0 ; i < numCompanies ; i++)
    {
        placeInHashTable(ht, &companies[i]);
    }
//    printf("test %s %s", ht->entries[414]->company->name, ht->entries[414]->company->symbol);
//    printMyHashTable(ht);
    for (int i = 0 ; i < numCompanies ; i++)
        getFromMyHash(ht, &companies[i]);

    struct timeval myEnd;
    gettimeofday(&myEnd, 0);

    double seconds = (double)(myEnd.tv_sec - myTime.tv_sec) + (double)(myEnd.tv_usec - myTime.tv_usec) / 1000000;
    printf("My time: %f\n", seconds);

//    Company *p = getFromMyHash(ht, &companies[0]);
//    printf("test %s\n", p->name);
//    printMyHashTable(ht);
//    myCLock = clock() - myCLock;
//    double myTime = ((double) myCLock) / CLOCKS_PER_SEC;
//    printf("my time %f, 3d starter: %f\n", myTime, timeTaken);
//    printMyHashTable(ht);
//    FetchAndPrint(&mfht, "ZNWAA");
//    FetchAndPrint(&mfht, "Z");
//    FetchAndPrint(&mfht, "ZIOP");
//    FetchAndPrint(&mfht, "ZIOQ");
//    FetchAndPrint(&mfht, "YIOQ");
//    FetchAndPrint(&mfht, "QIOQ");
//    FetchAndPrint(&mfht, "WIOQ");
//    FetchAndPrint(&mfht, "XIOQ");
//    FetchAndPrint(&mfht, "TIOQ");
//    FetchAndPrint(&mfht, "UIOQ");
//    FetchAndPrint(&mfht, "VIOQ");
//    FetchAndPrint(&mfht, "ZNGA");

//    struct timeval startTime;
//    gettimeofday(&startTime, 0);
//    int j = 0;
//    for(int i = 0; i < 100000; i++)
//        j++;
//    struct timeval endTime;
//    gettimeofday(&endTime, 0);
//    double seconds = (double)(endTime.tv_sec - startTime.tv_sec) + (double)(endTime.tv_usec - startTime.tv_usec) / 1000000;
//    printf("sdf %f", proj3dSec);


//    printMyHashTable(ht);
//    printf("test %s", ht->entries[0]->company->name);


}

/* YOUR PERFORMANCE STUDY WRITEUP GOES HERE:
I'll have to say this experiment did not go the way I thought it would.
I initially just chose one of the first hash functions that I came across
 online and tested the results with that. After some more experimentation,
 I decided to go with a hash function from our book that shifted the bits,
 since I'm familiar with them since we used it extensively in 211. This
 cut my time in half. The results were quite
 impressive. I thought that linked lists would be faster, but that was not the case.
 I even looked it up because I thought I screwed up, so I had to look it up online
 which only confirmed my results.
 */