#include"inc.h"

int
intfactorial (int input)
{
    int output = 1;
    while (input-- > 1)
    {
        output *= input;
    }
    return output;
}

int main(int argc,char* argv[])
{
    if(argc!=2){
        puts("wrong parameter!");
        return -1;
    }
    printf("%d",intfactorial(atoi(argv[1])));
    return 0;
}