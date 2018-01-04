#include "socket.h"
int main()
{
    int a;
    int b;
    int c;
    // wait(500);
    // puts("hhhhhhhhhh");
    scanf("%d", &c);
    InitializeSocket(c);
    struct position position;
    while(1){
    scanf("%d %d",&a,&b);
    position=Transfer(a, b);
    printf("%d %d\n", position.a, position.b);
    }
}