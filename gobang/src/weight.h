//Copyright (c) 2017-2018 Augustus Wang
//weight.h
//局面分析函数, 为当前的局面打分, 同时也是一个快速的胜负判断和禁手探测实现
//支持只根据单点落子快速更新局面评分

#ifndef _WEIGHT_H
#define _WEIGHT_H
#include <stdio.h>
#include "support.h"
#include "lazy.h"

#define EDGE 3 //越棋盘界

//这里的权值是随便赋的, 反正能用就行
#define WEIGHT1_2SIDE 2  //一子2气
#define WEIGHT2_2SIDE 30 //二子2气
#define WEIGHT3_2SIDE 500
#define WEIGHT4_2SIDE 20000
#define WEIGHT1_1SIDE 1 //1子1气
#define WEIGHT2_1SIDE 10
#define WEIGHT3_1SIDE 30
#define WEIGHT4_1SIDE 500

#define WEIGHT5 100000
#define BIG_WEIGHT 80000

int _scanmartix[BOUNDRY * 6 - 2][BOUNDRY + 2]; //将棋盘转化为一维数组

// Board();

int _ShowScanMartix() //单元测试用
{
    puts("_ShowScanMartix");
    for (int a = 0; a < 6 * BOUNDRY - 2; a++)
    {
        for (int b = 0; b < BOUNDRY + 2; b++)
        {
            printf("%d ", _scanmartix[a][b]);
        }
        puts("");
    }
    puts("----------------------");
}

int FlushScanMartix() //将棋盘转化为一维数组,形如"3333000012100000003"
{

    // 越界->3;
    // 黑棋->1;
    // 白棋->2;
    // 空白->0;

    int i = 0;
    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = -1; a <= BOUNDRY; a++)
        {
            _scanmartix[i][a + 1] = Board(a, b);
        }
        i++;
    }
    // printf("%d ", i);

    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = -1; a <= BOUNDRY; a++)
        {
            _scanmartix[i][a + 1] = Board(b, a);
        }
        i++;
    }
    // printf("%d ", i);

    for (int aplusb = 0; aplusb <= 2 * BOUNDRY - 2; aplusb++)
    {
        for (int a = -1; a <= BOUNDRY; a++)
        {
            //b=aplusb-a;
            _scanmartix[i][a + 1] = Board(a, aplusb - a);
        }
        i++;
    }
    // printf("%d ", i);

    for (int aminusb = -BOUNDRY + 1; aminusb <= BOUNDRY - 1; aminusb++)
    {
        //b=a-aminusb
        for (int a = -1; a <= BOUNDRY; a++)
        {
            _scanmartix[i][a + 1] = Board(a, a - aminusb);
        }
        i++;
    }
    // printf("%d ", i);
}

