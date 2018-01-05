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
    if (c == 1)
        while (1)
        {
            scanf("%d %d", &a, &b);
            Transfer(a, b);
            printf("%d %d\n", OppositeMove().a, OppositeMove().b);
        }
    else
    {
        while (1)
        {
            printf("%d %d\n", OppositeMove().a, OppositeMove().b);
            scanf("%d %d", &a, &b);
            Transfer(a, b);
        }
    }
}