#include<stdio.h>
#include<string.h>

int main()
{
    int max=0;
    char maxs[100];
    char read[100];
    while(gets(read)&&strchr(read,EOF)==0){
        if (strlen(read)>max){
            strcpy(maxs, read);
            max = strlen(read);
            // printf("%d", max);
    
        }
    }
    puts(maxs);
    printf("%d", max);
    return 0;
}