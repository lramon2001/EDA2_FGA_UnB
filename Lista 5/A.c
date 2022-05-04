#include <stdio.h>
#include <stdlib.h>

void solve(int n)
{
    if (!n)
        return;

    int ans = 0, counter = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf(" %d",&x);
        if (counter == 0)
        {
            ans = x;
            counter++;
        }
        else
            counter += (ans == x ? 1 : -1);
    }
    printf("%d\n", ans);
    scanf(" %d", &n);
    solve(n);
}

int main()
{
    int n;
    scanf(" %d", &n);
    solve(n);

    return 0;
}
