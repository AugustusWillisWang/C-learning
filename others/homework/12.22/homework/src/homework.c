#include"lazy.h"
// 定义一个结构体数组，记录下来10个学生的学号、姓名、性别、年龄。由用户输入每个学生的信息，编写排序程序，按照年龄进行排序，并按照年龄从小到大，输出每个人的全部信息到屏幕上。提交流程图和源代码。
#define SIZE_OF_NAME 30
typedef struct student{
    int id;
    int gender;
    char name[SIZE_OF_NAME];
    int age;
} student;

student list[10];

int get(int n){
    do{
    puts("id?");
    scanf("%d", &list[n].id);
    } while (0);
    do{
    puts("name?");
        scanf("%s", &list[n].name);
    } while (!strcmp(list[n].name, ""));
    do{puts("gender?");
    scanf("%d", &list[n].gender);
    } while (list[n].gender == 0 || list[n].gender == 1);
    do
    {
        puts("age?");
        scanf("%d", &list[n].age);
    }while(list[n].age<0||list[n].age>200);

}

int swap(int a,int b){
    student temp;
    temp = list[a];
    list[a] = list[b];
    list[b] = temp;
    return 0;
}

int lessthan(student a,student b)
{
    if(a.age<b.age){
        return 1;
    }
    return 0;
}

int sort(int start, int end){
    if(start>=end){
        return 0;
    }
    int middle = (start + end) / 2;
    int now = start;
    swap(start, middle);
    for (int i = start+1; i <= end;i++)
        {
            if(lessthan(list[i],list[start])){
                swap(i, ++now);
            }
        }
        swap(start, now);
        sort(start, now - 1);
        sort(now+1, end);
        return 0;
}

int outputall()
{
    puts("OUTPUTALL!\n--------------------");
    for (int i = 0; i < 10;i++){
   puts("id?");
    printf("%d\n",list[i].id);
    puts("name?");
    printf("%s\n", list[i].name);
    puts("gender?");
    printf("%d\n", list[i].gender);
    puts("age?");
    printf("%d\n", list[i].age);
    puts("------------------");
    }
}

int main()
{
    for (int i = 0; i < 10;i++){
        get(i);
    }
    sort(0, 9);
    outputall();
    return 0;
}
