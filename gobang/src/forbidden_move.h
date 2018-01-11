// Copyright (c) 2017-2018 Augustus Wang
// 禁手判断相关函数
#ifndef _FBD_MOVE
#define _FBD_MOVE
#include "support.h"
#include "weight.h"
// #define ENABLEFBDMOVE
// int board[BOUNDRY][BOUNDRY];      //棋盘数据
// int BoundLim(int a)

int valid_position[BOUNDRY][BOUNDRY];
int forbid_move[BOUNDRY][BOUNDRY];
int _fbd_line[9];
int _fbdmartix[BOUNDRY * 6 - 2][BOUNDRY + 2]; //将棋盘转化为一维数组

int TestForbidMove(int a, int b, int colornow) //判断一点是否为禁手点, 读取的全局变量: board 若为禁手点, 返回1, 否则返回0
//弃用
//程序中使用ForbidMove()
{
    StartTimer(0);
    //This function assumes that the position is legal, otherwise, other function should take care of this.
    if (a != BoundLim(a) || b != BoundLim(b))
        return 0; //Just return 0.

    //White has no forbidden move;
    if (colornow == WHITE)
        return 0;
    // int fbd_Testline();
    if (board[a][b])
    {
        BOOM("fbd20");
        return 0;
    }
    int huo3 = 0;
    int huo4 = 0;
    int huo5 = 0;
    int longlink5 = 0;
    int link = 1;
    int block = 0;

    board[a][b] = BLACK;

    for (int q = 0; q < 4; q++)
    {
        for (int i = -5; i <= 5; i++)
        {
            _fbd_line[i + 5] = Board(a + i * direction[q][0], b + i * direction[q][1]);
        }
        // fbd_Testline();
        {
            for (int p = 1; p <= 4; p++)
            {
                if (_fbd_line[5 - p] == BLACK)
                    link++;
                else
                {
                    if (_fbd_line[5 - p] == 0)
                    {
                        if (_fbd_line[5 - p - 1] == BLACK)
                            continue;
                        else
                            break;
                    }
                    else
                    {
                        block++;
                        break;
                    }
                }
            }
            for (int p = 1; p <= 4; p++)
            {
                if (_fbd_line[5 + p] == BLACK)
                    link++;
                else
                {
                    if (_fbd_line[5 + p] == 0)
                    {
                        if (_fbd_line[5 + p + 1] == BLACK)
                            continue;
                        else
                            break;
                    }
                    else
                    {
                        block++;
                        break;
                    }
                }
            }

            if (link >= 3 && (block == 0)) //33FORBID
            {
                huo3++;
            }
            if (link >= 4 && (block != 2)) //44FORBID
            {
                huo4++;
            }
            if (5 == link) //5 edge enabled
            {
                huo5++;
            }
            if (link >= 5)
            { //long link forbid_move
                longlink5++;
            }

            link = 1;
            block = 0;
        }
    }

    EndTimer(0);
    //====================================
    board[a][b] = 0;
    if (huo5)
        return 0;
    if (longlink5)
        return 1;
    if (huo3 >= 2)
    {
        if (huo4 >= 1)
            return 0;
        return 1;
    }
    if (huo4 >= 2)
        return 1;

    return 0;
    //-----------------------------------------------------------
}

// int GenForbidMove(int (*valid_position)[BOUNDRY], int colornow)//已弃用
// {
//     if (colornow == WHITE)
//     {
//         for (int a = 0; a < BOUNDRY; a++)
//         {
//             for (int b = 0; b < BOUNDRY; b++)
//             {
//                 forbid_move[a][b] = 0;
//             }
//         }

//         return 0;
//     }
//     for (int a = 0; a < BOUNDRY; a++)
//     {
//         for (int b = 0; b < BOUNDRY; b++)
//         {
//             if (valid_position[a][b])
//             {
//                 valid_position[a][b] = ForbidMove(a, b, colornow);
//             }
//         }
//     }
//     return 0;
// }

// int GenValidPosition(int (*valid_position)[BOUNDRY], int colornow)//已弃用
// {
//     StartTimer(1);

//     for (int a = 0; a < BOUNDRY; a++)
//     {
//         for (int b = 0; b < BOUNDRY; b++)
//         {
//             for (int c = a - 2; c <= a + 2; c++)
//             {
//                 for (int d = b - 2; d <= b + 2; b++)
//                 {
//                     valid_position[BoundLim(c)][BoundLim(d)] = (board[BoundLim(c)][BoundLim(d)] == 0 ? 1 : 0);
//                 }
//             }
//         }
//     }
//     EndTimer(1);
// }


