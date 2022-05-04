#include <stdio.h>
#include <stdlib.h>

#define ull unsigned long long
#define Item struct Element
#define key(x) (x.curr)
#define less(a, b) (key(a) < key(b))
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
    ull curr, prev, next;
};

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

int search(Item *v, int n, ull x)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (key(v[m]) == x)
            return m;
        else if (key(v[m]) < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

int is_sane(Item *v, int n, Item prev, Item target)
{
    if (prev.next == target.curr && target.prev == prev.curr)
        return 1;

    int idx = search(v, n, prev.next);
    if (idx == -1 || v[idx].prev != prev.curr)
        return 0;

    return is_sane(v, n, v[idx], target);
}

Item v[500000];

int main()
{
    int n;
    for (n = 0; scanf(" %llx %llx %llx", &v[n].curr, &v[n].prev, &v[n].next) == 3; n++);

    Item ptr1 = v[0], ptr2 = v[1];
    quicksort(v, n);

    printf("%s\n", (is_sane(v, n, ptr1, ptr2) ? "sana" : "insana"));

    return 0;
}
