#include<stdio.h>
int main()
{
    void sub1();
    void sub2();
    extern int exvar;
    exvar = 100;
    sub1();
    printf("%d\n", exvar);
    exvar = 100;
    sub2();
    printf("%d\n", exvar);
    return 0;
}

void sub1(){
    extern int exvar;
    exvar += 1;

}

void sub2(){
    int exvar;
    exvar += 1;
}
int exvar;