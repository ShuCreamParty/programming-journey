/*
    myfunc.c

    与えられた数値から、最小値・最大値を出力する関数を設定するプログラム
    作成者:宮﨑 九十九
    作成日:2025/07/09
*/

#include "myfunc.h"
#include <stdio.h>

// いろんな関数
int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

void min_max(int n)
{

    // 整数の宣言
    int small, big, k[n];

    // 数値の入力
    for (int _ = 0; _ < n; _++)
    {
        printf("%d番目の値 : ", _ + 1);
        scanf("%d", &k[_]);
    }

    small = k[0];
    big = k[0];

    // 演算
    for (int j = 1; j < n; j++)
    {
        small = min(small, k[j]);
        big = max(big, k[j]);
    }

    // 結果表示
    printf("\n最小値 : %d\n", small);
    printf("最大値 : %d\n", big);
}