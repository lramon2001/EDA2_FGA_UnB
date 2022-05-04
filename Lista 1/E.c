#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef char str[101];

typedef struct Vector
{
    int size, capacity;
    str *data;
} Vector;

Vector *newVector()
{
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    vector->capacity = 16;
    vector->size = 0;
    vector->data = (str *)malloc(vector->capacity * sizeof(str));

    return vector;
}

void deleteVector(Vector *vector)
{
    free(vector->data);
    free(vector);
}

char *vectorSpaceToAdd(Vector *vector)
{
    if (vector->size == vector->capacity)
    {
        vector->capacity = vector->capacity << 1;
        vector->data = realloc(vector->data, vector->capacity * sizeof(str));
    }
    return vector->data[vector->size++];
}

char *vectorPop(Vector *vector)
{
    if (!vector->size)
        return "NULL";
    return vector->data[--vector->size];
}

int main()
{
    char mode[10];
    Vector *vector = newVector();
    while (scanf("%s", mode) != EOF)
    {
        if (strcmp(mode, "inserir") == 0)
            scanf(" %[^\n]", vectorSpaceToAdd(vector));
        else
            printf("%s\n", vectorPop(vector));
    }
    deleteVector(vector);

    return 0;
}
