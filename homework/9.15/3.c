#include"inc.h"

int main(int argc,char* argv[])
{
    if(argc!=2){
        puts("wrong parameter!");
        return -1;
    }
    int input = atoi(argv[1]);
    int output = 1;
    int cnt = 1;
    while (cnt<=input)
    {
        output *= cnt;
        cnt += 2;
    }
    printf("%d\n", output);
    return output;
}