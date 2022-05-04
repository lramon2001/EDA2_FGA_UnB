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

    swap(v[(size - 1) / 2], v[size - 2]);
    cmpswap(v[0], v[size - 2]);
    cmpswap(v[0], v[size - 1]);
    cmpswap(v[size - 2], v[size - 1]);

    int m = partition(v, size - 1);
    quicksort(v, m);
    quicksort(v + m + 1, size - m - 1);
}

int main()
{
    int n;
    scanf(" %d", &n);
    int *v = (int *)malloc(sizeof(int) * (2 * n));
    for (int i = 0; i < n; i++)
        scanf(" %d", v + i);

    quicksort(v, n);

    for (int i = 0; i < n; i++)
        printf("%d%c", v[i], " \n"[i == n-1]);

    return 0;
}
