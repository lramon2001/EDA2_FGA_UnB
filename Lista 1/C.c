#include "stdio.h"
#include "stdlib.h"

int main()
{
    int n = 0, temp;
    while (scanf("%d", &temp) == 1) n++;
    printf("%d\n", n);

    return 0;
}
