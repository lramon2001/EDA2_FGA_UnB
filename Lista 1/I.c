#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int v[1000001];

int main()
{
    int n;
    scanf("%d", &n);

    while (n--)
    {
        int x;
        scanf("%d", &x);

        v[x]++;
    }
    int ans = 0;
    for (int i = 0; i < 1000001; i++)
        ans += v[i] > 0;
    printf("%d\n", ans);

    return 0;
}
