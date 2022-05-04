#include <stdio.h>
#include <stdlib.h>

#define key(x) (x.curr)
#define T unsigned long long

typedef struct
{
    T curr, prev, next;
} Item;

int search(Item *v, int n, T x)
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

void mergesort(Item *v, int n)
{
    if (n < 2)
        return;
    int m = n / 2;
    mergesort(v, m);
    mergesort(&v[m], n - m);
    merge(v, m, v + m, n - m);
}

void printitem(Item x)
{
    printf("%llx %llx %llx\n", x.curr, x.prev, x.next);
}

void printprev(Item *v, int n, T x)
{
    int idx = search(v, n, x);
    if (idx == -1 || v[idx].curr == 0)
        return;
    printprev(v, n, v[idx].prev);
    printitem(v[idx]);
}

void printnext(Item *v, int n, T x)
{
    int idx = search(v, n, x);
    if (idx == -1 || v[idx].curr == 0)
        return;
    printitem(v[idx]);
    printnext(v, n, v[idx].next);
}

void printnext_until(Item *v, int n, T x, T last)
{
    int idx = search(v, n, x);
    if (idx == -1 || v[idx].curr == last)
        return;
    printf("%llx\n", v[idx].curr);
    printnext_until(v, n, v[idx].next, last);
}

Item v[250001];

int main()
{
    int n;
    for (n = 0; scanf(" %llx %llx %llx", &v[n].curr, &v[n].prev, &v[n].next) == 3; n++);

    Item ptr1 = v[0], ptr2 = v[1];
    mergesort(v, n);

    v[search(v, n, ptr1.prev)].next = ptr2.next;
    v[search(v, n, ptr2.next)].prev = ptr1.prev;

    printprev(v, n, ptr1.prev);
    printnext(v, n, ptr2.next);
    printf("\n");
    printnext_until(v, n, ptr1.curr, ptr2.next);

    return 0;
}
