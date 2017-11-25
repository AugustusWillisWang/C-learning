#include"lazy.h"

int fact(int a)
{
    int result = 1;
    while (a>0){
        result *= a;
        a--;
        // CK(result);
    }
    return result;
}

int achooseb(int a, int b)
{
    return fact(a) / (fact(b) * fact(a - b));
}

int main()
{
    int m, n;
    GET(m);
    GET(n);
    CK(achooseb(m+n-1, n-1));
}