int GenerateWeight() //为当前局面打分, 黑方优势为正值, 白方优势为负值
{
    StartTimer(2);

    //根据转化之后的一维数组, 判断各种棋形
    //稍加改动可以写成胜负判断, 禁手判断函数(只要比较下一子前后各种棋形的数量)
    int weight = 0.0;
    int record[BOUNDRY + 2][3][3]; //record[link][side][color]
    memset(record, 0, sizeof(record));
    FlushScanMartix(); //将棋盘转化为一维数组

    for (int i = 0; i < BOUNDRY * 6 - 2; i++)
    {
        //每次扫描时保留前一个节点的值, 来判断连续的几个字有两边多少气
        int p = 1;
        int incolor = 3;
        int forecolor = 3;
        int backcolor = 0;
        int link = 1;
        int side = 0;
        while (p < BOUNDRY + 2)
        {
            if (_scanmartix[i][p++] == incolor) //连续的几个同色点
            {
                link++;
            }
            else //连续的几个同色点的末端
            {
                switch (incolor)
                {
                case 0: //连续的空点
                    forecolor = 0;
                    link = 1;
                    incolor = _scanmartix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmartix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][BLACK]++;
                    record[link][side][BLACK]++;
                    incolor = _scanmartix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][WHITE]++;
                    record[link][side][WHITE]++;
                    incolor = _scanmartix[i][p - 1];
                    link = 1;
                    forecolor = WHITE;
                    break;
                    // side = 0;
                }
            }
        }
    }
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][2][BLACK] * WEIGHT1_2SIDE;
    weight += record[2][1][BLACK] * WEIGHT2_1SIDE;
    weight += record[2][2][BLACK] * WEIGHT2_2SIDE;
    weight += record[3][1][BLACK] * WEIGHT3_1SIDE;
    weight += record[3][2][BLACK] * WEIGHT3_2SIDE;
    weight += record[4][1][BLACK] * WEIGHT4_1SIDE;
    weight += record[4][2][BLACK] * WEIGHT4_2SIDE;

    weight += record[1][1][WHITE] * WEIGHT1_1SIDE * (-1);
    weight += record[1][2][WHITE] * WEIGHT1_2SIDE * (-1);
    weight += record[2][1][WHITE] * WEIGHT2_1SIDE * (-1);
    weight += record[2][2][WHITE] * WEIGHT2_2SIDE * (-1);
    weight += record[3][1][WHITE] * WEIGHT3_1SIDE * (-1);
    weight += record[3][2][WHITE] * WEIGHT3_2SIDE * (-1);
    weight += record[4][1][WHITE] * WEIGHT4_1SIDE * (-1);
    weight += record[4][2][WHITE] * WEIGHT4_2SIDE * (-1);

    weight += record[5][0][BLACK] * WEIGHT5;
    weight += record[5][0][WHITE] * WEIGHT5 * (-1);

    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    EndTimer(2);

    return weight;
}

int GenerateWeightAt(int a, int b, int color)
{
    if (board[a][b])
        BOOM("!!!!");
    board[a][b] = color;
    int result = GenerateWeight();
    board[a][b] = 0;
    return result;
}

