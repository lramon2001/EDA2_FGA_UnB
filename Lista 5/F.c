#include <stdio.h>
#include <stdlib.h>

int v[1010];

int main()
{
    int n;
    scanf(" %d", &n);

    int ans = 0, best = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf(" %d",&x);
        if (++v[x] > best)
        {
            best = v[x];
            ans = x;
        }
        else if (v[x] == best && ans < x)
            ans = x;
    }
    printf("%d\n", ans);

    return 0;
}
