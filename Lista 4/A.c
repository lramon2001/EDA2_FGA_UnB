#include <stdio.h>
#include <stdlib.h>

#define Item int
#define key(x) (x)
#define less(a, b) (a < b)
#define swap(a, b)  \
    {               \
        Item t = a; \
        a = b;      \
        b = t;      \
    }
#define cmpswap(a, b) \
    if (less(b, a))   \
    swap(a, b)

int partition(Item *v, int size)
{
    int l = -1, r = size - 1;
    Item pivot = v[r];

    while (1)
    {
        while (less(v[++l], pivot));
        while (less(pivot, v[--r]) && r > l);

        if (l >= r)
            break;
        swap(v[l], v[r]);
    }
    swap(v[l], v[size - 1]);
    return l;
}

void quicksort(Item *v, int size)
{
    if (size < 2)
        return;

    cmpswap(v[(size - 1) / 2], v[size - 1]);
    cmpswap(v[0], v[(size - 1) / 2]);
    cmpswap(v[size - 1], v[(size - 1) / 2]);

    int m = partition(v, size);
    quicksort(v, m);
    quicksort(v + m + 1, size - m - 1);
}

void merge(Item *a, int sizea, Item *b, int sizeb)
{
    Item *temp = (Item *)malloc((sizea + sizeb) * sizeof(Item));
    int i = 0, j = 0, k = 0;
    for (; i < sizea && j < sizeb; k++)
    {
        if (key(a[i]) <= key(b[j]))
            temp[k] = a[i++];
        else
            temp[k] = b[j++];
    }

    while (i < sizea)
        temp[k++] = a[i++];
    while (j < sizeb)
        temp[k++] = b[j++];

    for (k = 0, i = 0; i < (sizea + sizeb); i++, k++)
        a[i] = temp[k];

    free(temp);
}

int remove_duplicates(Item *v, int n)
{
    int size = 1;
    for (int i = 1; i < n; i++)
        if (v[i] != v[size - 1])
            v[size++] = v[i];
    return size;
}

int main()
{
    int n;
    scanf(" %d", &n);
    int *v = (int *)malloc(sizeof(int) * (2 * n));
    for (int i = 0; i < n; i++)
        scanf(" %d", v + i);

    quicksort(v, n);

    int size = remove_duplicates(v, n);
    if (size % 2)
        v[size++] = 1000000000;

    int size_crazy = 0;
    for (int i = 0; i < size - 1; i += 2)
        v[size + size_crazy++] = v[i] + v[i + 1];

    merge(v, size, v + size, size_crazy);
    size = remove_duplicates(v, size + size_crazy);
    for (int i = 0; i < size; i += 4)
        printf("%d\n", v[i]);
    printf("Elementos: %d\n", size);

    return 0;
}
