/**
【サンプル10-3】
* ⽂字を⼤⽂字・⼩⽂字に変換して出⼒する
* 関数から，さらに他の関数を呼び出す練習
*/
#include <stdio.h>
// 「A」という定数が定義されていない場合のみ，各種定数を宣⾔する
// 今回は「ifndef」や「endif」などで囲む必要はないが，練習のため記述してみよう
#ifndef A
#define A 65
#define Z 90
#define a 97
#define z 122
#endif
// 英字を⼤⽂字・⼩⽂字のそれぞれに変換して出⼒する関数
void henkan(char moji);
// 英字を⼤⽂字に変換する関数
char to_upper(char moji);
// 英字を⼩⽂字に変換する関数
char to_lower(char moji);
/**
 * メイン関数
 */
int main()
{
    char moji;
    // 英字の⼊⼒
    printf("英字 = ");
    scanf("%c", &moji);
    // ⽂字を⼤⽂字・⼩⽂字に変換して出⼒する関数を呼び出す
    henkan(moji);
    return 0;
}

/**
 * 英字を⼤⽂字・⼩⽂字のそれぞれに変換して出⼒する関数
 *
 * 仮引数︓char moji    変換対象となる⽂字
 * 戻り値︓なし
 */
void henkan(char moji)
{
    char upper = '\0';
    char lower = '\0';
    // 仮引数の⽂字が⼤⽂字の場合
    if (A <= moji && moji <= Z)
    {
        // 元の⽂字は⼤⽂字とする
        upper = moji;
        // 変換後の⽂字を代⼊する
        lower = to_lower(moji);
    }
    else if (a <= moji && moji <= z)
    {
        // 元の⽂字は⼩⽂字とする
        lower = moji;
        // 変換後の⽂字を代⼊する
        upper = to_upper(moji);
    }

    printf("⼩⽂字: %c\n", lower);
    printf("⼤⽂字: %c\n", upper);
}

/**
 * 英字を⼤⽂字に変換する関数
 *
 * 仮引数︓char moji    変換対象となる⽂字
 * 戻り値︓⼤⽂字に変換された⽂字
 */
char to_upper(char moji) { return moji - 32; }

/**
 * 英字を⼩⽂字に変換する関数
 *
 * 仮引数︓char moji    変換対象となる⽂字
 * 戻り値︓⼩⽂字に変換された⽂字
 */
char to_lower(char moji) { return moji + 32; }