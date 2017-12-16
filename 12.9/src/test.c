#include"lazy.h"

#include <stdio.h>
#include <stdio.h>
#define SIZE 10
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp=0;
int getch(void);
void ungetch(int);
int array[SIZE];

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

int odd(){
    for (int i = 0; i < 10;i++){
        if(array[i]%2==1){
            array[i]++;
        }
    }
    SHOWALL(array, "int");
}

int right()
{
    int temp[10];
    for (int i = 0; i < 10;i++)
    {
        temp[i] = array[i] / 2;
        array[i] = array[i] / 2;
    }
    for (int i = 1; i < 10;i++)
    {
        array[i] += temp[i-1];
    }
    array[0] += temp[9];
    SHOWALL(array, "int");
    
    odd();
    SHOWALL(array, "int");
    
}

int checkfailed()
{
    for (int i = 0; i < 10; i++)
    {
        if(array[i]!=array[0])
            return 1;
    }
    return 0;
}

int main()
{
    for (int i = 0; i < 10;i++)
        getint(array+i);
    SHOWALL(array, "int");
    odd();
    while(checkfailed()){
        right();
    }
}