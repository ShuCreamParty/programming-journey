#include <stdio.h>

struct grades
{
    char name[255];
    int score;
};

int main()
{
    struct grades g1;

    printf("名前 : ");
    scanf("%s", g1.name);

    printf("点数 : ");
    scanf("%d", &g1.score);

    if (50 <= g1.score)
    {
        printf("%sさんは%d点なので、合格です\n", g1.name, g1.score);
    }
    else
    {
        printf("%sさんは%d点なので、赤点です\n", g1.name, g1.score);
    }

    return 0;
}