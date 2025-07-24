/**
 * typedefを用いた構造体の活用
 */
#include <stdio.h>

// 年月日を管理する構造体
typedef struct date
{
    int year;
    int month;
    int day;
} Date;

// main関数
int main()
{
    // 構造体型の変数を宣言
    Date d;

    // 年月日を入力
    printf("年：");
    scanf("%d", &d.year);
    printf("月：");
    scanf("%d", &d.month);
    printf("日：");
    scanf("%d", &d.day);

    // 入力された年月日を出力
    printf("%04d年 %02d月 %02d日\n", d.year, d.month, d.day);

    return 0;
}
