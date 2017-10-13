#include"lazy.h"

int mystrlen(char* str){
    int i = 0;
    int cnt = 0;
    while (str[i++] != '\0')
    {
        cnt++;
    }
    return cnt;
}

int main()
{
    SHOW(mystrlen("pp"));
    BP;
}
