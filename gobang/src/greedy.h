// Copyright (c) 2017-2018 Augustus Wang
// 贪婪启发, 维持一个按点赋值的全局数组, 每层迭代时先处理权值大的部分

// 目前仍存在一些问题
// 最后的版本没有用所以就没有注释了

#ifndef _GREEDY_H
#define _GREEDY_H
#include "support.h"
#include "forbidden_move.h"

#define SEARCHRANGE2
// #define SEARCHRANGE1 1

#define _SPACE_ 1
#define _BLOCK_ 2

int greedy_matrix[MAXLEVEL][BOUNDRY][BOUNDRY];
int threat_martix[BOUNDRY][BOUNDRY];

int (*SavePWMartix(int greedy_matrix[BOUNDRY][BOUNDRY]))[BOUNDRY]
//不能使用, malloc的效率太低
{
    int(*temp)[BOUNDRY];
    temp = (int(*)[BOUNDRY])malloc(sizeof(int) * BOUNDRY * BOUNDRY);
    memcpy(temp, greedy_matrix, sizeof(int) * BOUNDRY * BOUNDRY);
    return temp;
}

int RecoveryPWMartix(int greedy_matrix[BOUNDRY][BOUNDRY], int temp[BOUNDRY][BOUNDRY])
//效率太低
{
    memcpy(temp, greedy_matrix, sizeof(int) * BOUNDRY * BOUNDRY);
    free(temp);
    return 0;
}

int UpdatePositionWeight(int a, int b, int color,int level,int nextlevel)
//在当前level的基础上更新下一级(levelnext)的点赋值
{

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (Board(a + x, b + y) == 0)
            {
                greedy_matrix[nextlevel][a + x][b + y] += 1;
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
                greedy_matrix[nextlevel][a + x][b + y] += 1;
            }
        }
    }
#endif
    greedy_matrix[nextlevel][a][b] = 0;

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
        if (!((leftendtype == _BLOCK_) && (rightendtype == _BLOCK_) && ((leftopcolor + rightopcolor - 1) < 5)))
        {
            if (leftspace)
                greedy_matrix[nextlevel][a - leftspace*direction[q][0]][b-leftspace*direction[q][1]] += addweight;
            if (rightspace)
                greedy_matrix[nextlevel][a + rightspace*direction[q][0]][b+rightspace*direction[q][0]] += addweight;
            if (leftendtype == _SPACE_)
                greedy_matrix[nextlevel][a - leftend*direction[q][0]][b - leftend*direction[q][1]] += addweight;
            if (rightendtype == _SPACE_)
                greedy_matrix[nextlevel][a + rightend*direction[q][0]][b + rightend*direction[q][1]] += addweight;
        }
    }

    for (int q = 0; q < 4; q++)
    {
        for (int i = -5; i <= 5; i++)
        {
            int at = BoundLim(a + i * direction[q][0]);
            int bt = BoundLim(b + i * direction[q][1]);
            if (!Board(at, bt))
            {
                greedy_matrix[level][at][bt] *= (!ForbidMove(at, bt, Inverse(color)));
            }
        }
    }
}

// int _recordm[4][BOUNDRY];
// int SavePositionWeight(int a, int b, int color, int greedy_matrix[BOUNDRY][BOUNDRY])
// {
//         for (int i = 0; i < BOUNDRY;i++){
//             int at = 0 + direction[q][0];
//             int bt = 0 + direction[q][1];

//         }
// }
// int RecoverPositionWeight(int a, int b, int color, int greedy_matrix[BOUNDRY][BOUNDRY]){};

int UpdateThreat(int a, int b, int color, int threatcolor)
{
    threat_martix[a][b] = 0;
    if (color == threatcolor)
    {

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
            addweight = 1;
            break;
        default:
            addweight = 1;
            break;
        }
        if (!((leftendtype == _BLOCK_) && (rightendtype == _BLOCK_) && ((leftopcolor + rightopcolor - 1) < 5)))
        {
            if (leftspace)
                threat_martix[a - leftspace*direction[q][0]][b-leftspace*direction[q][1]] += addweight;
            if (rightspace)
                threat_martix[a + rightspace*direction[q][0]][b+rightspace*direction[q][0]] += addweight;
            if (leftendtype == _SPACE_)
                threat_martix[a - leftend*direction[q][0]][b - leftend*direction[q][1]] += addweight;
            if (rightendtype == _SPACE_)
                threat_martix[a + rightend*direction[q][0]][b + rightend*direction[q][1]] += addweight;
        }
        // DBG_ShowPWM(threat_martix);
    }
    }
    else if (color != threatcolor)
    {
        return 0;
        for (int q = 0; q < 4; q++)
        {
            int best = 0;
            for (int i = 1; i <= 4; i++)
            {
                if (Board(a + i * direction[q][0], b + i * direction[q][1]) == color)
                    best = i;
            }
            for (int i = 1; i < best; i++)
            {
                threat_martix[BoundLim(a + i * direction[q][0])][BoundLim(b + i * direction[q][1])] = 0;
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
            printf("%d ", m[a][b]);
        }
        puts("");
    }
}

#endif