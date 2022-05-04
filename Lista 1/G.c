#include "stdio.h"
#include "stdlib.h"

typedef struct Vector
{
    int size, capacity;
    int *data;
} Vector;

Vector *newVector()
{
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    vector->capacity = 16;
    vector->size = 0;
    vector->data = (int *)malloc(vector->capacity * sizeof(int));

    return vector;
}

void deleteVector(Vector *vector)
{
    free(vector->data);
    free(vector);
}

void vectorPush(Vector *vector, int n)
{
    if (vector->size == vector->capacity)
    {
        vector->capacity = vector->capacity << 1;
        vector->data = realloc(vector->data, vector->capacity * sizeof(int));
    }
    vector->data[vector->size++] = n;
}

void solve(Vector *v, int m, int s, int i)
{
    if (i == v->size)
        return;
    s += v->data[i];
    if (s > m)
    {
        solve(v, m, 0, i + 1);
        printf("%d\n", v->data[i]);
    }
    else
        solve(v, m, s, i + 1);
}

int main()
{
    Vector *v = newVector();
    for (;;)
    {
        int n;
        scanf(" %d", &n);
        if (!n)
            break;
        vectorPush(v, n);
    }

    int m;
    scanf(" %d", &m);
    solve(v, m, 0, 0);

    return 0;
}
