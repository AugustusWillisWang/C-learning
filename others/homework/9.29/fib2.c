#include <stdio.h>

int main()
{
    int num;
    scanf("%d",&num);
    if(num<=0){
        fprintf(stderr,"error");
        return -1;
    }
    int a=0, b=1;
    int cntb = 1;//the fib number b equals to
    for (; cntb <= num;cntb++){
        printf("%d\n", b);
        int temp;
        temp = a + b;
        a = b;
        b = temp;
    }
}