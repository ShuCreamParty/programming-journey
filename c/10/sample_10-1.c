/** 
* 計算結果を出⼒する関数を作成するサンプル 
* 関数の基本的な使い⽅に関するプログラムの練習 
*/ 
#include<stdio.h> 
// 計算をする関数のプロトタイプ宣⾔ 
void calc(int a, int b); 
int main() { 
// ⼊⼒した値を格納する変数 
int x, y; 
// 値を 2 つ⼊⼒ 
printf("x = "); 
scanf("%d", &x); 
printf("y = "); 
scanf("%d", &y); 
// 関数を呼び出す 
calc(x, y); 
// 仮引数 a に引数として渡した x を出⼒して，値を確認してみよう 
printf("%d\n", x); 
return 0; 
} 
/** 
* 値を2つ受け取って，四則演算の計算を⾏う関数 
* 
* 仮引数︓int a, int b 
* 戻り値︓なし 
*/ 
void calc(int a, int b) { 
// 仮引数a, b を⽤いて計算を⾏い，その結果を出⼒する処理 
printf("%d + %d = %d\n", a, b, a + b); 
printf("%d - %d = %d\n", a, b, a - b); 
printf("%d * %d = %d\n", a, b, a * b); 
printf("%d / %d = %d\n", a, b, a / b); 
// 仮引数の値を編集してみる (引数として渡したmain関数内の変数 x に影響があるか︖) 
a = 0; 
}