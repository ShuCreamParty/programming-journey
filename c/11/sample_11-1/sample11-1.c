#include "head.h"
#include <stdio.h>

int get_max(int n)
{
    int temp, max;

    for (int i = 0; i < n; i++)
    {
        printf("%d 個目の値を入力 : ", i + 1);
        scanf("%d", &temp);

        if (i == 0)
        {
            max = temp;
        }
        else
        {
            if (max < temp)
            {
                max = temp;
            }
        }
    }
    return max;
}