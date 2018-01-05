#include<stdio.h>
void funcl();
int main(){
    funcl();
    funcl();
    funcl();
    // funcl();
    return 0;
}
void funcl(){
    int c = 0;
    static int d = 0;
    printf("%d,%d", c, d);
    c++;
    d++;
}