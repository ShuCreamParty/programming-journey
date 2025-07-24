#include <stdio.h>

int x = 1;

int main()
{
    int x = 2;

    for (int i = 0; i < 5; i++)
    {
        float x = (float)i + 1.f;

        printf("for 文 %f\n", x);
    }
    printf("main 関数内 %d\n", x);

    return 0;
}