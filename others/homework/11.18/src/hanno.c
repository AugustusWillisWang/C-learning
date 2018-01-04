#include"lazy.h"
int step = 0;
int move(char a, char b)
{
    step++;
    printf("move %c to %c\n", a, b);
    return 0;
}

int hanno(int tomove,char a,char via, char b){
    if(tomove==1){
        move(a, b);
        return 0;
    }
    hanno(tomove - 1, a, b, via);
    move(a, b);
    hanno(tomove - 1, via, a, b);
    return 0;
}

int main(){
    int a;
    GET(a);
    hanno(a, 'A', 'B', 'C');
    CK(step);
}