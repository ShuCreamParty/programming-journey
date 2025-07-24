/*
    kadai12.c

    与えられた成績から、合否結果を出力するプログラム
    制作者:宮﨑 九十九
    制作日:2025/07/14
*/

#include <stdio.h>

// 成績情報を持つ構造体の定義
struct score
{
    int point;
    int absence;
};

// int型の関数の宣言
int check(struct score a);

int main()
{

    // 構造体の宣言
    struct score a;

    // 整数の宣言
    int result = 0;

    // 成績情報の入力
    printf("点数を入力してください : ");
    scanf("%d", &a.point);
    printf("欠課時数を入力してください : ");
    scanf("%d", &a.absence);

    // 処理
    result = check(a);

    // 結果出力
    if (result == 1)
    {
        printf("合格です\n");
    }
    else
    {
        printf("単位を落としました\n");
    }

    return 0;
}

int check(struct score a)
{
    // 判定処理
    if (a.point >= 50 && a.absence <= 15)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}