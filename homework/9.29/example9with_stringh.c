#include<stdio.h>
// #include<string.h>
#define LENGTH 100

void clear(char* chararray){
    for (int i = 0; i < LENGTH;i++){
        chararray[i] = 0;
    }
}

int main()
{
    int max=0;
    char maxs[100];
    char read[100];
    clear(maxs);
    clear(read);
    int cnt = 0;
    char c;//tips 声明不分配空间 声明数组不需要指定数组长
    while(c!=EOF){
        while ((c = getchar()) != '\n' && c != EOF &&cnt<LENGTH-1)//remark: when && 前条件为假,后面的语句均不执行
        {
            read[cnt] = c;
            cnt++;
        }
        read[cnt] = '\0';
        if (cnt > max)
        {
            max = cnt;
            for (int i = 0; read[i] != '\0';i++)
                maxs[i] = read[i];
            maxs[cnt] = '\0';
        }
        cnt = 0;
    }
    puts(maxs);
    printf("%d", max);
}