int UpdateWeight(int a, int b, int weight)
{
    StartTimer(3);

    // 越界->3;
    // 黑棋->1;
    // 白棋->2;
    // 空白->0;
    int record[BOUNDRY + 2][3][3]; //record[link][side][color]
    memset(record, 0, sizeof(record));

    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmartix[0][c + 1] = Board(a, c);
        _scanmartix[1][c + 1] = Board(c, b);
    }

    // printf("%d ", i);

    // printf("%d ", i);

    int aplusb = a + b;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        //b=aplusb-a;
        _scanmartix[2][c + 1] = Board(c, aplusb - c);
    }

    int aminusb = a - b;
    //b=a-aminusb
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmartix[3][c + 1] = Board(c, c - aminusb);
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
        while (p < BOUNDRY + 2)
        {
            if (_scanmartix[i][p++] == incolor) //连续的几个同色点
            {
                link++;
            }
            else //连续的几个同色点的末端
            {
                switch (incolor)
                {
                case 0: //连续的空点
                    forecolor = 0;
                    link = 1;
                    incolor = _scanmartix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmartix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][BLACK]++;
                    record[link][side][BLACK]++;
                    incolor = _scanmartix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][WHITE]++;
                    record[link][side][WHITE]++;
                    incolor = _scanmartix[i][p - 1];
                    link = 1;
                    forecolor = WHITE;
                    break;
                    // side = 0;
                }
            }
        }
    }
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][2][BLACK] * WEIGHT1_2SIDE;
    weight += record[2][1][BLACK] * WEIGHT2_1SIDE;
    weight += record[2][2][BLACK] * WEIGHT2_2SIDE;
    weight += record[3][1][BLACK] * WEIGHT3_1SIDE;
    weight += record[3][2][BLACK] * WEIGHT3_2SIDE;
    weight += record[4][1][BLACK] * WEIGHT4_1SIDE;
    weight += record[4][2][BLACK] * WEIGHT4_2SIDE;

    weight += record[1][1][WHITE] * WEIGHT1_1SIDE * (-1);
    weight += record[1][2][WHITE] * WEIGHT1_2SIDE * (-1);
    weight += record[2][1][WHITE] * WEIGHT2_1SIDE * (-1);
    weight += record[2][2][WHITE] * WEIGHT2_2SIDE * (-1);
    weight += record[3][1][WHITE] * WEIGHT3_1SIDE * (-1);
    weight += record[3][2][WHITE] * WEIGHT3_2SIDE * (-1);
    weight += record[4][1][WHITE] * WEIGHT4_1SIDE * (-1);
    weight += record[4][2][WHITE] * WEIGHT4_2SIDE * (-1);

    weight += record[5][0][BLACK] * WEIGHT5;
    weight += record[5][0][WHITE] * WEIGHT5 * (-1);

    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight += record[1][1][BLACK] * WEIGHT1_1SIDE;

    memset(record, 0, sizeof(record));
    int _color = board[a][b];
    board[a][b] = 0;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmartix[0][c + 1] = Board(a, c);
        _scanmartix[1][c + 1] = Board(c, b);
    }

    // printf("%d ", i);

    // printf("%d ", i);

    // int aplusb = a + b;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        //b=aplusb-a;
        _scanmartix[2][c + 1] = Board(c, aplusb - c);
    }

    // int aminusb = a - b;
    //b=a-aminusb
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmartix[3][c + 1] = Board(c, c - aminusb);
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
        while (p < BOUNDRY + 2)
        {
            if (_scanmartix[i][p++] == incolor) //连续的几个同色点
            {
                link++;
            }
            else //连续的几个同色点的末端
            {
                switch (incolor)
                {
                case 0: //连续的空点
                    forecolor = 0;
                    link = 1;
                    incolor = _scanmartix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmartix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][BLACK]++;
                    record[link][side][BLACK]++;
                    incolor = _scanmartix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmartix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][WHITE]++;
                    record[link][side][WHITE]++;
                    incolor = _scanmartix[i][p - 1];
                    link = 1;
                    forecolor = WHITE;
                    break;
                    // side = 0;
                }
            }
        }
    }
    weight -= record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight -= record[1][2][BLACK] * WEIGHT1_2SIDE;
    weight -= record[2][1][BLACK] * WEIGHT2_1SIDE;
    weight -= record[2][2][BLACK] * WEIGHT2_2SIDE;
    weight -= record[3][1][BLACK] * WEIGHT3_1SIDE;
    weight -= record[3][2][BLACK] * WEIGHT3_2SIDE;
    weight -= record[4][1][BLACK] * WEIGHT4_1SIDE;
    weight -= record[4][2][BLACK] * WEIGHT4_2SIDE;

    weight -= record[1][1][WHITE] * WEIGHT1_1SIDE * (-1);
    weight -= record[1][2][WHITE] * WEIGHT1_2SIDE * (-1);
    weight -= record[2][1][WHITE] * WEIGHT2_1SIDE * (-1);
    weight -= record[2][2][WHITE] * WEIGHT2_2SIDE * (-1);
    weight -= record[3][1][WHITE] * WEIGHT3_1SIDE * (-1);
    weight -= record[3][2][WHITE] * WEIGHT3_2SIDE * (-1);
    weight -= record[4][1][WHITE] * WEIGHT4_1SIDE * (-1);
    weight -= record[4][2][WHITE] * WEIGHT4_2SIDE * (-1);

    weight -= record[5][0][BLACK] * WEIGHT5;
    weight -= record[5][0][WHITE] * WEIGHT5 * (-1);

    weight -= record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight -= record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight -= record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight -= record[1][1][BLACK] * WEIGHT1_1SIDE;
    weight -= record[1][1][BLACK] * WEIGHT1_1SIDE;

    board[a][b] = _color;
        EndTimer(3);

    return weight;
}

#endif