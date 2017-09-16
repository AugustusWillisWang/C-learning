#include"inc.h"

int
intfactorial (int input)
{
    int output = 1;
    while (input-- > 1)
    {
        output *= input;
    }
    return output;
}

int main()
{
    printf("%d",intfactorial(5));
    return 0;
}