#include"lazy.h"
#include<stdio.h>
int func(int p);
int a = 5;
int b = 0;
int main(int argc,char* argv){//分配栈帧:内容:参数,返回地址
    int c;
    c = 1;
    b = func(a + c);
    CK(b);
    int tt[100] = {1, 1}; //按编译器的约定, 后面的初始化为0;
    return 0;
}
int func(int p){
    int a = 1, b, c;
    {
        int a = 10;//块中定义的变量作用域为块
        b = ++a;//定义在块外, 这里的改动会影响外层
    }
    a += 100;
    c = a + b + p;
    return c;
}
//局部变量不显式初始化无意义
//全局变量, 静态变量若不显式初始化则初始化为0;