#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXOP 100
#define BUFSIZE 100
#define NUMBER '0'
#define MAXVAL 100 //栈的最大深度

double qiuyu(double a, double b)
{
    if(a<0)
        a = -a;
    while(a>0){
        a = a - b;
    }
    return a + b;
}

int getch(void);
void ungetch(int);

int getop(char []);
void push(double);
double pop(void);

char buf[BUFSIZE];
int bufp=0; 
int sp=0; //下一个空栈的位置
double val[MAXVAL]; //栈

int nerrorform = 1;

int boomrpn(){
bufp=0; 
sp=0; //下一个空栈的位置
    setbuf(stdin, NULL);
    nerrorform = 0;
}
int rpnmain();
int main()
{
while(1)
    rpnmain();
}

int rpnmain(){
    int type;
    double op2;
    char s[MAXOP];
    bufp=0; 
    sp=0; 
    nerrorform = 1;
    while ((type = getop(s)) != EOF && nerrorform)
    {
        switch(type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop()+pop());
                break;
            case '*':
                push(pop()*pop());
                break;
            case '-':
                op2=pop();
                push(pop()-op2);
                break;
            case '/':
                op2=pop();
                if(op2>0.000000000001||op2<-0.00000000001)
                    push(pop()/op2);
                else
                    printf("error: zero divisor\n");
                    nerrorform = 0;

                break;
            case '%':
                op2 = pop();
                if(op2>0.000000000001||op2<-0.00000000001)
                {
                    push(qiuyu(pop(),  op2));
                }
                else{
                    printf("error: zero divisor\n");
                    nerrorform = 0;
                                        
                }
                break;
            case '\n':
                if(sp==1){
                printf("\t%.8g\n", pop());
                break;}else{
                    nerrorform = 0;
                    break;
                }

            default:
                printf("error: unknown command %s\n", s);
                    nerrorform = 0;

                break;                    
        }
    }
    if(nerrorform==0){
        puts("sth went wrong");
    }
    setbuf(stdin, NULL);    
    return 0;
}

int getch(void) //取一个字符
{
    return (bufp>0)?buf[--bufp]:getchar();   
}

void ungetch(int c) //将字符压回输入
{
    if(bufp>=BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++]=c;
}

int getop(char s[])
{
    int i,c;
    while((s[0]=c=getch())==' ' || c=='\t')
        ;
    s[1]='\0';
    if(!isdigit(c) && c!='.')
        return c;
    i=0;
    if(isdigit(c))
        while(isdigit(s[++i]=c=getch()))
            ;
    if(c=='.')
        while(isdigit(s[++i]=c=getch()))
            ;
    s[i]='\0';
    if(c!=EOF)
        ungetch(c);
    return NUMBER;
}

void push(double f)
{
    if(sp<MAXVAL)
        val[sp++]=f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if(sp>0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        //此时表达式不成立
        // boomrpn();
    nerrorform = 0;
        
        return 0.0;
    }
}
