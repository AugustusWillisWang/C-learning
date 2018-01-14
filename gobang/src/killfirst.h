// Copyright (c) 2017-2018 Augustus Wang
// VCF 连续冲4/活三取胜判断

#ifndef _KILLFIRST_H
#define _KILLFIRST_H
#include "support.h"
#include "weight.h"

// #define KILLSEARCH 4
int TestKillPoint(int a, int b)
{
    if (board[a][b])
        return 0;
    //--------------1
    int i = 1;
    int incolor = Board(a - 1, b - 1);
    if (incolor == BLACK || incolor == WHITE)
    {
        while ((incolor == Board(a - i, b - i)) && i <= 5)
            i++;
        if (i >= 4)
            return 1;
    }
    //--------------2
    i = 1;
    incolor = Board(a - 1, b + 1);
    if (incolor == BLACK || incolor == WHITE)
    {
        while ((incolor == Board(a - i, b + i)) && i <= 5)
            i++;
        if (i >= 4)
            return 1;
    }
    //--------------3
    i = 1;
    incolor = Board(a + 1, b - 1);
    if (incolor == BLACK || incolor == WHITE)
    {
        while ((incolor == Board(a + i, b - i)) && i <= 5)
            i++;
        if (i >= 4)
            return 1;
    }
    //--------------4
    i = 1;
    incolor = Board(a + 1, b + 1);
    if (incolor == BLACK || incolor == WHITE)
    {
        while ((incolor == Board(a + i, b + i)) && i <= 5)
            i++;
        if (i >= 4)
            return 1;
    }
    //--------------5
    i = 1;
    incolor = Board(a, b - 1);
    if (incolor == BLACK || incolor == WHITE)
    {
        while ((incolor == Board(a, b - i)) && i <= 5)
            i++;
        if (i >= 4)
            return 1;
    }
    //--------------6
    i = 1;
    incolor = Board(a - 1, b);
    if (incolor == BLACK || incolor == WHITE)
    {
        while ((incolor == Board(a - i, b)) && i <= 5)
            i++;
        if (i >= 4)
            return 1;
    }
    //--------------7
    i = 1;
    incolor = Board(a + 1, b);
    if (incolor == BLACK || incolor == WHITE)
    {
        while ((incolor == Board(a + i, b)) && (i <= 5))
            i++;
        if (i >= 4)
            return 1;
    }
    //--------------8
    i = 1;
    incolor = Board(a, b + 1);
    if (incolor == BLACK || incolor == WHITE)
    {
        while ((incolor == Board(a, b + i)) && (i <= 5))
            i++;
        if (i >= 4)
            return 1;
    }
    return 0;
}

int killboard[BOUNDRY][BOUNDRY];

int onekillmove[BOUNDRY][BOUNDRY];

int haveonekill = 0;

int TestOneStepKill(int colornow)
{
    haveonekill = 0;
    memset(onekillmove, 0, sizeof(onekillmove));
    struct fbd_weight result;

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b] == 0)
            {
                board[a][b] = colornow;

                result = UpdateFBDWeight(a, b, 0);

                board[a][b] = 0;
                if (result.fbd == 0)
                {
                    if (Abs(result.weight) > 800)
                    {
                        haveonekill = 1;
                        onekillmove[a][b] = 1;
                    }
                }
            }
        }
    }
}

// int UpdateKillBoard(int a, int b, int color){
//     killboard[a][b] = 0;

// }
#endif