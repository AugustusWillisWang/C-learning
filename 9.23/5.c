#include<stdio.h>
#define show(x) printf(""#x":%d\t",x)
#define get(x) int x; scanf("%d",&x)
//by 王华强

int main(){
    int a=6,b=99;
    int gcd=a,lcm=a;
    for(;!(a%gcd==0&&b%gcd==0%gcd<=a&&gcd<=b);gcd--);
    show(gcd);
    for(;!(lcm%a==0&&lcm%b==0%lcm>=a&&lcm>=b);lcm++);
    show(lcm);
    return 0;
}