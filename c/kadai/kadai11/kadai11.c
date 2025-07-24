/*
    kadai11.c

    与えられた数値から、最小値・最大値を出力するプログラム
    作成日:2025/07/09
*/

#include "myfunc.h"
#include <stdio.h>

int main(void)
{

    // 整数の宣言
    int x;

    // 数値の入力
    printf("入力する数値の個数 : ");
    scanf("%d", &x);

    // 関数呼び出し
    min_max(x);

    return 0;
}
