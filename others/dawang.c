#include <stdio.h>
#define MAX 100
int s[MAX];
void poi(int n,int k);
int main()
{
    int n,k,i;
    scanf("%d%k",&n,&k);
    for (i=0;i<n;i++)
            s[i]=1;
    poi(n,k);
    for (i=0;i<n;i++)
        if (s[i]==1)
            printf("%d ",i);
    printf("\n");
    return 0;
}

void poi(int n,int k)
{
    int m,j=0,i;
    m=n;
    while (m>=k)
    {
        s[j]=0;
        m--;
        for (i=1;i<=k;i++)
        {
            j=(j+1)%n;
            while (s[j]==0)
                j=(j+1)%n;
        }
        for (i=0;i<n;i++)
        if (s[j]==1){
            printf("%d ",i);
            puts("");
        }
    }
}

// struct node 
// {
//     int index;
//     int ndel;
//     struct node *next;
// }

// int
// checklist(int num, int step)
// {

// }