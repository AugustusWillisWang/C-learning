#include <stdio.h>
int a,b;
int *pb,*pa;

int main()
{
    pa=&a;
    pb=&b;
    printf("addr_of_a =%p\n",&a);
    printf("addr_of_b =%p\n",&b);
    printf("data_in_pa =%p\n",pa);
    printf("data_in_pb =%p\n",pb);
    printf("size_of_a =%ld\n",sizeof(pa));
    printf("size_of_b =%ld\n",sizeof(pb));
    printf("addr_of_pa =%p\n",&pa);
    printf("addr_of_pb =%p\n",&pb);
    return 0;
}

