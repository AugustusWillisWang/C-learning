#ifndef _HEURISTIC_T
#define _HEURISTIC_T
#include "support.h"
#include "stdlib.h"


struct heuristic_element
{
    int a;
    int b;
    int history;
    // int weight;
};

// int history_table[BOUNDRY][BOUNDRY];

//Declare this at every level.
// struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY];

int Swap_heuristic_element(struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY], int a, int b)
{
    struct heuristic_element temp;
    temp = heuristic_list[a];
    heuristic_list[a] = heuristic_list[b];
    heuristic_list[b] = temp;
    return 0;
}

int Cmp_heuristic_element(struct heuristic_element a, struct heuristic_element b) //a have bigger weight than b
{
    if (a.history > b.history)
        return 1;
    return 0;
}

int Qsort_heuristic_element(struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY], int start, int end)
{
    if (start >= end)
        return 0;
    int middle = (start + end) / 2;
    Swap_heuristic_element(heuristic_list, middle, start);
    int now = start;
    for (int i = start + 1; i <= end; i++)
    {
        if (Cmp_heuristic_element(heuristic_list[i], heuristic_list[start]))
        {
            Swap_heuristic_element(heuristic_list, i, ++now);
        }
    }
    Swap_heuristic_element(heuristic_list, now, start);
    Qsort_heuristic_element(heuristic_list, start, now - 1);
    Qsort_heuristic_element(heuristic_list, now + 1, end);
}

int Reverse_heuristic_list(struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY], int start, int end)
{
    while (start < end)
    {
        Swap_heuristic_element(heuristic_list, start++, end--);
    }
}

int Getend_heuristic_list(struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY])
{
    int i = 0;
    while (heuristic_list[i++].history)
    {
    }
    return --i;
}

// int QSlist(struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY])
// {
//     int i = 0;
//     for (int a = 0; a < BOUNDRY; a++)
//     {
//         for (int b = 0; b < BOUNDRY; b++)
//         {
//             // if() todo
//             heuristic_list[i++].a = a;
//             heuristic_list[i++].b = b;
//             heuristic_list[i++].weight = 1; //todo
//         }
//     }

//     Qsort_heuristic_element(heuristic_list, 0, Getend_heuristic_list(heuristic_list));
// }

int AddTo_heuristic_list(struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY], int index, int a, int b, int depth, int history)
{
    heuristic_list[index].a = a;
    heuristic_list[index].b = b;
    heuristic_list[index].history=history;
}

// int history_table[BOUNDRY][BOUNDRY];
int FindIn_history_table(int history_table[BOUNDRY][BOUNDRY][LEVEL+1], int a, int b, int depth)
{
    return history_table[a][b][depth];
}

int AddTo_history_table(int history_table[BOUNDRY][BOUNDRY][LEVEL+1], int a, int b, int depth)
{
    history_table[a][b][depth] += (2 << depth);
    return history_table[a][b][depth];
}


//usage
int history_table[BOUNDRY][BOUNDRY][LEVEL+1];
// memset(history_table, 0, sizeof(int)*BOUNDRY *BOUNDRY*(LEVEL+1));

//usage
//todo
// for (int i = 0; i < HEURISTIC_BOUND;i++){
//     if(heuristic_list[i].valid){
//         //todo: do sth
//     }
// }

#endif