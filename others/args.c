#include<stdlib.h>
#include<stdarg.h>
#include<stdio.h>

int foo(int fms,...){
    va_list va;
    int n=999;
    va_start(va, fms);
    int lists[n];
    int a = va_arg(va, int);
    double b = va_arg(va, double);
    fprintf(stderr, "%d\n", sizeof(lists));
}
int main()
{
    foo(1, 2, 33.33);
    // system("dir");
}