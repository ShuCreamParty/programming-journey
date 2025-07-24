/**
 * 配列と構造体
 */
#include <stdio.h>

// 文字列の最大長さ
#define STRLEN 255
// 入力データ数
#define N 3

// 年月日を管理する構造体
typedef struct _birthday
{
    char name[STRLEN];
    int month;
    int day;
} Birthday;

// main関数
int main()
{
    // 構造体型の変数を宣言
    Birthday bd[N];

    // N人分の名前，月，日を入力するループ
    for (int i = 0; i < N; i++)
    {
        printf("%d人目の名前，誕生日(月・日)を入力してください\n", i + 1);
        scanf("%s %d %d", bd[i].name, &bd[i].month, &bd[i].day);
    }

    // 入力された値を出力する
    for (int i = 0; i < N; i++)
    {
        printf("%sさんの誕生日は %02d月 %02d日です\n", bd[i].name, bd[i].month,
               bd[i].day);
    }
    return 0;
}