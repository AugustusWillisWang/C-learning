#include<stdio.h>
// #include<string.h>
#define LENGTH 100
//for function version,see longest2_plus.c


void clear(char* chararray){
    for (int i = 0; i < LENGTH;i++){
        chararray[i] = 0;
    }
}

int main()
{
    int max=0;
    int max2=0;
    char maxs[100];
    clear(maxs);//数组置为0
    char maxs2[100];
    clear(maxs2);
    char read[100];
    clear(read);
    // int maxlen = 100;
    int cnt = 0;//计数用变量
    int strcnt;//读入行数+1(含有EOF)
    char c; //tips 声明不分配空间 声明数组不需要指定数组长
    while(c!=EOF){
        //计数部分,读入字符串到缓冲区read
        while ((c = getchar()) != '\n' && c != EOF &&cnt<LENGTH-1)//remark: when && 前条件为假,后面的语句均不执行
        {
            read[cnt] = c;
            cnt++;
        }
        read[cnt] = '\0';
        strcnt++;
        
        //判断最大
        if (cnt > max)
        {
            max = cnt;
            for (int i = 0; read[i] != '\0';i++)
                maxs[i] = read[i];
            maxs[cnt] = '\0';

        }

        //判断次长
        if(cnt>max2&&cnt<max){
            for (int i = 0; maxs[i] != '\0';i++)
            maxs2[i] = read[i];
            maxs2[cnt] = '\0';
        }
        cnt = 0;
    }

    //输出
    if(strcnt>1)puts(maxs);
    if(strcnt>2)puts(maxs2);
    printf("%d", max);
    // printf("%s", maxs2);
    getchar();
}