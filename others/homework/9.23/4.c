#include<stdio.h>
#define show(x) printf(""#x":%d\t",x)
#define get(x) int x; scanf("%d",&x)
#include <limits.h>
//by 王华强

int main()
{
    int a[10];
    for (int i = 0; i < 10;i++){
        scanf("%d", &a[i]);
    }
    int max = INT_MIN;
    for (int i = 0; i < 10; i++)
    {
        if(a[i]>max)
            max = a[i];
    }
    show(max);
    return 0;
}