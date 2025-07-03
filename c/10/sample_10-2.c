/**
【サンプル10-2】
* ⾓周波数を計算するサンプル
* 定数・関数マクロのあるプログラムの練習
*/
#include <stdio.h>
// 定数「PI」が定義されていなければ定義を⾏う処理 (プリプロセッサ)
#ifndef PI
// 定数の宣⾔
#define PI 3.14
// 関数マクロの宣⾔
#define OMG(f) (2.0 * PI * f)
#endif
/**
 * main 関数
 */
int main()
{
    // ⼊⼒した値を格納する変数
    float f, omega;
    // 周波数を⼊⼒
    printf("周波数 f = ");
    scanf("%f", &f);
    // 関数マクロを実⾏し，結果を変数に格納する
    omega = OMG(f);
    printf("周波数 = %f [Hz]\n", f);
    printf("角周波数 = %f [rad/s]\n", omega);
    return 0;
}