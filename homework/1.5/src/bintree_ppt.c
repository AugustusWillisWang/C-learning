#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100
struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};
struct tnode *addtree(struct tnode*,char *);
struct tnode *talloc(void);
void treeprint(struct tnode *ptree);
char *mystrdup(char *);
int getword(char*,int);
int main()
{
    struct tnode *ptree;
    char word[MAXWORD];
    ptree=NULL;
    while (getword(word,MAXWORD)!=EOF)
    {
        if (isalpha(word[0]))
        {
            ptree=addtree(ptree,word);
        }
    }
    printf("the results are:\n");
    treeprint(ptree);
    return 0;
}

struct tnode* addtree(struct tnode* ptree,char *word)
{
    struct tnode *p;
    int cmpresult;
    if (ptree==NULL)
    {
        p=talloc();
        p->word=mystrdup(word);
        p->count=1;
        p->left=p->right=NULL;
        return p;
    }else if ((cmpresult=strcmp(word,ptree->word))==0)
    {
        ptree->count++;
    }else if (cmpresult<0)
    {
        ptree->left=addtree(ptree->left,word);
    }else
    {
        ptree->right=addtree(ptree->right,word);
    }
    return ptree;
}

struct tnode* talloc(void)
{
    return (struct tnode*)malloc(sizeof(struct tnode));
}
char *mystrdup(char *s)
{
    char *p;
    p=(char*)malloc(strlen(s)+1);
    if (p!=NULL)
        strcpy(p,s);
    return p;
}

void treeprint(struct tnode *ptree)
{
    if (ptree)
    {
        treeprint(ptree->left);
        printf("%4d %s\n",ptree->count,ptree->word);
        treeprint(ptree->right);
    }
}

int getword(char *word,int lim)
{
    int c,getch(void);
    void ungetch(int);
    char *w=word;
    while (isspace(c=getch()))
        ;
    if (c!=EOF)
        *w++=c;
    if (!isalpha(c))
    {
        *w='\0';
        return c;
    }
    for (;--lim>0;w++)
        if (!isalnum(*w=getch()))
    {
        ungetch(*w);
        break;
    }
    *w='\0';
    return word[0];
}

char buf[BUFSIZE];
int bufp=0;
int getch(void)
{
    return (bufp>0)?buf[--bufp]:getchar();
}

void ungetch(int c)
{
    if (bufp>=BUFSIZE)
        printf("ungetch:too much characters\n");
    else
        buf[bufp++]=c;
}


