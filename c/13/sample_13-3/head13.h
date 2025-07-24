#ifndef HEAD13_H

#define HEAD13_H 1

// 座標 (x, y)の情報を格納する構造体
typedef struct _point
{
    int x;
    int y;
} Point;

// 2点の座標の情報を用いて，2点間の距離を計算する関数
float calc_dist(Point p1, Point p2);

#endif