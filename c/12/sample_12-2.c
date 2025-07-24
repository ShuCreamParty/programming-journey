#include <stdio.h>

struct grades
{
    char name[255];
    int score;
};

int main()
{
    struct grades g1 = {"Yamada Taro", 95};
    struct grades g2 = g1;

    printf("g1 名前 : %s\n", g1.name);
    printf("g1 点数 : %d\n", g1.score);
    printf("g2 名前 : %s\n", g2.name);
    printf("g2 点数 : %d\n", g2.score);

    printf("g2 名前を入力 : ");
    scanf("%s", g2.name);
    printf("g2 点数を入力 : ");
    scanf("%d", &g2.score);

    printf("g1 名前 : %s\n", g1.name);
    printf("g1 点数 : %d\n", g1.score);
    printf("g2 名前 : %s\n", g2.name);
    printf("g2 点数 : %d\n", g2.score);

    return 0;
}