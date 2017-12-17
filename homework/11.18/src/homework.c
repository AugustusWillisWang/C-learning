#include"lazy.h"
//fib by recursion.
//can do faster by array.
//can be O(n) by writting out the General Term Formula;
int fib(long long int n){
    if(n==0)
        return 1;
    if(n==1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int whenitbooms(){
    long long int a = 1;
    long long int b=1;
    int cnt = 2;
    do{
        a = b;
        cnt++;
        b = fib(cnt);
        // CK(b);
        // CK(a);
        // CK(b > a);
    } while (b > a);
    CK(cnt);//returned 45. Stack not boomed, exciting!
}
int main(){
    // whenitbooms();
    int a;
    GET(a);
    if(a>45)
        BOOM("too big!");
    printf("%ld", fib((long long int)a));
}