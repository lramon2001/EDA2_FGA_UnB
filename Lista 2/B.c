#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) \
    int t = a;     \
    a = b;         \
    b = t;

void sort(int *v, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
            if (v[j] < v[min])
                min = j;
        SWAP(v[i], v[min]);
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
