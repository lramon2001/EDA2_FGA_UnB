#include "stdio.h"
#include "stdlib.h"

int main()
{
    int n, s = 0;
    scanf("%d", &n);
    while (n--)
    {
        int x;
        scanf("%d", &x);
        s += x;
    }
    printf("%d\n", s);

    return 0;
}
