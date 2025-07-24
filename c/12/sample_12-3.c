#include <stdio.h>

struct human
{
    float height;
    float weight;
};

float calc_bmi(struct human h);

int main()
{
    struct human h;

    printf("身長[m] : ");
    scanf("%f", &h.height);
    printf("体重[kg] : ");
    scanf("%f", &h.weight);

    printf("BMI = %f\n", calc_bmi(h));

    return 0;
}

float calc_bmi(struct human h)
{
    float bmi = h.weight / (h.height * h.height);
    return bmi;
}