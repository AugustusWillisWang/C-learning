#include "lazy.h"

int factor(int input)
{
    for (int i = 1; i < input; i++)
    {
        if ((input % i) == 0)
        {
            printf("%d\t", i);
        }
    }
    puts("");
}

int main()
{
    for (int a = 1; a <= 1000; a++)
    {
        int sum = 0;
        for (int b = 1; b < a; b++)
        {
            if (a % b == 0)
                sum += b;
        }
        if (sum == a)
        {
            printf("comp_num:%d\n", a);
            factor(a);
        }
    }
    return 0;
}