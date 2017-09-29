#include <stdio.h>

//It takes too much memory and it is also too complicated. For a better one, see fib2.c
int main()
{
    int num;
    scanf("%d",&num);
    if(num<=0){
        fprintf(stderr,"error");
        return -1;
    }
    //make sure that len(array)>1
    int array[num];//c11
    array[0] = 0;
    array[1] = 1;
    int i;
    for (i = 2; i <= num; i++)
    {
        array[i] = array[i - 1] + array[i - 2];
        printf("%d\n", array[i - 1]);
    }
    printf("%d\n", array[i-1]);
}