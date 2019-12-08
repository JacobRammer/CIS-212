
#include <stdio.h>
#include <stdlib.h>

/*
Project 3a
Jacob Rammer
*/

/* struct definitions go here.
 * use:
 *  typedef struct
 *  {
 *     ...
 *  } Apple;  (or Banana or Fruit)
 */

typedef struct
{
    void *self;
    char* (*GetColor)(void *self);
    double (*GetVolume)(void *self);
}Fruit;
typedef struct 
{
    double height;
    double radius;
    char color;
}Banana;

typedef struct
{
    double radius;
    int green;
}Apple;

char *BananaGetColor(Banana *b)
{
    // printf("banana color\n");
    return "yellow";
}

double FruitGetVolume(Fruit *fr)
{
    double volume = fr->GetVolume(fr->self);
    return volume;
}

char* FruitGetColor(Fruit *fr)
{
    // printf("fruit color\n");
    char *color = fr->GetColor(fr->self);
    return color;
}

double BananaGetVolume(Banana *fr)
{
    double volume = (fr->height * fr->radius * fr->radius * 3.14);
    return volume;
}

char* AppleGetColor(Apple *a)
{
    if (a->green == 1)
        return "green";
    return "red";
}

double AppleGetVolume(Apple *a)
{
    double volume = (4 / 3.0 * a->radius * a->radius * a->radius * 3.14);
    return volume;
}

/* DO NOT MODIFY BELOW THIS POINT */
/* (ALTHOUGH YOU CAN MODIFY FOR TESTING PURPOSES ... JUST CHANGE IT BACK) */

Fruit *CreateBanana(double r, double h)
{
    Banana *a = malloc(sizeof(Banana));
    a->radius = r;
    a->height = h;
    Fruit *f = malloc(sizeof(Fruit));
    f->self = a;
    f->GetColor = (char *(*)(void *)) BananaGetColor;
    f->GetVolume = (double (*)(void *)) BananaGetVolume;
    return f;
}

Fruit *CreateApple(double r, int isGreen)
{
    Apple *a = malloc(sizeof(Apple));
    a->radius = r;
    a->green = isGreen;
    Fruit *f = malloc(sizeof(Fruit));
    f->self = a;
    f->GetColor = (char *(*)(void *)) AppleGetColor;
    f->GetVolume = (double (*)(void *)) AppleGetVolume;
    return f;
}

int main()
{
    Fruit *f1 = CreateApple(0.2, 0);
    Fruit *f2 = CreateApple(0.4, 1);
    Fruit *f3 = CreateBanana(0.5, 2);
    Fruit *f4 = CreateBanana(0.4, 3);

    printf("Fruit 1 is %s and has volume %f\n", FruitGetColor(f1), FruitGetVolume(f1));
    printf("Fruit 2 is %s and has volume %f\n", FruitGetColor(f2), FruitGetVolume(f2));
    printf("Fruit 3 is %s and has volume %f\n", FruitGetColor(f3), FruitGetVolume(f3));
    printf("Fruit 4 is %s and has volume %f\n", FruitGetColor(f4), FruitGetVolume(f4));
}
