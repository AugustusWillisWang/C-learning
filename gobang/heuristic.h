#ifndef _HEURISTIC_T
#define _HEURISTIC_T
#include "support.h"

struct heuristic_element
{
    int a;
    int b;
    int valid;
    double weight;
};

struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY];

int Swap_heuristic_element(int a, int b)
{
    struct heuristic_element temp;
    temp = heuristic_list[a];
    heuristic_list[a] = heuristic_list[b];
    heuristic_list[b] = temp;
    return 0;
}

int Cmp_heuristic_element(struct heuristic_element a, struct heuristic_element b) //a have bigger weight than b
{
    if (a.weight >= b.weight)
        return 1;
    return 0;
}

int Qsort_heuristic_element(int start, int end)
{
    if (start >= end)
        return 0;
    int middle = (start + end) / 2;
    Swap_heuristic_element(middle, start);
    int now = start;
    for (int i = start + 1; i <= end; i++)
    {
        if (Cmp_heuristic_element(heuristic_list[i], heuristic_list[start]))
        {
            Swap_heuristic_element(i, ++now);
        }
    }
    Swap_heuristic_element(now, start);
    Qsort_heuristic_element(start, now - 1);
    Qsort_heuristic_element(now + 1, end);
}

int Reverse_heuristic_list(int start,int end)
{
    while(start<end){
        Swap_heuristic_element(a++, b--);
    }
}

int Getend_heuristic_list(){
    int i = 0;
    while (heuristic_list[i++].valid)
    {
    }
    return --i;
}

int QSlist()
{
    int i = 0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            // if() todo
            heuristic_list[i++].a = a;
            heuristic_list[i++].b = b;
            heuristic_list[i++].weight = 1; //todo
        }
    }
    
    Qsort_heuristic_element(0, Getend_heuristic_list());
}

//usage
//todo
for (int i = 0; i < HEURISTIC_BOUND;i++){
    if(heuristic_list[i].valid){
        //todo: do sth
    }
}

#endif