#include<stdio.h>
#include<stdlib.h>

int main()
{
    
    int cnt;
    while((p=getchar())!=EOF){
        if(p=='\n')cnt++;
    }
    printf("%d",cnt);
    return 0;
}