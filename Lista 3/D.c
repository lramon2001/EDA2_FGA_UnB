#include <stdio.h>
#include <stdlib.h>

int search(int *v, int n, int x)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (v[m] == x)
            return m;
        else if (v[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return l;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int *v = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf(" %d", v + i);

    while (m--)
    {
        int x;
        scanf(" %d", &x);
        printf("%d\n", search(v, n, x));
    }

    return 0;
}
