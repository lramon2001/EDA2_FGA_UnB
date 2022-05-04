#include "stdio.h"
#include "stdlib.h"

int countDigit(char s[], char d, int i)
{
    if (s[i] == '\0')
        return 0;
    return (s[i] == d) + countDigit(s, d, i + 1);
}

int main()
{
    char s[20];
    scanf("%s", s);
    printf("%d\n", countDigit(s, '7', 0));

    return 0;
}
