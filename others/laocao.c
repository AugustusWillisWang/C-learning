//Linear structure and its applications
//by aw

#include <stdio.h>
#include <stdlib.h>
#define NAMESIZE 20
#define NUMBER_OF_PEOPLE 233

//-------------------------------------------
//顺序表部分

//顺序表存储单元
struct NormalTable
{
    char name[NAMESIZE];
    int grade;
}

//初始化空顺序表
struct NormalTable *
InitializeArray(int size_of_array)
{
    struct NormalTable *result;
    result = (struct NormalTable *)malloc(sizeof(NormalTable) * size_of_array);
    if (result != 0)
    {
        return result;
    }
    else
    {
        fprintf(stderr, "malloc failed.\n");
        return 0;
    }
}

//注意:顺序表的建立要考虑空元素问题,你可能需要使用额外的变量来跟踪存储情况,如下面所示的int position, int length.
//一个偷懒的做法是,在每个结构中加上是否为空的标识符,具体如何实现取决于你.

//插入顺序表中元素
int AddToArray(char *name, int grade, struct NormalTable *class, int position)
{
    //注意降序存储
    return 0;
}

//顺序表查找
int FindInArray(struct NormalTable *class, char *name, int length)
{
    //使用strcmp()
    //使用二分查找以提高效率
}

//综合排名
struct NormalTable *
MergeArray(struct NormalTable *class,
           struct NormalTable *class2,
           struct NormalTable *class3,
           struct NormalTable *class4,
           ... //长度之类的乱七八糟的)
           )
{
    result = InitializeArray(大小自己写);
    //使用类似归并排序的方法以提高效率
}

//输出
int OutputArray(struct NormalTable *class, int length)
{
    //略
}

int Array()
{
    //使用顺序表的主程序;
}
//-------------------------------------------
//链表部分

//链表存储单元
struct ChainTable
{
    char name[NAMESIZE];
    int grade;
    struct ChainTable *next;
}

//建立链表空节点(建立空链表)
//如果用此建立空链表记得保存指针位置
struct ChainTable *
InitializeChain()
{
    struct ChainTable *result;
    result = (struct ChainTable *)malloc(sizeof(ChainTable));
    if (result != 0)
    {
        return result;
    }
    else
    {
        fprintf(stderr, "malloc failed.\n");
        return 0;
    }
    result->next = 0;
    result->grade = 0;
    result->name = "";
}

//建立新节点并填充内容
struct ChainTable *
AddChain(char *name, int grade);
{
    result = InitializeChain();
    strcpy(&result->name, name);
    result->grade = grade;
    return result;
}

//链表可以使用表头,也可以不使用.
//没有要求是使用单向链表还是双向链表

//链表插入
struct ChainTable *
Insert(char *name, int grade, struct ChainTable *class)
{
    //遍历到大小合适的
    //struct ChainTable * temp=前一个.next;
    //前一个.next=AddChain(name,grade);
    //前一个.next->next=temp;
}

//链表查找
struct ChainTable *
FindInChain(char *name, struct ChainTable *class)
{
    //自己写吧
}

//链表合并
struct ChainTable *
MergeChain(struct ChainTable *class1,
           struct ChainTable *class2,
           struct ChainTable *class3,
           struct ChainTable *class4, )
{
    result = InitializeChain();
    //类似归并
    //return
}

//链表输出
int OutputChain(struct ChainTable *class)
{
    //略
}

int Chain()
{
    //使用链表的主程序
}
//-----------------------------------------------
//主程序

int main()
{
    puts("链表(1)还是顺序表(2)?\n");
    int temp;
    scanf("%d", temp);
    switch (temp)
    {
    case 1:
        Chain();
        break;
    case 2:
        Array();
        break;
    }
    return 0;
}

//-------------------------------------
//主程序示例(用在Chain(),Array()的位置)

int mymain()
{
    while (1)
    {
        puts("输入1增添数据,输入2查找数据,输入3显示数据,输入4年级排名,输入5退出.\n");
        int code = getchar();
        switch (code)
        {
        case '1':
        {
            //屏幕提示输入格式及终止格式,之后循环读入数据,直到读到终止条件时停止
            //注意异常处理(数据过多,无效数据)
            break;
        }
        case '2':
        {
            //自己写吧
            break;
        }
        //...........
        default:
        {
            puts("非法指令\n");
        }
        }
    }
}

//补充:使用额外的结构(如:带头链表)可以极大简化程序......总之看你心情了
//先声明函数再在main后使用看起来会爽一点,不过我很懒.....