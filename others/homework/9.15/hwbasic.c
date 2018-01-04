#include"inc.h"

#define PRIME 0
#define NOPRIME 1
#define UPPER 3000
#define LOWER 100

//一个基础的实现
int
checkprime(int input)
{
    int mark = PRIME;
    int sqinput = (int)sqrt(input);//检测素数只要处理到此上限
    for (int i = 2; i <= sqinput; i++)
    {
        if(input%i==0)
            mark = NOPRIME;
    }
    return mark;
}

int main()
{
    //排除几个简单的情况议以提高运算效率(筛法)(完整筛法实现/骗分请看另一段)
    char list[UPPER+1];
    for (int i = 4; i <= UPPER;i+=2){
        list[i] = NOPRIME;
    }
    for (int i = 6; i <= UPPER;i+=3){
        list[i] = NOPRIME;
    }
    list[1] = NOPRIME;


    for (int i = 2; i <= UPPER;i++){
        if(list[i]==PRIME){
            list[i]=checkprime(i);
        }
    }

    //output
    for (int i = LOWER; i <= UPPER;i++){
        if(list[i]==PRIME){
            printf("%d\n", i);
        }
    }
    return 0;
}