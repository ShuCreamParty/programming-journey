/*
    kadai10-1.c

    与えられた整数から、ピラミッドを出力するプログラム
    制作者:宮﨑 九十九
    制作日:2025/07/03
*/

#include <stdio.h>

// プロトタイプ宣言
void pyramid(int n);

int main(void)
{

    // 整数の宣言
    int x;

    // 1~2行目
    printf("整数を入力してください : ");
    scanf("%d", &x);
    printf("\n");

    // 関数呼び出し
    pyramid(x);

    return 0;
}


void pyramid(int n)
{

    // 整数の宣言
    int i, j;

    // 3~n+2行目
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    // n+3~2n+1行目
    for (i = n - 1; i >= 1; i--)
    {
        for (j = 0; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}