#include<stdio.h>
#define show(x) printf("#x:%d\n",x)
#define get(x) int x; scanf("%d",&x)
//by 王华强

int fun(int n)
{
    int pro=1;
    while(n>0){
        pro*=n;
        n--;
    }
    return pro;
}

int main(int argc,char* argv)
{
    // int num = atoi(argv[2]);
    int num;
    scanf("%d", &num);
    int sum = 0;
    int i;
    for (int i = 1; i <= num; i++)
    {
        sum += fun(i);
    }
    printf("%d", sum);
}