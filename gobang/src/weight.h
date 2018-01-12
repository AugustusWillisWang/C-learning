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
#define WEIGHT1_2SIDE 1  //一子2气
#define WEIGHT2_2SIDE 40 //二子2气
#define WEIGHT3_2SIDE 200
#define WEIGHT4_2SIDE 2000
#define WEIGHT1_1SIDE 0 //1子1气
#define WEIGHT2_1SIDE 4
#define WEIGHT3_1SIDE 40
#define WEIGHT4_1SIDE 200

#define WEIGHT5 100000
#define BIG_WEIGHT 80000

int _scanmatrix[BOUNDRY * 6 - 2][BOUNDRY + 2]; //将棋盘转化为一维数组

// Board();

int _ShowScanMartix() //单元测试用
{
    puts("_ShowScanMartix");
    for (int a = 0; a < 6 * BOUNDRY - 2; a++)
    {
        for (int b = 0; b < BOUNDRY + 2; b++)
        {
            printf("%d ", _scanmatrix[a][b]);
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
            _scanmatrix[i][a + 1] = Board(a, b);
        }
        i++;
    }
    // printf("%d ", i);

    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = -1; a <= BOUNDRY; a++)
        {
            _scanmatrix[i][a + 1] = Board(b, a);
        }
        i++;
    }
    // printf("%d ", i);

    for (int aplusb = 0; aplusb <= 2 * BOUNDRY - 2; aplusb++)
    {
        for (int a = -1; a <= BOUNDRY; a++)
        {
            //b=aplusb-a;
            _scanmatrix[i][a + 1] = Board(a, aplusb - a);
        }
        i++;
    }
    // printf("%d ", i);

    for (int aminusb = -BOUNDRY + 1; aminusb <= BOUNDRY - 1; aminusb++)
    {
        //b=a-aminusb
        for (int a = -1; a <= BOUNDRY; a++)
        {
            _scanmatrix[i][a + 1] = Board(a, a - aminusb);
        }
        i++;
    }
    // printf("%d ", i);
}

int DBG_ShowRecord(int record[BOUNDRY + 2][3][3][2])
{
    for (int a = 0; a < 5; a++)
    {
        printf("link%d", a);
        for (int b = 0; b < 3; b++)
        {
            printf("side%d", b);
            for (int c = 0; c < 3; c++)
            {
                printf("color%d:", c);
                for (int d = 0; d < 2; d++)
                {
                    printf("space%d:", d);
                    printf("% d\n", record[a][b][c][d]);
                }
            }
        }
        puts("-----------------");
    }
    // record[BOUNDRY + 2][3][3][2]
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
            if (_scanmatrix[i][p++] == incolor) //连续的几个同色点
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
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][BLACK]++;
                    record[link][side][BLACK]++;
                    incolor = _scanmatrix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][WHITE]++;
                    record[link][side][WHITE]++;
                    incolor = _scanmatrix[i][p - 1];
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
        _scanmatrix[0][c + 1] = Board(a, c);
        _scanmatrix[1][c + 1] = Board(c, b);
    }

    // printf("%d ", i);

    // printf("%d ", i);

    int aplusb = a + b;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        //b=aplusb-a;
        _scanmatrix[2][c + 1] = Board(c, aplusb - c);
    }

    int aminusb = a - b;
    //b=a-aminusb
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmatrix[3][c + 1] = Board(c, c - aminusb);
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
            if (_scanmatrix[i][p++] == incolor) //连续的几个同色点
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
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][BLACK]++;
                    record[link][side][BLACK]++;
                    incolor = _scanmatrix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][WHITE]++;
                    record[link][side][WHITE]++;
                    incolor = _scanmatrix[i][p - 1];
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

    memset(record, 0, sizeof(record));
    int _color = board[a][b];
    board[a][b] = 0;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmatrix[0][c + 1] = Board(a, c);
        _scanmatrix[1][c + 1] = Board(c, b);
    }

    // printf("%d ", i);

    // printf("%d ", i);

    // int aplusb = a + b;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        //b=aplusb-a;
        _scanmatrix[2][c + 1] = Board(c, aplusb - c);
    }

    // int aminusb = a - b;
    //b=a-aminusb
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmatrix[3][c + 1] = Board(c, c - aminusb);
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
            if (_scanmatrix[i][p++] == incolor) //连续的几个同色点
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
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][BLACK]++;
                    record[link][side][BLACK]++;
                    incolor = _scanmatrix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][0][WHITE]++;
                    record[link][side][WHITE]++;
                    incolor = _scanmatrix[i][p - 1];
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

    board[a][b] = _color;
    EndTimer(3);

    return weight;
}

