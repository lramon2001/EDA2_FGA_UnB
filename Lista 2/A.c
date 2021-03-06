#include <stdio.h>
#include <stdlib.h>

void bubblesort(int *v, int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = 1; j < size; j++)
            if (v[j - 1] > v[j])
            {
                int t = v[j - 1];
                v[j - 1] = v[j];
                v[j] = t;
            }
}

int main()
{
    int v[1001], size;
    for (size = 0; scanf(" %d", v + size) == 1; size++);
    bubblesort(v, size);
    for (int i = 0; i < size; i++)
        printf("%d%c", v[i], (i == size - 1 ? '\n' : ' '));

    return 0;
}
