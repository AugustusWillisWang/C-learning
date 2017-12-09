#include <stdio.h>
#define allocsize 10000
char allocp[allocsize];
int allocnow = 0;
char *myalloc(int size)
{
    if (size + allocnow < allocsize)
    {
        allocnow += size;
        return allocp + allocnow - size;
    }
    else
    {
        return 0;
    }
}
char *myfree(int size)
{
    if (allocnow - size >= 0)
    {
        allocnow -= size;
        return allocp + allocnow;
    }
    else
    {
        return 0;
    }
}
int mystrlen(char *p)
{
    int result = 0;
    while (*p != '\0')
    {
        result++;
        p++;
    }
    return result;
}
int mystrlen2(char *p)
{
    char* c=p;
    while (*c != '\0')
    {
        c++;
    }
    return c-p;
}


int main()
{
    char a[] = "the time is now";
    char *b = "the time is now";
    puts(a);
    puts(b);
    a[0] = 'T'; 
    // b[0] = 'T';  //Will boom!
    puts(a);
    puts(b);
    printf("%p\n", myalloc(20));
    printf("%d\n", allocnow);
    myfree(30);
    printf("%d\n", allocnow);
    myfree(10);
    printf("%d\n", allocnow);
    printf("%d\n", mystrlen("gg"));
}