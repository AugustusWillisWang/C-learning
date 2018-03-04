#include <stdio.h>

int binsearch(int search, int *array, int length)
{
    int start = 0;
    int end = length - 1;
    int middle = (start + end) / 2;
    while ((start != end) && (array[middle] != search))
    {
        if (array[middle] > search)
            start = middle + 1;
        else
        {
            end = middle - 1;
        }
        middle = (start + end) / 2;
    }
    if (array[middle] == search)
        return middle;
    else
        return -1;
}

int a[] = {8, 6, 4, 2, 1};

// #define BUF 100
// int del_space(char* c)
// {
//     char p[BUF];
//     char *t = p;

//     while (*c != '\0')
//     {
//         if(c!=' ')
//         {
//             *t = *c;
//             t++;
//             c++;
//         }
//         else
//             c++;
//     }
//     return p;
// }
#include<type.h>
int atoi(char *c)
{
    int result = 0;
    int sign = 1;
    int havedot=0;
    int startnum = 0;
    int dotcnt=1;
    while (*c != '\0')
    {
        if (*c == ' ')
        {
            c++;
            continue;
        }
        if(*c=='-'){
            if(startnum)
                BOOM !;
            sign *= -1;
            c++;
            continue;
        }

        if(isdigit(c))
        {
            if(havedot){
                result += (c - '0') * power(10, -dotcnt);
                dotcnt++;
            }
            else{
            startnum = 1;
            result = result * 10 + c - '0';
            }
        }
        if(c=='.')
        {
            if(havedot)
                BOOM !;

            havedot = 1;
            
        }
    }
}

int main()
{
    int b = binsearch(2, a, 5);
    printf("%d", b);
}