#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ull unsigned long long
// #define Item int
// #define key(x) (x)
#define less(a, b) (a.value == b.value ? a.key < b.key : a.value < b.value)
#define less2(a, b) (a.key == b.key ? a.value < b.value : a.key < b.key)
#define swap(a, b)  \
    {               \
        Item t = a; \
        a = b;      \
        b = t;      \
    }
#define cmpswap(a, b) \
    if (less(b, a))   \
    swap(a, b)
#define cmpswap2(a, b) \
    if (less2(b, a))   \
    swap(a, b)

typedef struct
{
    long long key;
    int value;
} Item;

int partition2(Item *v, int l, int r)
{
    Item pivot = v[r];
    int j = l;
    for (int k = l; k < r; k++)
        if (less2(v[k], pivot))
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
    cmpswap2(v[l], v[r - 1]);
    cmpswap2(v[l], v[r]);
    cmpswap2(v[r - 1], v[r]);

    int m = partition2(v, l, r);
    quicksortM3(v, l, m - 1);
    quicksortM3(v, m + 1, r);
}

void insertionsort(Item *v, int l, int r)
{
    for (int i = l + 1, j; i <= r; i++)
    {
        Item t = v[i];
        for (j = i; j > 0 && less2(t, v[j - 1]); j--)
            v[j] = v[j - 1];
        v[j] = t;
    }
}

void quicksort2(Item *v, int l, int r)
{
    quicksortM3(v, l, r);
    insertionsort(v, l, r);
}

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

void quickselect(Item *v, int l, int r, int i)
{
    cmpswap(v[(l + r) / 2], v[r]);
    cmpswap(v[l], v[(l + r) / 2]);
    cmpswap(v[r], v[(l + r) / 2]);

    int m = partition(v, l, r);
    if (m > i)
        quickselect(v, l, m - 1, i);
    else if (m < i)
        quickselect(v, m + 1, r, i);
}

Item v[10000001];

void solve()
{
    int k;
    scanf(" %d", &k);
    int n;
    for (n = 0; scanf(" %lld %d", &v[n].key, &v[n].value) == 2; n++);

    quickselect(v, 0, n - 1, k - 1);
    quicksort2(v, 0, k - 1);

    for (int i = 0; i < k; i++)
        printf("%lld %d\n", v[i].key, v[i].value);
}

int main()
{
    solve();

    return 0;
}
