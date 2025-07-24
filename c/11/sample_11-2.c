#include <stdio.h>

int g_n = 0;

void test();

int main()
{
    g_n = 1;
    test();

    g_n = 2;
    test();
    g_n = 3;
    test();

    return 0;
}

void test()
{
    int temp = 0;
    temp += g_n;

    static int sum = 0;
    sum += g_n;

    printf("global g_n =%d\n", g_n);
    printf("aut temp = %d\n", temp);
    printf("static sum = %d\n\n", sum);
}