#include <stdio.h>
#include <stdio.h>
#define SIZE 10
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp=0;
int getch(void);
void ungetch(int);
int array[SIZE];
int main()
{
    int n,getint(int*);
    for (n=0;n<SIZE&&getint (&array[n])!=EOF;n++)
    ;
    for (n=0;n<SIZE;n++)
        printf("array[%d]=%d\n",n,array[n]);
    return 0;
}

int getint(int *pn)
{
    int c,sign;
    while(isspace(c=getch()))
    ;
    if (!isdigit(c)&&c!=EOF&&c!='+'&&c!='-')
    {
        ungetch(c);
        return 0;
    }
    sign=(c=='-')?-1:1;
    if (c=='+'||c=='-')
        c=getch();
    for (*pn=0;isdigit(c);c=getch())
        *pn=10* *pn+(c-'0');
    *pn*=sign;
    if (c!=EOF)
        ungetch(c);
    return c;
}

int getch(void)
{
    return (bufp>0)?buf[--bufp]:getchar();
}

void ungetch(int c)
{
    if (bufp>=BUFSIZE)
        printf("ungetch: too many charachters\n");
    else
        buf[bufp++]=c;
}
