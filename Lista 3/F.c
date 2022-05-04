#include <stdio.h>
#include <stdlib.h>

#define Item int
#define key(x) (x)

int search(Item *v, int n, int x)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (key(v[m]) == x)
            return 1;
        else if (key(v[m]) < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return 0;
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
    if (n < 2) return;
    int m = n / 2;
    mergesort(v, m);
    mergesort(&v[m], n - m);
    merge(v, m, v + m, n - m);
}

int main()
{
    int n;
    scanf("%d", &n);
    Item *v = (Item *)malloc(n * sizeof(Item));
    for (int i = 0; i < n; i++)
        scanf(" %d", &v[i]);

    mergesort(v, n);

    for (int x; scanf(" %d", &x) == 1;)
    {
        printf("%s\n", search(v, n, x) ? "sim" : "nao");
    }

    return 0;
}
