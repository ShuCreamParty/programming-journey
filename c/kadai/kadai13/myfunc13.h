/*
    myfunc13.h

    構造体や関数を宣言するプログラム
    制作者:宮﨑 九十九
    制作日:2025/07/15
*/

// インクルードガード
#pragma once

// 成績情報を持つ構造体の定義
typedef struct score
{
    char subject[255];
    int point;
    int absence;
} Score;

// int型の関数の宣言
int check(Score x);