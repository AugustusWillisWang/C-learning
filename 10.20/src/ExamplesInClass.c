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