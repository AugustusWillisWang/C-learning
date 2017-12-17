#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lazy.h"
#define BUFSIZE 2000

int swap(int *target, int a, int b);

int mqsort(int *target, int left, int right)
{
    int middle = (left + right) / 2;
    if (left >= right)
        return 0;
    swap(target, left, middle);
    int last = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (target[i] < target[left])
        {
            swap(target, i, ++last);
        }
    }
    swap(target, last, left);
    mqsort(target, left, last - 1);
    mqsort(target, last + 1, right);
    return 0;
}

int swap(int *target, int a, int b)
{
    int temp = target[a];
    target[a] = target[b];
    target[b] = temp;
}

int st[BUFSIZE];

int setup(int n)
{
    for (int i = 0; i < n; i++)
    {
        st[i] = 1;
    }
}

int next(int now,int n)
{
    do
    {
        now++;
        if (now == n)
            now = 0;
    } while (!st[now]);

    return now;
}

int main(int argc, char **argv)
{
    if(argc!=5){
        puts("parameter shoule be like -n 10 -k5");
        return 0;
    }
        int setn = 0;
        int setk = 0;
        int n;
        int k;

        while (--argc)
        {
            argv++;
            puts(*argv);
            if (setk)
            {
                sscanf(*argv, "%d", &k);
                setk = 0;
                continue;
            }
            if (setn)
            {
                sscanf(*argv, "%d", &n);
                setn = 0;
                continue;
            }
            CP;
            if (!strcmp(*argv, "-n"))
                setn = 1;
            if (!strcmp(*argv, "-k"))
                setk = 1;
            CK(argc);
    }
    if (!n && !k)
    {
        puts("wrong input!");
        return 0;
    }
    // printf("n:%d k:%d", n, k);
    CK(k);
    CK(n);

    setup(n);
    int left = n;
    int cnt = 1;
    int now = 0;
    while (left != 1)
    {
        
        if(cnt==k){
            st[now] = 0;
            cnt = 1;
            left--;
        }
        else
        {
            cnt++;
        }
            now = next(now, n);
            // CK(now);
            // SHOWALL(st, "int");
    }
    puts("The answer is:");
    CK(next(now, n) + 1);
    return 0;
}