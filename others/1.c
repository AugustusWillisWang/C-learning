#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 20
#define N 50
#define NAMESIZE 10
#define Elemtype node
#define True 1
#define False 0

typedef struct
{
    int class;
    long studentID;
    char studentName[NAMESIZE];
    int score;
}node;

typedef struct list
{
   node *elem;
   int length;
   int listsize;
}Sqlist;
Sqlist *L=NULL;Sqlist *L1=NULL;Sqlist *L2=NULL;Sqlist *L3=NULL;Sqlist *L4=NULL;              /*L为总线性表*//*每个list容纳一个班的学生的信息）*/

int InitList_Sq(Sqlist *L)                                        /*构造一个空的线性表L*/
{
    (*L).elem=(node*)malloc(LIST_INIT_SIZE*sizeof(node));
    if(!(*L).elem) return(0);                                   /*"0"表示fail*/
    (*L).length=0;
    (*L).listsize=LIST_INIT_SIZE;
    return 1;
}

void ListInsert_(Sqlist *L,node *e)                   /*在顺序线性表L中降序插入新元素(*L)elem[i]*/
{
    if((*L).length>=(*L).listsize)
    {
        node* newbase=(node*)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(node));
        if(!newbase)exit(0);
        (*L).elem=newbase;
        (*L).listsize+=LISTINCREMENT;
    }
    node *q=(*L).elem;
    while((*q).score>(*e).score)                             /*要求成绩降序排列*/
    {
        q++;
    }
    node *p=(*L).elem+(*L).length;
        for(;p>=q;p--) *(p+1)=*p;
        p=e;                                       /*插入的即为(*L).elem的三个属性，姓名、学号、分数*/
        (*L).length++;
}

void Insert(int class,char *studentName,long studentID,int score)
{
    node *temp=(node *)malloc(sizeof(node));
    (*temp).class=class;
    (*temp).studentID=studentID;
    (*temp).score=score;
    int i;
    for(i=0;studentName[i]!='\0';i++)
    {
        (*temp).studentName[i]=studentName[i];
    }
    (*temp).studentName[i]='\0';
    if(class==1)
        ListInsert_(L1,temp);
    if(class==2)
        ListInsert_(L2,temp);
    if(class==3)
        ListInsert_(L3,temp);
    if(class==4)
        ListInsert_(L4,temp);
}

    /*若已知学号*/
void SearchID(long ID)
{
    int i;
    for(i=0;i<(*L).length;i++)
    {
        if((*L).elem[i].studentID==ID)      /*要求用户输入需要查找的学号*/
        {
            printf("class:%3d studentID:%10ld name:%8s score:%3d\n",(*L).elem[i].class,(*L).elem[i].studentID,(*L).elem[i].studentName,(*L).elem[i].score);
            break;
        }
    }
    if(i=(*L).length) printf("Input error.");
}

    /*若已知分数*/
void Searchscore(int score)
{
    int i;
    for(i=0;i<(*L).length;i++)
    {
        if((*L).elem[i].score==score)      /*要求用户输入需要查找的分数*/
        {
            printf("class:%3d studentID:%10ld name:%8s score:%3d\n",(*L).elem[i].class,(*L).elem[i].studentID,(*L).elem[i].studentName,(*L).elem[i].score);
            break;
        }
    }
    if(i=(*L).length) printf("Input error.");
}

void MergeList(Sqlist *La,Sqlist *Lb,Sqlist *Lc)    /*先将两个线性表合并，再将两个合并完的表合并*/
{
    node *pa,*pb,*pc;
    node *pa_last,*pb_last;
    int i;
    pa=(*La).elem;pb=(*Lb).elem;
    (*Lc).listsize=(*Lc).length=(*La).length+(*Lb).length;
    pc=(*Lc).elem=(node*)malloc(LIST_INIT_SIZE*sizeof(node));
    if(!(*Lc).elem) exit(0);
    pa_last=(*La).elem+(*La).length;
    pb_last=(*Lb).elem+(*Lb).length;
    while(pa<=pa_last&&pb<=pb_last)
    {
        if(pa->score>=pb->score)
        {
            *pc++=*pa++;
        }
        else
        {
            *pc++=*pb++;
        }
        while(pa<=pa_last) *pc++=*pa++;
        while(pb<=pb_last) *pc++=*pb++;
    }
}
int main()
{
    int n1,n2,n3,n4,n;
    char ch;
    Sqlist *L;Sqlist *Lk;Sqlist *Lm;
    Sqlist a;L1=&a;Sqlist b;L2=&b;Sqlist c;L3=&c;Sqlist d;L4=&d;Sqlist e;Lk=&e;Sqlist f;Lm=&f;Sqlist g;L=&g;
    InitList_Sq(L1);
    InitList_Sq(L2);
    InitList_Sq(L3);
    InitList_Sq(L4);
    InitList_Sq(L);InitList_Sq(Lk);InitList_Sq(Lm);
    int i=-1;                          /*i初始化为-1，可保证循环体内i增加1后数组下标从0开始*/
    int class,score;long ID;char studentName[NAMESIZE];
    do
    {
        i++;
        printf("Input record %d:class ID Name score.\n",i);
        scanf("%d,%ld,%s,%d",&class,&ID,&studentName[NAMESIZE],&score);
        if(class==-1) break;
        Insert(class,studentName,ID,score);
    }while(class>=0);    /*输入"-1"代表结束输入*/
    printf("Inputing finishes.\n");
    printf("1.Insert a student's score\n 2.Merge all the lists.\n3.Search.\n4.Output total rank.\n");
    scanf("%d",&ch);
    switch(ch)
    {
        case'1':
            printf("Input class,ID,studentName and score:\n");
            scanf("%d,%ld,%s,%d",&class,&ID,studentName,&score);
            Insert(class,studentName,ID,score);
            printf("Inserting finishes!\n");
            break;
        case'2':
            MergeList(L1,L2,Lk);MergeList(L3,L4,Lm);MergeList(Lk,Lm,L);break;
        case'3':
            MergeList(L1,L2,Lk);MergeList(L3,L4,Lm);MergeList(Lk,Lm,L);
            int op;
            printf("Press 1 to search through ID and press 2 to search through score:");
            switch(op)
            {
                case'1':
                    printf("Input ID:");
                    scanf("%ld",&ID);
                    SearchID(ID);break;
                case'2':
                    printf("Input score:");
                    scanf("%d",score);
                    Searchscore(score);break;
                default:printf("Input error!");
            }
        case'4':                                 /*将L1,L2,L3,L4合并为L之后输出综合排名*/
            MergeList(L1,L2,Lk);MergeList(L3,L4,Lm);MergeList(Lk,Lm,L);
            int j;
            for(j=0;j<(*L).length;j++)
            {
                printf("%d\t%ld\t%s\t%d\n",(*L).elem[j].class,(*L).elem[j].studentID,(*L).elem[j].studentName,(*L).elem[j].score);
            }
            break;
        default:
            printf("Invalid operator!\n");
    }
    return 0;
}
