/**
 * 構造体をヘッダファイルに宣言する
 *
 * コンパイル時は「gcc -o sample13-3.exe head13.c sample13-3.c -lm」とする
 * ・複数のソースコードをきちんと指定すること
 * ・「-lm」オプションを使って，数学ライブラリをリンクしないとエラーになる場合がある
 */
#include "head13.h"
#include <stdio.h>

int main()
{
    // 座標を格納する変数
    Point p1, p2;

    // 座標をキーボードから入力する
    printf("1点目のx, y座標：");
    scanf("%d %d", &p1.x, &p1.y);
    printf("2点目のx, y座標：");
    scanf("%d %d", &p2.x, &p2.y);

    // 別ファイルにある関数を呼び出して，距離を出力する
    printf("2点間の距離 = %f\n", calc_dist(p1, p2));

    return 0;
}
