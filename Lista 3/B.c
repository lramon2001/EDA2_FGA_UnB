#include <stdio.h>
#include <stdlib.h>

void printarr(int *v, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d%c", v[i], (i == n - 1 ? '\n' : ' '));
}

void merge(int *a, int sizea, int *b, int sizeb)
{
    int *temp = (int *)malloc((sizea + sizeb) * sizeof(int));
    int i = 0, j = 0, k = 0;
    for (; i < sizea && j < sizeb; k++)
    {
        if (a[i] <= b[j])
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

void mergesort(int *v, int n)
{
    if (n < 2) return;
    int m = n / 2;
    mergesort(v, m);
    mergesort(&v[m], n - m);
    merge(v, m, v + m, n - m);
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int *v = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf(" %d", v + i);

    mergesort(v, n);
    printarr(v, n);

    return 0;
}
