#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main()
{
    for (int k = 1, n; scanf("%d", &n) != EOF; k++)
    {
        char name[21];
        int grade = -1;
        while (n--)
        {
            char s[21];
            int g;
            scanf("%s %d", s, &g);
            if (grade == -1 || g < grade || (g == grade && strcmp(name, s) < 0))
            {
                grade = g;
                strcpy(name, s);
            }
        }
        printf("Instancia %d\n", k);
        printf("%s\n\n", name);
    }

    return 0;
}
