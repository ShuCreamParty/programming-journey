#include "head13.h"
#include <math.h>

//
/**
 * 2点の座標の情報を用いて，2点間の距離を計算する関数
 *
 * 引数： p1, p2  Point型で格納された座標情報
 * 戻り値： 2点間のユークリッド距離
 */
float calc_dist(Point p1, Point p2)
{
    // 2点間の距離を格納する変数
    float dist;

    // 各座標について，差の2乗を計算して加算する
    dist = powf(((float)p1.x - (float)p2.x), 2.0) +
           powf(((float)p1.y - (float)p2.y), 2.0);
    // 平方根を計算し，最終的な距離とする
    dist = sqrtf(dist);

    // 結果を返す
    return dist;
}