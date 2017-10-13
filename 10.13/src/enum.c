#include"lazy.h"

//Also, we can use define to subsitude enum bool. 
#define TRUE 1
#define FALSE 1

enum bool//默认分配
{
    False,
    True
} a,b;

enum test //指定分配
{
    A = 1,
    B = 2
}
ins_test;

const int unchange = 233;

int main()
{
    LICENSE;
    a = True;
    b = False;
    CK(a);
    CK(b);
    ins_test = B;
    CK(ins_test);

    int i;
    CK(&i);
    i = 10;
    CK(&i);
    CK(unchange);

    //课上讲到的其他东西
    double f = (double)1;
    if(1)
        CP;
    int a = 0;
    int b = 0;
    if(++a||b++)
        ;
    CK(a);
    CK(b);
    CK(-1L < 1UL);//L被转化成unsignedlong
    CK(-1L < 1U);
}
