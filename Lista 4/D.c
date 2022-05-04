#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ull unsigned long long
#define Item struct Element
#define key(x) (x.jp)
#define less(a, b) (strcmp(key(a), key(b)) < 0)
#define less_key(a, k) (strcmp(key(a), k) < 0)
#define eq_key(a, k) (strcmp(key(a), k) == 0)
#define swap(a, b)  \
    {               \
        Item t = a; \
        a = b;      \
        b = t;      \
    }
#define cmpswap(a, b) \
    if (less(b, a))   \
    swap(a, b)

struct Element
{
    char jp[82], br[82];
};

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

int binarysearch(Item *v, int l, int r, char *x)
{
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (eq_key(v[m], x))
            return m;
        else if (less_key(v[m], x))
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

Item v[1000001];

void solve()
{
    int m, n;
    scanf(" %d %d\n", &m, &n);

    for (int i = 0; i < m; i++)
    {
        gets(v[i].jp);
        gets(v[i].br);
    }

    quicksort(v, 0, m - 1);

    while (n--)
    {
        char line[81];
        gets(line);
        char *word;
        word = strtok(line, " ");
        while (word != NULL)
        {
            int idx = binarysearch(v, 0, m - 1, word);
            printf("%s", (idx != -1 ? v[idx].br : word));
            word = strtok(NULL, " ");
            printf("%c", " \n"[word == NULL]);
        }
    }

    printf("\n");
}

int main()
{
    int t;
    scanf(" %d", &t);
    while (t--)
        solve();

    return 0;
}
