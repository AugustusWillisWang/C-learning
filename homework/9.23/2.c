#include<stdio.h>
#define show(x) printf(""#x":%d\t",x)
#define get(x) int x; scanf("%d",&x)
//by 王华强

int gcd(int n,int m)
{
    if(n<=0||n<=0){
        puts("NO ZERO OR NEGATIVE");
        return(-1);
    }
    while(n!=m){
        
        if(n>m){
            int temp;
            temp = n;
            n = m;
            m = temp;
        }
        //(m>=n)
            m = m % n;
            if(m==0)
                break;
    }
    return n;
}

int lcm(int n,int m)
{
    if(n<=0||n<=0){
        puts("NO ZERO OR -");
    }
    
    return n*m/gcd(n,m);
}

int main()
{
    get(n);
    get(m);
    show(gcd(n, m));
    show(lcm(n, m));
    return 0;
}