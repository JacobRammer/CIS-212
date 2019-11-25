#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct name FullName;
struct name
{
    char *fname;
    char *lname;
}name;

typedef struct info Info;
struct info
{
    int age;
    FullName *full_name;
    void (*print)(Info *);
    void (*destroy)(Info *);
};


void printName(Info *info)
{
    printf("%s\n%s\n%d\n", info->full_name->fname, info->full_name->lname, info->age);
}

void destroyInfo(Info * info)
{
    free(info->full_name->fname);
    free(info->full_name->lname);
    free(info->full_name);
    free(info);
}

int main()
{
    // name myName;
    FullName *name = (FullName*)malloc(sizeof(FullName));
    name->fname = strdup("John");
    name->lname = strdup("Doe");

    Info *info = (Info *)malloc(sizeof(Info));
    info->age = 30;
    info->full_name = name;
    info->print = printName;
    info->destroy = destroyInfo;

    info->print(info);
    info->destroy(info);



    // myName->age = 30;
    // strcpy(myName->fname, "John");
    // strcpy(myName->lname, "Doe");
    // printName(myName);
}
