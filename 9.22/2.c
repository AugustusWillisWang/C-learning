#include<stdio.h>
#include<stdlib.h>

int main()
{
    int cnt=0;
    while(getchar()!='\n')cnt++;
    printf("%d",cnt);
    return cnt;
}