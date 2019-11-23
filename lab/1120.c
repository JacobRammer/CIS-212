#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap(int *array, size_t size, int i, int j)
{
    char tmp[size];
    memset(tmp, 0, size);
    memcpy(tmp, array + i * size, size);
    memcpy(array + i * size, array + j * size, size);
    memcpy(array + j * size, tmp, size);
}


int intCompare(void *a, void *b)
{
    int *ia = (int *)a;
    int *ib = (int *)b;
    if (*ia < *ib)
        return -1;
    else if (*ia > *ib)
        return 1;
    else
        return 0;
}

void sort(void *array, size_t size, int n_items, int (*intCompare)(void *, void *))
{
    for (int i = 0; i < n_items; i++)
    {
        for (int j = i+1; j < n_items; j++)
        {
            if (intCompare(array+i*size, array+j*size) > 0)
            {
                swap(array, size, i, j);
            }
        }
    }
}


int main()
{
    int a[5] = {5, 4, 3, 2, 1};
    sort((void *)a, sizeof(int), 5, intCompare);
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", a[i]);
    }
}