#include"lazy.h"

int choose(int m, int n, int max)
{
    int result = 0;
    if(m==0)
        return 1;
    if(n==0)
        return 0;
    for (int i = 0; i <= max && i <= m; i++)
    {
        result += choose(m - i, n - 1, i);
    }
    return result;
}

// int choosenormal(int m,int n)
// {
//     int result = 0;
//     return choosenormal( m, n - 1)//尾空;
// }

int calc(int m,int n)
{
    return choose(m, n, m);
}

int main()
{
    int m, n;
    GET(m);
    GET(n);
    CK(calc(m, n));
}