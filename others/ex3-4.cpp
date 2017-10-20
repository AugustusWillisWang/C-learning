#include<cstdio>
#include<iostream>
using namespace std;
int game[6][6];
void flip(int i,int j);
int judge();
void dfs(int i,int j,int h);
int k;
int boolean=0;
int main()
{
    int i,j;
    char c;
    for (i=1;i<=4;i++)
        for (j=1;j<=4;j++)
        {
        //    cin>>c;
           scanf("%c",&c);//如果输入scanf会输出impossible
           if (c=='b') game[i][j]=1;
           else game[i][j]=0;
        }

    for (k=0;k<=16;k++)
    {
        dfs(1,1,0);
        if (boolean)
            break;
    }
    if (boolean) printf("%d\n",k);
    else printf("Impossible\n");
    return 0;
}

int judge(){
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
            if(game[i][j]!=game[1][1])
                return 0;
    return 1;
}

void flip(int i,int j)
{
    game[i][j]=!game[i][j];
    game[i+1][j]=!game[i+1][j];
    game[i-1][j]=!game[i-1][j];
    game[i][j+1]=!game[i][j+1];
    game[i][j-1]=!game[i][j-1];
}

void dfs(int i,int j,int h)
{
    if (h==k)
    {
        boolean=judge();
        return;
    }
    if (boolean||i==5) return;
    flip(i, j);
    if(j< 4) dfs(i,j+1,h+1);
    else dfs(i+1,1,h+1);

    flip(i, j);
    if(j<4) dfs(i,j+1,h);
    else dfs(i+1,1,h);
}
