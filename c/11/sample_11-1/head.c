#include "head.h"
#include <stdio.h>

int main()
{
    int n;
    printf("値を入力する個数 : ");
    scanf("%d", &n);

    printf("最大値 = %d\n", get_max(n));

    return 0;
}