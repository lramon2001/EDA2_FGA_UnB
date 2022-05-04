#include <stdio.h>
#include <stdlib.h>

#define ull unsigned long long
#define min(a, b) (a < b ? a : b)
#define max(a, b) (b < a ? a : b)
// #define Item unsigned
#define key(x) (x)
#define less(a, b) (a.v == b.v ? a.k < b.k : a.v < b.v)
#define swap(a, b)  \
    {               \
        Item t = a; \
        a = b;      \
        b = t;      \
    }
#define cmpswap(a, b) \
    if (less(b, a))   \
    swap(a, b)

typedef struct
{
    int k, v;
} Item;

int partition(Item *v, int l, int r)
{
    Item pivot = v[r];
    int j = l;
    for (int k = l; k < r; k++)
        if (less(v[k], pivot))
        {
            swap(v[k], v[j]);
            j++;
        }
    swap(v[j], v[r]);
    return j;
}

void quicksortM3(Item *v, int l, int r)
{
    if (r - l <= 32)
        return;

    swap(v[(l + r) / 2], v[r - 1]);
    cmpswap(v[l], v[r - 1]);
    cmpswap(v[l], v[r]);
    cmpswap(v[r - 1], v[r]);

    int m = partition(v, l, r);
    quicksortM3(v, l, m - 1);
    quicksortM3(v, m + 1, r);
}

void insertionsort(Item *v, int l, int r)
{
    for (int i = l + 1, j; i <= r; i++)
    {
        Item t = v[i];
        for (j = i; j > 0 && less(t, v[j - 1]); j--)
            v[j] = v[j - 1];
        v[j] = t;
    }
}

void quicksort(Item *v, int l, int r)
{
    quicksortM3(v, l, r);
    insertionsort(v, l, r);
}

int main()
{
    char s[1010];
    while (scanf(" %s", s) == 1)
    {
        int fr[130];
        Item v[130];

        for (int i = 0; i < 130; i++)
            fr[i] = 0;

        for (int i = 0; s[i] != '\0'; i++)
            fr[s[i]]++;
        int k = 0;
        for (int i = 0; i < 130; i++)
            if (fr[i])
                v[k++] = (Item) {.k = i, .v=fr[i]};
        quicksort(v, 0, k-1);
        for (int i = 0; i < k; i++)
            printf("%d %d\n", v[i].k, v[i].v);
        printf("\n");
    }

    return 0;
}
