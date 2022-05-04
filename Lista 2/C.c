#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) \
    int t = a;     \
    a = b;         \
    b = t;

void sort(int *v, int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0; j--)
            if (v[j - 1] > v[j])
            {
                SWAP(v[j - 1], v[j]);
            }
    }
}

int main()
{
    int v[1001], size;
    for (size = 0; scanf(" %d", v + size) == 1; size++);
    sort(v, size);
    for (int i = 0; i < size; i++)
        printf("%d%c", v[i], (i == size - 1 ? '\n' : ' '));

    return 0;
}
