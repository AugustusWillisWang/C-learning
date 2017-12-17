#include"lazy.h"

int power(int i,int pow){
    int sum = 1;
    while(pow>0){
        sum *= i;
        pow--;
    }
    return sum;
}

int main()
{
    SHOW(power(10, 3));
}