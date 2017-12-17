#include <ctype.h>
#include <stdio.h>
#include "getch.c"

int getint(int *ip)
{
    int c, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }
    sign = ((c == '-' )? -1 : 1);
    if(c=='+'||c=='-')
        c = getch();
    for (*ip = 0; isdigit(c); c = getch())
    {
        *ip = 10 * (*ip) + c - '0';
    }
    *ip *= sign;
    if(c!=EOF)
        ungetch(c);
    return *ip;
}

int main()
{
    int a;
    getint(&a);
    printf("%p", a);
    void *b;
    b = &a;
    b++;
    printf("%p", b);
    getchar();
    
}