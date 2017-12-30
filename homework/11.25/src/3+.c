#include"lazy.h"

int powi(int a, int b)
{
    if(a==0)
        return 0;
    int result = 1;
    while (b-- > 0)
    {
        result *= a;
        result %= 10;
    }
    return result;
}
int main()
{
    int a, b;
    GET(a);
    GET(b);
    CK( powi(a, b));
}