int UpdateFBDWeight(int a, int b, int weight) //和weight.h基于相同原理
//带禁手的权值判断函数, 对于禁手点, 直接返回白胜(-INF)
//注意只对于空点生效
{

    // 越界->3;
    // 黑棋->1;
    // 白棋->2;
    // 空白->0;
    int record[BOUNDRY + 2][3][3][2]; //record[link][side][color][space]
    memset(record, 0, sizeof(record));

    int _color = board[a][b];
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmatrix[0][c + 1] = Board(a, c);
        _scanmatrix[1][c + 1] = Board(c, b);
    }

    // printf("%d ", i);

    // printf("%d ", i);

    int aplusb = a + b;
    for (int c = -1; c <= BOUNDRY; c++)
    {
        //b=aplusb-a;
        _scanmatrix[2][c + 1] = Board(c, aplusb - c);
    }

    int aminusb = a - b;
    //b=a-aminusb
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmatrix[3][c + 1] = Board(c, c - aminusb);
    }

    for (int i = 0; i < 4; i++)
    {
        //每次扫描时保留前一个节点的值, 来判断连续的几个子两边有多少气
        int p = 1;
        int incolor = 3;
        int forecolor = 3;
        int backcolor = 0;
        int link = 1;
        int side = 0;
        int space = 0;
        while (p < BOUNDRY + 2)
        {
            if (_scanmatrix[i][p++] == incolor) //连续的几个同色点
            {
                link++;
            }
            else //连续的几个同色点的末端
            {
                if ((_scanmatrix[i][p] == incolor) && (_scanmatrix[i][p - 1] == 0) && (space == 0))
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
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0)); //side 为棋形两边的气数
                    if (link >= 5)
                        record[5][side][BLACK][space]++;
                    else
                        record[link][side][BLACK][space]++;
                    incolor = _scanmatrix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][side][WHITE][space]++;
                    else
                        record[link][side][WHITE][space]++;
                    incolor = _scanmatrix[i][p - 1];
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
        _scanmatrix[0][c + 1] = Board(a, c);
        _scanmatrix[1][c + 1] = Board(c, b);
    }

    for (int c = -1; c <= BOUNDRY; c++)
    {
        //b=aplusb-a;
        _scanmatrix[2][c + 1] = Board(c, aplusb - c);
    }

    //b=a-aminusb
    for (int c = -1; c <= BOUNDRY; c++)
    {
        _scanmatrix[3][c + 1] = Board(c, c - aminusb);
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
            if (_scanmatrix[i][p++] == incolor) //连续的几个同色点
            {
                link++;
            }
            else //连续的几个同色点的末端
            {
                if ((_scanmatrix[i][p] == incolor) && (_scanmatrix[i][p - 1] == 0) && (space == 0))
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
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0)); //side 为棋形两边的气数
                    if (link >= 5)
                        record[5][side][BLACK][space]--;
                    else
                        record[link][side][BLACK][space]--;
                    incolor = _scanmatrix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][side][WHITE][space]--;
                    else
                        record[link][side][WHITE][space]--;
                    incolor = _scanmatrix[i][p - 1];
                    link = 1;
                    forecolor = WHITE;
                    break;
                    // side = 0;
                }
            }
        }
    }

    board[a][b] = _color;
    // DBG_ShowRecord(record);

    int huo4 = record[4][2][BLACK][0];
    int chong4 = record[5][2][BLACK][1] + record[5][1][BLACK][1] + record[5][0][BLACK][1] + record[4][1][BLACK][0] + record[4][1][BLACK][1] + record[4][2][BLACK][1] + record[4][0][BLACK][1];
    int huo3 = record[3][2][BLACK][0] + record[3][2][BLACK][1];
    if (_color == BLACK)
    {
        if (record[5][0][BLACK][0] || record[5][1][BLACK][0] || record[5][2][BLACK][0]) //成5直接终止判断
            return INF;

        if ((huo4 + chong4) >= 2) //44禁手
            return -INF;

        if (huo3 >= 2) //33禁手
            return -INF;
    }
    if ((huo4 + huo3 + chong4) >= 2)
        weight += 1500;

    huo4 = record[4][2][WHITE][0];
    chong4 = record[5][2][WHITE][1] + record[5][1][WHITE][1] + record[5][0][WHITE][1] + record[4][1][WHITE][0] + record[4][1][WHITE][1] + record[4][2][WHITE][1] + record[4][0][WHITE][1];
    huo3 = record[3][2][WHITE][0] + record[3][2][WHITE][1];

    if ((huo4 + huo3 + chong4) >= 2)
        weight -= 1500 ;

    weight += record[1][1][BLACK][0] * WEIGHT1_1SIDE;
    weight += record[1][2][BLACK][0] * WEIGHT1_2SIDE;
    weight += record[2][1][BLACK][0] * WEIGHT2_1SIDE;
    weight += record[2][2][BLACK][0] * WEIGHT2_2SIDE;
    weight += record[3][1][BLACK][0] * WEIGHT3_1SIDE;
    weight += record[3][2][BLACK][0] * WEIGHT3_2SIDE;
    weight += record[4][1][BLACK][0] * WEIGHT4_1SIDE;
    weight += record[4][2][BLACK][0] * WEIGHT4_2SIDE;

    // weight += record[1][1][BLACK][1] * WEIGHT1_1SIDE;
    // weight += record[1][2][BLACK][1] * WEIGHT1_1SIDE;
    weight += record[2][1][BLACK][1] * WEIGHT2_1SIDE;
    weight += record[2][2][BLACK][1] * WEIGHT2_2SIDE;
    weight += record[3][1][BLACK][1] * WEIGHT3_1SIDE;
    weight += record[3][2][BLACK][1] * WEIGHT3_2SIDE;
    weight += record[4][1][BLACK][1] * WEIGHT4_1SIDE;
    weight += record[4][2][BLACK][1] * WEIGHT4_1SIDE;
    weight += record[4][2][BLACK][0] * WEIGHT4_1SIDE;

    //长连禁手的判断其实有点问题.....算了不管了
    weight += record[5][0][BLACK][0] * WEIGHT5;
    weight += record[5][1][BLACK][0] * WEIGHT5;
    weight += record[5][2][BLACK][0] * WEIGHT5;

    weight += record[5][0][BLACK][1] * WEIGHT4_1SIDE;
    weight += record[5][1][BLACK][1] * WEIGHT4_1SIDE;
    weight += record[5][2][BLACK][1] * WEIGHT4_1SIDE;
    //------------------
    weight += record[1][1][WHITE][0] * (-1) * WEIGHT1_1SIDE;
    weight += record[1][2][WHITE][0] * (-1) * WEIGHT1_2SIDE;
    weight += record[2][1][WHITE][0] * (-1) * WEIGHT2_1SIDE;
    weight += record[2][2][WHITE][0] * (-1) * WEIGHT2_2SIDE;
    weight += record[3][1][WHITE][0] * (-1) * WEIGHT3_1SIDE;
    weight += record[3][2][WHITE][0] * (-1) * WEIGHT3_2SIDE;
    weight += record[4][1][WHITE][0] * (-1) * WEIGHT4_1SIDE;
    weight += record[4][2][WHITE][0] * (-1) * WEIGHT4_2SIDE;

    // weight += record[1][1][BLACK][1] * WEIGHT1_1SIDE;
    // weight += record[1][2][BLACK][1] * WEIGHT1_1SIDE;
    weight += record[2][1][WHITE][1] * (-1) * WEIGHT2_1SIDE;
    weight += record[2][2][WHITE][1] * (-1) * WEIGHT2_2SIDE;
    weight += record[3][1][WHITE][1] * (-1) * WEIGHT3_1SIDE;
    weight += record[3][2][WHITE][1] * (-1) * WEIGHT3_2SIDE;
    weight += record[4][1][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    weight += record[4][2][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    weight += record[4][2][WHITE][0] * (-1) * WEIGHT4_1SIDE;

    //长连禁手的判断其实有点问题.....算了不管了
    weight += record[5][0][WHITE][0] * (-1) * WEIGHT5;
    weight += record[5][1][WHITE][0] * (-1) * WEIGHT5;
    weight += record[5][2][WHITE][0] * (-1) * WEIGHT5;

    weight += record[5][0][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    weight += record[5][1][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    weight += record[5][2][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    //------------------
    return weight;
}

int GenerateFBDWeight() //为当前局面打分, 黑方优势为正值, 白方优势为负值
{
    StartTimer(2);

    //根据转化之后的一维数组, 判断各种棋形
    //稍加改动可以写成胜负判断, 禁手判断函数(只要比较下一子前后各种棋形的数量)
    int weight = 0;
    int record[BOUNDRY + 2][3][3][2]; //record[link][side][color][space]
    memset(record, 0, sizeof(record));
    FlushScanMartix(); //将棋盘转化为一维数组

    for (int i = 0; i < BOUNDRY * 6 - 2; i++)

    {
        //每次扫描时保留前一个节点的值, 来判断连续的几个子两边有多少气
        int p = 1;
        int incolor = 3;
        int forecolor = 3;
        int backcolor = 0;
        int link = 1;
        int side = 0;
        int space = 0;
        while (p < BOUNDRY + 2)
        {
            if (_scanmatrix[i][p++] == incolor) //连续的几个同色点
            {
                link++;
            }
            else //连续的几个同色点的末端
            {
                if ((_scanmatrix[i][p] == incolor) && (_scanmatrix[i][p - 1] == 0) && (space == 0))
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
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case EDGE: //越过棋盘边界
                    forecolor = EDGE;
                    link = 1;
                    incolor = _scanmatrix[i][p - 1];
                    break;
                case BLACK:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0)); //side 为棋形两边的气数
                    if (link >= 5)
                        record[5][side][BLACK][space]++;
                    else
                        record[link][side][BLACK][space]++;
                    incolor = _scanmatrix[i][p - 1];
                    link = 1;
                    forecolor = BLACK;
                    // side = 0;
                    break;
                case WHITE:
                    backcolor = _scanmatrix[i][p - 1];
                    side = ((forecolor == 0) + (backcolor == 0));
                    if (link >= 5)
                        record[5][side][WHITE][space]++;
                    else
                        record[link][side][WHITE][space]++;
                    incolor = _scanmatrix[i][p - 1];
                    link = 1;
                    forecolor = WHITE;
                    break;
                    // side = 0;
                }
            }
        }
    }


    int huo4 = record[4][2][WHITE][0];
    int chong4 = record[5][2][WHITE][1] + record[5][1][WHITE][1] + record[5][0][WHITE][1] + record[4][1][WHITE][0] + record[4][1][WHITE][1] + record[4][2][WHITE][1] + record[4][0][WHITE][1];
    int huo3 = record[3][2][WHITE][0] + record[3][2][WHITE][1];

    if ((huo4 + huo3 + chong4) >= 2)
        weight -= 1500 ;

    weight += record[1][1][BLACK][0] * WEIGHT1_1SIDE;
    weight += record[1][2][BLACK][0] * WEIGHT1_2SIDE;
    weight += record[2][1][BLACK][0] * WEIGHT2_1SIDE;
    weight += record[2][2][BLACK][0] * WEIGHT2_2SIDE;
    weight += record[3][1][BLACK][0] * WEIGHT3_1SIDE;
    weight += record[3][2][BLACK][0] * WEIGHT3_2SIDE;
    weight += record[4][1][BLACK][0] * WEIGHT4_1SIDE;
    weight += record[4][2][BLACK][0] * WEIGHT4_2SIDE;

    // weight += record[1][1][BLACK][1] * WEIGHT1_1SIDE;
    // weight += record[1][2][BLACK][1] * WEIGHT1_1SIDE;
    weight += record[2][1][BLACK][1] * WEIGHT2_1SIDE;
    weight += record[2][2][BLACK][1] * WEIGHT2_2SIDE;
    weight += record[3][1][BLACK][1] * WEIGHT3_1SIDE;
    weight += record[3][2][BLACK][1] * WEIGHT3_2SIDE;
    weight += record[4][1][BLACK][1] * WEIGHT4_1SIDE;
    weight += record[4][2][BLACK][1] * WEIGHT4_1SIDE;
    weight += record[4][2][BLACK][0] * WEIGHT4_1SIDE;

    //长连禁手的判断其实有点问题.....算了不管了
    weight += record[5][0][BLACK][0] * WEIGHT5;
    weight += record[5][1][BLACK][0] * WEIGHT5;
    weight += record[5][2][BLACK][0] * WEIGHT5;

    weight += record[5][0][BLACK][1] * WEIGHT4_1SIDE;
    weight += record[5][1][BLACK][1] * WEIGHT4_1SIDE;
    weight += record[5][2][BLACK][1] * WEIGHT4_1SIDE;
    //------------------
    weight += record[1][1][WHITE][0] * (-1) * WEIGHT1_1SIDE;
    weight += record[1][2][WHITE][0] * (-1) * WEIGHT1_2SIDE;
    weight += record[2][1][WHITE][0] * (-1) * WEIGHT2_1SIDE;
    weight += record[2][2][WHITE][0] * (-1) * WEIGHT2_2SIDE;
    weight += record[3][1][WHITE][0] * (-1) * WEIGHT3_1SIDE;
    weight += record[3][2][WHITE][0] * (-1) * WEIGHT3_2SIDE;
    weight += record[4][1][WHITE][0] * (-1) * WEIGHT4_1SIDE;
    weight += record[4][2][WHITE][0] * (-1) * WEIGHT4_2SIDE;

    // weight += record[1][1][BLACK][1] * WEIGHT1_1SIDE;
    // weight += record[1][2][BLACK][1] * WEIGHT1_1SIDE;
    weight += record[2][1][WHITE][1] * (-1) * WEIGHT2_1SIDE;
    weight += record[2][2][WHITE][1] * (-1) * WEIGHT2_2SIDE;
    weight += record[3][1][WHITE][1] * (-1) * WEIGHT3_1SIDE;
    weight += record[3][2][WHITE][1] * (-1) * WEIGHT3_2SIDE;
    weight += record[4][1][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    weight += record[4][2][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    weight += record[4][2][WHITE][0] * (-1) * WEIGHT4_1SIDE;

    //长连禁手的判断其实有点问题.....算了不管了
    weight += record[5][0][WHITE][0] * (-1) * WEIGHT5;
    weight += record[5][1][WHITE][0] * (-1) * WEIGHT5;
    weight += record[5][2][WHITE][0] * (-1) * WEIGHT5;

    weight += record[5][0][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    weight += record[5][1][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    weight += record[5][2][WHITE][1] * (-1) * WEIGHT4_1SIDE;
    //------------------

    // DBG_ShowRecord(record);
    EndTimer(2);

    return weight;
}

#endif