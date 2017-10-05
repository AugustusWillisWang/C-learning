#include"lazy.h"
int main()
{
    int cnt=0;
    int c;
    for (; (c = getchar()) != EOF;)
    {
        cnt++;
        SHOW(c);
        SHOW(cnt);
    }
    puts("---------");
    SHOW(c);
    SHOW(cnt);
}