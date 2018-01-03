#include "myhead.h"
#include <ctype.h>
#include "binsearch.c"

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many charachters\n");
    else
        buf[bufp++] = c;
}

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}};

#include <stdio.h>
#include <ctype.h>
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }

    *w = '\0';
    return word[0];
}
// int getword(char* word, int length)
// {
//     int i = 0;
//     char t;
//     t = getchar();
//     if(t==EOF)
//         return EOF;
//     while (t != EOF && t != 0 && i < (length - 1))
//     {
//         word[i++] = t;
//     }
//     word[i] = '\0';
//     return 1;
// }

int main()
{
    char word[MAXWORD];
    struct key *p;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
        {
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;
        }

    for (p = keytab; p < keytab + NKEYS; p++)
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
    return 0;
}