#include<stdio.h>
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
char getch()
{
    return (bufp > 0 ? buf[--bufp] : getchar());
}
char ungetch(char t){
    if (bufp>BUFSIZE){
        printf("BOOMSTACK!");
        return -1;}
        else{
            buf[bufp++] = t;
        }
        return 0;
}