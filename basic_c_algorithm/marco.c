#include"lazy.h"

#define uMIN(x,y) ({\
typeof(x) _x = (x);\
typeof(y) _y = (y);\
(void) (&_x == &_y);\
_x < _y ? _x : _y; })\

#define SWAP(a,b) do{\
    typeof(a) _t=a;\
    a=b;\
    b=_t;}while(0)

#undef CK

#define CK(x) ({typeof(x) (_x)=(x);printf("track: " #x ":%d\n", _x);_x; })
//整数值追踪
//注意不要追踪会引发全局变化的函数和非整数值

// #define CK(x) ({ typeof(x) _x=x; printf("track: " #x ":%d\n", _x); })

int main(){
    CK(__COUNTER__);
    CK(__COUNTER__);
    // CK(__COUNTER__);
    CK(__COUNTER__);
    CK(__COUNTER__);
    CK(__COUNTER__);
    int a=3;
    int b = 2;
    char c = 1;
    char d = 0;
    SWAP(a, b);
    SWAP(d, c);
    CK(a);
    CK(b);
    CK(c);
    CK(d);
    CK(uMIN(1, 2));
    CK(a++);
    CK(a++);
}