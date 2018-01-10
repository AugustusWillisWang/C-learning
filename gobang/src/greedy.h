// Copyright (c) 2017-2018 Augustus Wang
// 贪婪启发, 维持一个按点赋值的全局数组, 每层迭代时先处理权值大的部分

// 目前仍存在一些问题

#ifndef _GREEDY_H
#define _GREEDY_H
#include "support.h"
#include "forbidden_move.h"

#define SEARCHRANGE2
// #define SEARCHRANGE1 1

#define _SPACE_ 1
#define _BLOCK_ 2

int (*SavePWMartix(int original_martix[BOUNDRY][BOUNDRY]))[BOUNDRY]
{
    StartTimer(7);
    int(*temp)[BOUNDRY];
    temp = (int(*)[BOUNDRY])malloc(sizeof(int) * BOUNDRY * BOUNDRY);
    memcpy(temp, original_martix, sizeof(int) * BOUNDRY * BOUNDRY);
    EndTimer(7);
    return temp;
}

int RecoveryPWMartix(int original_martix[BOUNDRY][BOUNDRY], int temp[BOUNDRY][BOUNDRY])
{
    StartTimer(8);    
    memcpy(original_martix,temp , sizeof(int) * BOUNDRY * BOUNDRY);
    free(temp);
    EndTimer(8);    
    return 0;
}

int UpdatePositionWeight(int a, int b, int color, int original_martix[BOUNDRY][BOUNDRY])
{
    StartTimer(9);
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (Board(a + x, b + y) == 0)
            {
                original_martix[a + x][b + y] += 1;
            }
        }
    }
#ifdef SEARCHRANGE2
    for (int x = -2; x <= 2; x++)
    {
        for (int y = -2; y <= 2; y++)
        {
            if (Board(a + x, b + y) == 0)
            {
                original_martix[a + x][b + y] += 1;
            }
        }
    }
#endif
    original_martix[a][b] = 0;

    int link = 0;
    int leftspace = 0;
    int rightspace = 0;
    int leftend = 0;
    int rightend = 0;
    int leftendtype = 0;
    int rightendtype = 0;
    int leftopcolor = 0;
    int rightopcolor = 0;
    for (int q = 0; q < 4; q++)
    {
        link = 1;
        leftspace = 0;
        rightspace = 0;
        leftend = 0;
        rightend = 0;
        leftendtype = 0;
        rightendtype = 0;
        leftopcolor = 0;
        rightopcolor = 0;

        //right
        for (int i = 1; i <= 6; i++)
        {
            int at = a + i * direction[q][0];
            int bt = b + i * direction[q][1];
            if (rightendtype)
            {
                int colortemp = Board(at, bt);
                if (colortemp == Inverse(color) || colortemp == OUTOFBOARD)
                {
                    rightopcolor = i;
                    break;
                }
                continue;
            }
            if (Board(at, bt) == color)
            {
                link++;
                continue;
            }
            if (Board(at, bt) == 0)
            {
                if (rightspace == 0)
                {
                    rightend = i;
                    rightspace = i;
                    continue;
                }
                else
                {
                    if (i == (rightspace + 1))
                    {
                        rightend = rightspace;
                        rightspace = 0;
                        rightendtype = _SPACE_; //1 means space
                        continue;
                    }
                    else
                    {
                        rightend = i;
                        rightendtype = _SPACE_; //1 means space
                        continue;
                    }
                }
            }
            // (Board(at,bt)==3orInverse(color))
            rightend = i;
            rightendtype = _BLOCK_;
        }

        //left
        for (int i = 1; i <= 6; i++)
        {
            int at = a - i * direction[q][0];
            int bt = b - i * direction[q][1];
            if (leftendtype)
            {
                int colortemp = Board(at, bt);
                if (colortemp == Inverse(color) || colortemp == OUTOFBOARD)
                {
                    leftopcolor = i;
                    break;
                }
                continue;
            }
            if (Board(at, bt) == color)
            {
                link++;
                continue;
            }
            if (Board(at, bt) == 0)
            {
                if (leftspace == 0)
                {
                    leftend = i;
                    leftspace = i;
                    continue;
                }
                else
                {
                    if (i == (leftspace + 1))
                    {
                        leftend = leftspace;
                        leftspace = 0;
                        leftendtype = _SPACE_; //1 means space
                        continue;
                    }
                    else
                    {
                        leftend = i;
                        leftendtype = _SPACE_; //1 means space
                        continue;
                    }
                }
            }
            // (Board(at,bt)==3orInverse(color))
            leftend = i;
            leftendtype = _BLOCK_;
        }
        // CK(leftend);
        // CK(leftendtype);
        // CK(leftspace);
        // CK(leftopcolor);
        // CK(rightend);
        // CK(rightendtype);
        // CK(rightspace);
        // CK(rightopcolor);
        // CK(link);

        int addweight = 0;
        switch (link)
        {
        case 0:
            addweight = 0;
            break;
        case 1:
            addweight = 0;
            break;
        case 2:
            addweight = 20;
            break;
        case 3:
            addweight = 100;
            break;
        case 4:
            addweight = 1000;
            break;
        case 5:
            addweight = 2500;
            break;
        }
        if (!((leftendtype == _BLOCK_) && (rightendtype == _BLOCK_) && ((leftend + rightend - 1) < 5)))
        {
            if (leftspace)
                original_martix[a - leftspace][b] += addweight;
            if (rightspace)
                original_martix[a + rightspace][b] += addweight;
            if (leftendtype == _SPACE_)
                original_martix[a - leftend][b] += addweight;
            if (rightendtype == _SPACE_)
                original_martix[a + rightend][b] += addweight;
        }
        EndTimer(9);
    }

    for (int q = 0; q < 4;q++)
    {
        for (int i = -5; i <= 5; i++)
        {
            int at = a + i * direction[q][0];
            int bt = b + i * direction[q][1];
            if (!Board(at, bt))
            {
                original_martix[at][bt]*=(!TestForbidMove(at, bt,Inverse(color)));
            }
        }
    }
}

int DBG_ShowPWM(int m[BOUNDRY][BOUNDRY])
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%d\t", m[a][b]);
        }
        puts("");
    }
}

#endif