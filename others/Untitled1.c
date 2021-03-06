#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50
#define NAMESIZE 10
typedef struct node
{
    long studentID;
    char studentname[NAMESIZE];
    int score;
    int class;
}node;

struct link
{
    node data;
    struct link* next;
};

struct link *head,*head1;*head2;*head3;*head4;    /*定义四个链表的头节点指针和总表的头节点指针*/

/*新建一个链表，并设置头节点*/
struct link *AppendNode(struct link *head)
{
    struct link *p=NULL;
    node data;
    p=(struct link *)malloc(sizeof(struct link));
    if(p==NULL)
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }
    head=p;
    return head;
}

/*插入一个节点，返回插入后链表的头指针*/
struct link *InsertNode(struct link *head,node e)
{
    struct link *pr=head->next,*p=head,*temp=NULL;
    p=(struct link *)malloc(sizeof(struct link));          /*p指向带插入节点*/
    if(p=NULL)
    {
        printf("No enough memory!\n");
        exit(0);
    }
    p->next=NULL;
    p->data=e;
    if(head->next==NULL)
    {
        head->next=p;
    }
    else
    {
        while(pr->data.score>e.score&&pr->next!=NULL)
        {
            temp=pr;
            pr=pr->next;
        }
        if(pr->data.score<=e.score)
        {
            pr=temp;
            p->next=pr->next;
            pr->next=p;
        }
        else                   /*若在表尾插入新节点*/
        {
            pr->next=p;
        }
    }
    return head;
}

struct link *Init_List(struct link *head)
{
    struct link *q,*p=head->next;
    for(;p->next!=NULL;)
    {
        q=p;
        free(p);
        p=q->next;
    }
    head->next=NULL;
    return head;
}

void Init(void)
{
    Init_List(&head1);
    Init_List(&head2);
    Init_List(&head3);
    Init_List(&head4);
    Init_List(&head);
    printf("Lists have been initialized!\n");
}

struct link *Merge_List(struct link *head1,struct link *head2,struct link *head)
{
    struct link *p,*p1,*p2;
    p1=head1->next;
    p2=head2->next;
    head=p=head1;
    while(p1&&p2)
    {
        if(p1->data.score>=p2->data.score)
        {
            p->next=p1;
            p=p1;
            p1=p1->next;
        }
        else
        {
            p->next=p2;
            p=p2;
            p2=p2->next;
        }
    }
    p->next=p1?p1:p2;
    free(head2);
    return head;
}

void Merge(void)
{
    struct link *head5,*head6;
    Init_List(head);
    head5=Merge_List(head1,head2,head5);
    head6=Merge_List(head3,head4,head6);
    head=Merge_List(head5,head6,head);
}
void Search(char n[])
{
    Merge();
    struct link *p=head;
    for(;p!=NULL;p=p->next)
    {
        if(strcmp(p->data.studentname,n))
        {
            printf("score:\t%d\nclass\t%d\n",p->data.score,p->data.class);
            break;
        }
    }
    if(p==NULL) printf("Input error!\n");
}

void output(struct link *head)
{
    Merge();
    int counter=1;
    struct link *p=head;
    for(p=p->next;p!=NULL;p=p->next)
    {
        printf("%d\t%s\t%d\t%d\n",p->data.class,p->data.studentname,p->data.score,counter);
        counter++;
    }
}

int main()
{
    struct link *head=NULL,*head1=NULL;*head2=NULL;*head3=NULL;*head4=NULL;
    head=AppendNode(head);
    printf("1.Initialize a list.\n2.Insert score.\n3.Merge list.4.Search for someone.5.Output the result.\n");
    int op;
    while(scanf("%d",&op)&&op)
    {
        if(op==1)
        {
            Init();
        }
        if(op==2)
        {
            int score,c;
            char n[NAMESIZE];
            node e;
            printf("Input the class,studentID,studentname and score.(input -1 as end)\n");
            while(scanf("%d",&c)&&c!=-1)
            {
                e.class=c;
                scanf("%ld",&e.studentID);
                fgets(e.studentname,sizeof(e.studentname),stdin);
                scanf("%d",&e.score);
                if(c==1)
                {
                    head1=InsertNode(head1,e);
                }
                if(c==2)
                {
                    head2=InsertNode(head2,e);
                }
                if(c==3)
                {
                    head3=InsertNode(head3,e);
                }
                if(c==4)
                {
                    head4=InsertNode(head4,e);
                }
                else
                {
                    printf("Input error!.");
                }
            }
            printf("Inserting has been completed!\n");
        }
        if(op==3)
        {
            Merge();
        }
        if(op==4)
        {
            char n[NAMESIZE];
            printf("Input student's name:\n");
            scanf("%s",n);
            Search(n);
        }
        if(op==5)
        {
            if(head1->next!=NULL)printf("Class1 result:\nClass   Name    Grade   Ranking\n");
            output(head1);
            if(head2->next!=NULL)printf("Class2 result:\nClass   Name    Grade   Ranking\n");
            output(head2);
            if(head3->next!=NULL)printf("Class3 result:\nClass   Name    Grade   Ranking\n");
            output(head3);
            if(head4->next!=NULL)printf("Class4 result:\nClass   Name    Grade   Ranking\n");
            output(head4);
            if(head->next!=NULL)printf("Totally result:\nClass   Name    Grade   Ranking\n");
            output(head);
        }
        else
        {
            printf("Input error!\n");
        }
    }
    return 0;
}












































