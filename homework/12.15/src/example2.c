#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
#define ALLOCSIZE 10000

char *lineptr[MAXLINES];
static char allocbuf[ALLOCSIZE];
static char *allocp=allocbuf;

int mygetline(char s[], int lim);
char *alloc(int n);
void afree(char *p);
void swap(char *v[], int i, int j);
int readlines(char *lineptr[], int lim);
void writelines(char *lineptr[], int nlines);
void mqsort(char *lineptr[], int left, int right, int (*comp)(char *, char *));
int numcmp(const char *s, const char *t);

int main(int argc, char *argv[])
{
    int nlines;
    int numberic=0;
    if(argc>1 && strcmp(argv[1], "-n")==0)
        numberic=1;
    if((nlines=readlines(lineptr,MAXLINES))>0)
    {
        mqsort(lineptr, 0, nlines-1, (int (*)(char*,char*))(numberic?numcmp:strcmp));
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("input too big or too short\n");
        return 1;    
    }
}

int readlines(char *lineptr[], int lim)
{
    int len, nlines;
    char *p, line[MAXLINES];
    nlines=0;
    while((len=mygetline(line, lim))>0)
    {
        if(nlines>=MAXLINES || (p=alloc(len))==0)
            return -1;
        else
        {
            line[len-1]='\0';
            strcpy(p, line);
            lineptr[nlines++]=p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int  i;
    for(i=0; i<nlines; i++)
        printf("%s\n", lineptr[i]);
}

void mqsort(char *lineptr[], int left, int right, int (*comp)(char *, char *))
{
    int i, last;
    if(left>=right)
        return ;
    swap(lineptr, left, (left+right)/2);
    last=left;
    for(i=left+1; i<=right; i++)
        if((*comp)(lineptr[i], lineptr[left])<0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    mqsort(lineptr, left, last-1, comp);
    mqsort(lineptr, last+1, right, comp);
}

int numcmp(const char *s, const char *t)
{
    if(atof(s)<atof(t))
        return -1;
    else if(atof(s)>atof(t))
        return 1;
    else 
        return 0;
}

int mygetline(char s[], int lim)
{
    int i, c;
    i=0;
    while(--lim>0 && (c=getchar())!=EOF && c!='\n')
        s[i++]=c;
    if(c=='\n')
        s[i++]='\n';
    s[i]='\0';
    return i;
}

char *alloc(int n)
{
    if(allocbuf+ALLOCSIZE-allocp>=n)
    {
        allocp+=n;
        return allocp-n;
    }
    else 
        return 0;
}

void afree(char *p)
{
    if(p>=allocbuf && p<allocbuf+ALLOCSIZE)
        allocp=p;
}

void swap(char *v[], int i, int j)
{
    void *tmp;
    tmp=v[i];
    v[i]=v[j];
    v[j]=tmp;
}
