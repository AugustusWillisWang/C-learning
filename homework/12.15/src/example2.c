#include <stdio.h>
#include <string.h>
#define MAXLINES 5000
#define ALLOCSIZE 10000
char *lineptr[MAXLINES];
int readline(char *lineptr[],int nlines);
void writelines(char *lineptr[],int nlines);
void qsort(void *lineptr[],int left,int right,int (*comp)(void*,void*));
int numcmp(const char*,const char*);
int mygetline(char*,int);
char *alloc(int);
static char allocbuf[ALLOCSIZE];
static char *allocp=allocbuf;
main(int argc,char *argv[])
{
    int nlines;
    int numberic=0;
    if (argc>1&&strcmp(argv[1],"-n")==0)
        numberic=1;
    if ((nlines=readlines(lineptr,MAXLINES))>=0)
    {
        qsort((void**)lineptr,0,nlines-1,(int (*)(void*,void*))(numberic?numcmp:strcmp));
        writelines(lineptr,nlines);
        return 0;
    }
    else
    {
        printf("input too big to sort\n");
        return 1;
    }
}

void qsort(void *v[],int left,int right,int (*comp)(void*,void*))
{
    int i,last;
    void swap(void *v[],int,int);
    if (left>=right)
        return;
    swap(v,left,(left+right)/2);
    last=left;
    for (i=left+1;i<=right;i++)
        if ((*comp)(v[i],v[left])<0)
            swap(v,++last,i);
    swap(v,left,last);
    qsort(v,left,last-1,comp);
    qsort(v,last+1,right,comp);
}
int numcmp(const char *s1,const char *s2)
{
    double v1,v2;
    v1=atof(s1);
    v2=atof(s2);
    if(v1<v2)
        return -1;
    else if (v1>v2)
        return 1;
    else
        return 0;
}

int readlines(char *lineptr[],int maxlines)
{
    int len,nlines;
    char *p,line[MAXLINES];
    nlines=0;
    while((len=mygetline(line,MAXLINES))>0)
        if (nlines>=maxlines||(p=alloc(len))==NULL)
            return -1;
        else
        {
            line[len-1]='\0';
            strcpy(p,line);
            lineptr[nlines++]=p;
        }
    return nlines;
}

void writelines(char *lineptr[],int nlines)
{
    int i;
    for (i=0;i<nlines;i++)
        printf("%s\n",lineptr[i]);
}

int mygetline(char s[],int lim){
    int i,c;
    i=0;
    while (--lim>0&&(c=getchar())!=EOF&&c!='\n')
        s[i++]=c;
    if (c=='\n')
        s[i++]='\n';
    s[i]='\0';
    return i;

}

char *alloc(int n)
{
    if (allocbuf+ALLOCSIZE-allocp>=n)
    {
        allocp+=n;
        return allocp-n;
    }
    else
        return 0;
}

void afree(char *p)
{
    if (p>=allocbuf&&p<allocbuf+ALLOCSIZE)
        allocp=p;
}

void swap(void *v[],int i,int j)
{
    void *temp;
    temp=v[i];
    v[i]=v[j];
    v[j]=temp;
}
