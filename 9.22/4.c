#include<stdio.h>

int main()
{
    int inword=0;
    int cnt=0;
    int p;
    while((p=getchar())!='\n'){
        if (inword){
            if(p==' ')inword=0;
        }
        else{
            if(p==' '){

            }
            else{
                inword=1;
                cnt++;
            }
        }
    }
    printf("%d",cnt);
}