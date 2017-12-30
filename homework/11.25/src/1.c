#include "lazy.h"
#define STKSIZE 100

//Homework:
//c=3,result=20
//c=7,result=53

int stack[STKSIZE];
char dist[100];

int i = 0;

int push(int x)
{
    if (i > STKSIZE)
    {
        BOOM("Boomstack");
        return -1;
    }
    stack[i++] = x;
    return 0;
}

int pop()
{
    if(i==0){
        BOOM("Empty stack!");
        return 0;
    }
    return stack[--i];
}

int itoh_bitver(unsigned int x, char *s)
{
    int word;
    int i = 0;
    do
    {
        word = x & 0xf;
        word += (word >= 10 ? 'a' : '0');
        s[i++] = word;
        x >>= 4;
    } while (x != 0);
    return 0;
}

int getword(char *src, char *dist)
{
    static int position = 0;
    int inword = 0;
    int chr;
    int i = 0;
    while ((chr = src[position++]) != '\0')
    {
        if (!inword)
        {
            if (chr == '0')
            {
                continue;
            }
            else
            {
                inword = 1;
                dist[i++] = chr;
            }
        }
        else
        {
            if (chr == ' ')
            {
                inword = 0;
                dist[i++] = '\0';
                return 1;
            }
            else
            {
                dist[i++] = chr;
            }
        }
    }
    return 0;
}

char temp[100];
char test[100] = {1, ' ', '2', ' ', '+'};



int main()
{
    LICENSE;

    //Test getword function
    SHOWALL(temp, "char");
    SHOWALL(test, "char");

    getword(test, temp);
    SHOWALL(temp, "char");
    SHOWALL(test, "char");
    getword(test, temp);

    SHOWALL(temp, "char");
    SHOWALL(test, "char");
    CK(strlen(temp));
}
//请收下我的膝盖