int ForbidMove(int a, int b, int color)//和weight.h基于相同原理, 效率低于原有禁手函数
//禁手探测, 返回1为禁手, 0为非禁手
//注意只对于空点生效
{
    if (board[a][b])
        BOOM("position must be empty!");
    if (color == WHITE)
        return 0;
    // 越界->3;
    // 黑棋->1;
    // 白棋->2;
    // 空白->0;
    int record[BOUNDRY + 2][3][3][2]; //record[link][side][color][space]
    memset(record, 0, sizeof(record));

    board[a][b] = color;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _fbdmartix[0][c + 1] = Board(a, c);
        _fbdmartix[1][c + 1] = Board(c, b);
    }

    // printf("%d ", i);

    // printf("%d ", i);

    int aplusb = a + b;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        //b=aplusb-a;
        _fbdmartix[2][c + 1] = Board(c, aplusb - c);
    }

    int aminusb = a - b;
    //b=a-aminusb
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _fbdmartix[3][c + 1] = Board(c, c - aminusb);
    }

    for (int i = 0; i < 4; i++)
    {
        //每次扫描时保留前一个节点的值, 来判断连续的几个字有两边多少气
        int p = 1;
        int incolor = 3;
        int forecolor = 3;
        int backcolor = 0;
        int link = 1;
        int side = 0;
        int space = 0;
        while (p < BOUNDRY + 2)
        {
            if (_fbdmartix[i][p++] == incolor) //连续的几个同色点
            {
                link++;
            }
            else //连续的几个同色点的末端
            {
                if ((_fbdmartix[i][p] == incolor) && (_fbdmartix[i][p - 1] == 0) && (space == 0))
                {
                    space++;
                    p++;
                    continue;
                }
                switch (incolor)
                {
                case 0: //连续的空点
                    forecolor = 0;
                    link = 1;
                    incolor = _fbdmartix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _fbdmartix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _fbdmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0)); //side 为棋形两边的气数
                    if (link >= 5)
                        record[5][side][BLACK][space]++;
                    else
                        record[link][side][BLACK][space]++;
                    incolor = _fbdmartix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _fbdmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][side][WHITE][space]++;
                    else
                        record[link][side][WHITE][space]++;
                    incolor = _fbdmartix[i][p - 1];
                    link = 1;
                    forecolor = WHITE;
                    break;
                    // side = 0;
                }
            }
        }
    }

    board[a][b] = 0;

    for (int c = -1; c <= BOUNDRY; c++)
    {
        _fbdmartix[0][c + 1] = Board(a, c);
        _fbdmartix[1][c + 1] = Board(c, b);
    }

    for (int c = -1; c <= BOUNDRY; c++)
    {
        //b=aplusb-a;
        _fbdmartix[2][c + 1] = Board(c, aplusb - c);
    }

    //b=a-aminusb
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _fbdmartix[3][c + 1] = Board(c, c - aminusb);
    }

    for (int i = 0; i < 4; i++)
    {
        //每次扫描时保留前一个节点的值, 来判断连续的几个字有两边多少气
        int p = 1;
        int incolor = 3;
        int forecolor = 3;
        int backcolor = 0;
        int link = 1;
        int side = 0;
        int space = 0;
        while (p < BOUNDRY + 2)
        {
            if (_fbdmartix[i][p++] == incolor) //连续的几个同色点
            {
                link++;
            }
            else //连续的几个同色点的末端
            {
                if ((_fbdmartix[i][p] == incolor) && (_fbdmartix[i][p - 1] == 0) && (space == 0))
                {
                    space++;
                    p++;
                    continue;
                }
                switch (incolor)
                {
                case 0: //连续的空点
                    forecolor = 0;
                    link = 1;
                    incolor = _fbdmartix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _fbdmartix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _fbdmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0)); //side 为棋形两边的气数
                    if (link >= 5)
                        record[5][side][BLACK][space]--;
                    else
                        record[link][side][BLACK][space]--;
                    incolor = _fbdmartix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _fbdmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][side][WHITE][space]--;
                    else
                        record[link][side][WHITE][space]--;
                    incolor = _fbdmartix[i][p - 1];
                    link = 1;
                    forecolor = WHITE;
                    break;
                    // side = 0;
                }
            }
        }
    }
    if (record[5][0][BLACK][0] || record[5][1][BLACK][0] || record[5][2][BLACK][0])//成5直接终止判断
        return 0;
    int huo4 = record[4][2][BLACK][0];
    int chong4 = record[5][2][BLACK][1] + record[5][1][BLACK][1] + record[5][0][BLACK][1] + record[4][1][BLACK][0];
    int huo3 = record[3][2][BLACK][0] + record[3][2][BLACK][1];
    if ((huo4 + chong4) >= 2)//44禁手
        return 1;
    if (huo3 >= 2)//33禁手
        return 1;
    return 0;
}

int TestTipForbidMove(int a, int b, int colornow) //return 1 if it is a forbidden move
{
    if (ForbidMove(a, b, colornow))
    {
        puts("Black takes forbidden move, reinput please!");
        return 1;
    }
    return 0;
}

#endif