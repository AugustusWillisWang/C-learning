#include"lazy.h"

int cnt1(unsigned int num){
    int cnt=0;
    while(num!=0){
        if(num%2)
            cnt++;
        num=num>>1;//在c 中左移也就是所说的逻辑移位，右端补0，而右移是算数移位，左端补齐的是最高位的符号位。
        //故负数左移，有可能变成正数，但负数右移，肯定还是负数。
    }
    return cnt;
}

int choose_part(unsigned int input,int left,int right){
    if(right>left)
        BOOM("left must >= right");
    input &= (~(-1 << (left+1)));
    CK(input);
    // input >>= right;
    // input <<= right;
    input &= (-1 << (right));
    return input;
}

int eg8(){
    char c;
    unsigned char uc;
    int a, b;
    c = 0xff;
    uc = c;
    a = c;
    b = uc;
    CK(a);
    CK(b);
    return 0;
}

int eg9(){
    int org;
    int a, b, c;
    org = 0x12345678;
    a = (char)org;
    b = (short)org;
    CK(a);
    CK(b);
    org = 0x123456ff;
    a = (char)org;
    b = (short)org;
    CK(a);
    CK(b);
    return 0;
}

int eg11(){
    int a = 5, b;
    b = a++ + a++;
    CK(b);
    CK(a);
    return 0;
}

int eg12(){
    int a[] = {1, 2, 3, 4, 5};
    int i = 0,j;
    a[i] = i++;
    for (j = 0; j < 5;j++){
        CK(a[j]);
    }
    return 0;
}

int eg17(){
    for (int i = 0; i < 1000;i++){
        printf("%6d%c", i, (i % 10 == 9 || i == 999) ? '\n' : ' ');
    }
    return 0;
}

int eg18(){
    for (int i = 0; i < 100;i++){
        printf("You have %d item%s. \n", i, (i > 1) ? "s" : "");
    }
}

//main里面尝试了课上的各种操作
int main(){
    char ca=255;
    unsigned char cb = 255;
    int a = ca;
    int b = cb;
    CK(a);
    CK(b);
    a = 1;
    b = 1;
    a = b++ + b++;
    CK(a);
    CK(cnt1(-1));
    CK((-1) << 1);
    int tochoose = 99;
    tochoose = choose_part(tochoose, 4, 1);
    CK(tochoose);
    BOOM("the end");
}