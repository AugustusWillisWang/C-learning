#include<stdio.h>
#define BLANK 10
#define OTHER 11

int main()
{
    int p;
    int cnt[12];
    for(int i=0;i<12;i++){
        cnt[i]=0;
    }
    
    while((p=getchar())!='\n'){
        if(p>='0'&&p<='9'){
            cnt[p-'0']++;
            continue;
        }
        if(p==' '){
            cnt[BLANK]++;
            continue;
        }
        cnt[OTHER]++;
    }

    for(int i=0;i<10;i++){
        printf("%d\t",i);
    }
    printf("blank\t");
    printf("other\n");
    for(int i=0;i<12;i++){
        printf("%d\t",cnt[i]);
    }
    return 0;
}