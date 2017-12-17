#include<stdio.h>
#define show(x) printf("%d\t",x)
#define get(x) int x; scanf("%d",&x)
//by 王华强

int addi(int *array, int i) //长度为i的数组,将array[i-1]按升序插入到array[0:i-2]中
{
    int ns = i - 1;
    for (int t = 0; t < i;t++){
        if(array[i-1]<array[t]){
            int temp = array[i - 1];
            array[i - 1] = array[t];
            array[t] = temp;
        }
    }
}

int insertsort(int* array,int len)
{
    int i=1;
    while (i<=len)
    {
        addi(array, i);
        i++;
    }
}

int showarray(int * array,int len)
{
    for (int i = 0; i < len;i++){
        show(array[i]);
    }
    puts("");
    return 0;
}

int array1[10] = {3, 4, 6, 7, 2, 8, 3, 6, 2, 1};
int array2[10] = {6,3,6,8,34,6,36,41,2};
int array3[10] = {36, 34, 69, 777, 42, 82, 31, 2, 2, 233};

int main()
{
    insertsort(array1, 10);
    insertsort(array2, 10);
    insertsort(array3, 10);
    showarray(array1, 10);
    showarray(array2, 10);
    showarray(array3, 10);
    return 0;
}