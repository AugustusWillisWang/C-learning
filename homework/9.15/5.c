#include"inc.h"

int main()
{
    for(int y=2000;y<2101;y++){
        if((y%4==0 && y%100!=0)||(y%400==0))printf("%d\n",y);
    }
}