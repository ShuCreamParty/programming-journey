/*
    kadai13.c

    各科目の与えられた成績から、合否結果を出力するプログラム
    制作者:宮﨑 九十九
    制作日:2025/07/15
*/

#include "myfunc13.h"
#include <stdio.h>

int main()
{

    // 構造体の宣言
    Score a[5];

    // 整数の宣言
    int result = 0;

    // 成績情報の入力
    for (int i = 0; i < 5; i++)
    {
        printf("科目名を入力してください : ");
        scanf("%s", a[i].subject);
        printf("点数を入力してください : ");
        scanf("%d", &a[i].point);
        printf("欠課時数を入力してください : ");
        scanf("%d", &a[i].absence);
    }

    for (int i = 0; i < 5; i++)
    {
        // 処理
        result = check(a[i]);

        // 結果出力
        if (result == 1)
        {
            printf("%s は合格です\n", a[i].subject);
        }
        else
        {
            printf("%s は単位を落としました\n", a[i].subject);
        }
    }

    return 0;
}