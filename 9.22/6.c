#include<stdio.h>

int mypow(int base,int pow){
    int output=1;
    while(pow-->0){
        output*=base;
    }
    return output;
}
int main()
{
    printf("%d",mypow(9,2));
}