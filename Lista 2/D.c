#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) \
    int t = a;     \
    a = b;         \
    b = t;

void sort(int *v, int size)
{
    for (int i = 1, j; i < size; i++)
    {
        int t = v[i];
        for (j = i; j > 0 && t < v[j - 1]; j--)
            v[j] = v[j - 1];
        v[j] = t;
    }
}

int main()
{
    int v[50001], size;
    for (size = 0; scanf(" %d", v + size) == 1; size++);
    sort(v, size);
    for (int i = 0; i < size; i++)
        printf("%d%c", v[i], (i == size - 1 ? '\n' : ' '));

    return 0;
}
