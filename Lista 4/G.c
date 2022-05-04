#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ull unsigned long long
#define min(a, b) (a < b ? a : b)
#define max(a, b) (b < a ? a : b)
#define Item unsigned
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

void quickselect(Item *v, int l, int r, int i)
{
    if (i < l || i > r)
        return;

    cmpswap(v[(l + r) / 2], v[r]);
    cmpswap(v[l], v[(l + r) / 2]);
    cmpswap(v[r], v[(l + r) / 2]);

    int m = partition(v, l, r);
    if (m > i)
        quickselect(v, l, m - 1, i);
    else if (m < i)
        quickselect(v, m + 1, r, i);
}

void solve()
{
    int n, p, x;
    scanf(" %d %d %d", &n, &p, &x);
    unsigned *v = malloc(n * sizeof(unsigned));
    for (int i = 0; i < n; i++)
        scanf(" %u", v + i);

    quickselect(v, 0, n-1, min(n-1, p*x));
    quickselect(v, 0, n-1, min(n-1, (p+1)*x-1));
    quicksort(v, min(n-1, p*x), min(n-1, (p+1)*x-1));

    for (int i = p*x; i < min(n, (p+1)*x); i++)
        printf("%u\n", v[i]);
}

int main()
{
    solve();

    return 0;
}
