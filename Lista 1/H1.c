#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        char s[101];
        scanf("%s", s);
        int sum = 0;
        for (int i = 0; s[i] != '\0' && i < 100; i++)
            sum += ('0' <= s[i] && s[i] <= '9' ? s[i] - '0' : 0);
        printf("%d\n", sum);
    }

    return 0;
}
