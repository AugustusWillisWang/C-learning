#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdarg.h>
#include<time.h>
#include<ctype.h>

//大写宏
#ifndef _AWSHEAD
    #define _AWSHEAD


#define GET(x) scanf("%d", &x)
//读取整数

#define TRACK(x) (printf("track: " #x ":%d\n", x) * 0 + x)
//值追踪

#define CK(x) (printf("track: " #x ":%d\n", x) * 0 + x)
//整数值追踪
//注意不要追踪会引发全局变化的函数和非整数值

#define CP (printf("checkpoint. line:%d\n", __LINE__))
//检查点

#define BP (printf("breakpoint. line:%d\n", __LINE__), getchar())
//断点
// #define LICENSE() (printf("Augustus Wang (c) 2017\n"),printf("Compiled on %s at %s\n", __DATE__,__TIME__))
//签名

#define LICENSE (printf("%s\n", __FILE__), printf("Augustus Wang (c) 2017\n"), printf("Compiled on %s at %s\n", __DATE__, __TIME__))
//签名

#define LEN(x) (sizeof(x) / sizeof(x[0]))
//数组长度

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
//比较大小

#define BOOM(str) (fprintf(stderr, "Boomed in line%d, because of %s.\n", __LINE__, str), exit(1))
//错误处理:直接退出

#define SHOWALL(array, type) (puts("------------------------\nShow "#type" array:" #array ":"),SHOW(array,type,LEN(array)))
//显示数组值

#endif

int _getline(char s[],int lim){
    int c,i;
    i=0;
    while((c=getchar())!=EOF&&c!='\n'&&i<lim-1)
        s[i++]=c;
    if(c==EOF&&i==0)
        return -1;
    s[i]='\0';
    return i;
}

int SHOW(void* array,char* type,int length){
    if(!strcmp(type,"int")){
        int *point = (int *)array;
        for (int i = 0; i < length; i++)
        {
                if(i%10==0)
                    puts("");
                printf("%d ", *(point + i));
        }
        puts("");
    }else if(!strcmp(type,"double")){
        double *point = (double *)array;
        for (int i = 0; i < length; i++)
        {
                if(i%10==0)
                    puts("");
                printf("%lf ", *(point + i));
        }
        puts("");
    }else if(!strcmp(type,"float")){
        float *point = (float *)array;
        for (int i = 0; i < length; i++)
        {
                if(i%10==0)
                    puts("");
                printf("%d ", *(point + i));
        }
        puts("");
    }else if(!strcmp(type,"char")){
        char *point = (char *)array;
        for (int i = 0; i < length; i++)
        {
                if(i%10==0)
                    puts("");
                printf("%d ", *(point + i));
        }
        puts("");
    }else{
        // puts("No matched type!");
        BOOM("No matched type!");
    }
}

char *m_reverse(char *str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;
    // CK(length);
    int first = 0;
    int last = length - 1;
    while (first < last)
    {
        char temp = str[last];
        str[last] = str[first];
        str[first] = temp;
        first++;
        last--;
    }
    return str;
}