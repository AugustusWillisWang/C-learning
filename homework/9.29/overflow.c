#include<stdio.h>
int main(){
    int i=0;
    while(i+1>i)i++;
    printf("%d\n",i);//
    printf("%d\n",i+1);
    printf("%d\n",sizeof(99999999999999999999));//编译器自动解释为long int
    printf("%d\n",077);//8进制整数常量

}