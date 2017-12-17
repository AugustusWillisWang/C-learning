#include <stdio.h>
#define MAXLEN 20
int eg20()
{
    int a=10,i;
    int arr[4]={4,5,6,7};
    int *pa=&a;
    int *ap[4]={&arr[0],&arr[1],&arr[2],&arr[3]};
    int **pp;
    pp=&pa;
    printf("a:%d,&d:%p,&pa:%p,pa:%p,*pa:%d\n",a,&a,&pa,pa,*pa);
    printf("pp:%p,*pp:%p,**pp:%d\n",pp,*pp,**pp);
    pp=&ap[0];
    for (i=0;i<4;i++)
        printf("%3d",**pp++);
        printf("\n");
        return 0;
}

int eg21()
{
    static char name1[13][15]=
    {
        "Illegal month","January","February","March","April","May","June","July",
        "August","September","October","November","December"
    };

    static char *name2[13]=
    {
        "Illegal month","January","February","March","April","May","June","July",
        "August","September","October","November","December"
    };
    printf("name[1][0]=%c\n",name1[1][0]);
    printf("name2[1][0]=%c\n",name2[1][0]);
    name2[1]=name2[2];
    printf("name2[1][0]=%c\n",name2[1][0]);
    printf("len of name1=%3ld elements totalbytes=%3ld bytes\n",sizeof(name1)/sizeof(char),sizeof(name1));
    printf("len of name2=%3ld elements totalbytes=%3ld bytes\n",sizeof(name2)/sizeof(char),sizeof(name2));
    return 0;
}

void printd(int n);
int eg22()
{
    int a=132;
    printd(a);
    return 0;
}
void printd(int n)
{
    if (n<0)
    {
        putchar("-");
        n=-n;
    }
    if (n/10)
        printd(n/10);
    putchar(n%10+'0');
}
int mygetline(char s[], int lim);
char pattern[] = "ould";
int strindex(char s[], char t[]);

int eg25(){
    char line[MAXLEN];
    int found=0;
    int strindex(char s[],char t[]);
    int mygetline(char s[],int lim);
    while (mygetline(line,MAXLEN)>0)
        if (strindex(line,pattern)>=0){
            printf("%s",line);
            found++;
            printf("%d\n",strindex(line,pattern));
        }
    return found;
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
int strindex(char s[],char t[]){
    int i,j,k;
    for (i=0;s[i]!='\0';i++){
        j=i;
        k=0;
        while(t[k]!='\0'){
            if (s[j]==t[k]){
                j++;
                k++;
            }else break;
        }
        if (k>0&&t[k]=='\0')
        return i;
    }
    return -1;
}


int main()
{
    eg20();
    eg21();
    eg22();
    eg25();
}