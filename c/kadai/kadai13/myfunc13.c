/*
    myfunc13.c

    合否判定関数の定義をするプログラム
    制作者:宮﨑 九十九
    制作日:2025/07/15
*/

#include "myfunc13.h"
#include <stdio.h>

int check(Score x)
{

    // 判定処理
    if (x.point >= 50 && x.absence <= 15)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}