// Copyright (c) 2017-2018 Augustus Wang

#ifndef _WEIGHT_H
#define _WEIGHT_H
#include "support.h"
#include "stdio.h"
#include "lazy.h"

#define EDGE 3

//这里的权值是随便赋的
#define WEIGHT1_2SIDE 2.0
#define WEIGHT2_2SIDE 20.0
#define WEIGHT3_2SIDE 1000.0
#define WEIGHT4_2SIDE 2000.0
#define WEIGHT1_1SIDE 1.0
#define WEIGHT2_1SIDE 10.0
#define WEIGHT3_1SIDE 500.0
#define WEIGHT4_1SIDE 1500.0

#define WEIGHT5 10000.0

int _scanmartix[BOUNDRY * 6 - 2][BOUNDRY + 2];

// Board();

int _ShowScanMartix()
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

int FlushScanMartix()
{
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

double GenerateWeight()
{
    double weight = 0.0;
    int record[BOUNDRY + 2][3][3]; //record[link][side][color]
    memset(record, 0, sizeof(record));
    FlushScanMartix();

    for (int i = 0; i < BOUNDRY * 6 - 2; i++)
    {
        int p = 1;
        int incolor = 3;
        int forecolor = 3;
        int backcolor = 0;
        int link = 1;
        int side = 0;
        while (p < BOUNDRY + 2)
        {
            if (_scanmartix[i][p++] == incolor)
            {
                link++;
            }
            else
            {
                switch (incolor)
                {
                case 0:
                    forecolor = 0;
                    link = 1;
                    incolor = _scanmartix[i][p - 1];
                    break;
                case EDGE:
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
    weight += record[1][1][BLACK]*WEIGHT1_1SIDE;
    weight += record[1][2][BLACK]*WEIGHT1_2SIDE;
    weight += record[2][1][BLACK]*WEIGHT2_1SIDE;
    weight += record[2][2][BLACK]*WEIGHT2_2SIDE;
    weight += record[3][1][BLACK]*WEIGHT3_1SIDE;
    weight += record[3][2][BLACK]*WEIGHT3_2SIDE;
    weight += record[4][1][BLACK]*WEIGHT4_1SIDE;
    weight += record[4][2][BLACK]*WEIGHT4_2SIDE;

    weight += record[1][1][WHITE]*WEIGHT1_1SIDE*(-1);
    weight += record[1][2][WHITE]*WEIGHT1_2SIDE*(-1);
    weight += record[2][1][WHITE]*WEIGHT2_1SIDE*(-1);
    weight += record[2][2][WHITE]*WEIGHT2_2SIDE*(-1);
    weight += record[3][1][WHITE]*WEIGHT3_1SIDE*(-1);
    weight += record[3][2][WHITE]*WEIGHT3_2SIDE*(-1);
    weight += record[4][1][WHITE]*WEIGHT4_1SIDE*(-1);
    weight += record[4][2][WHITE]*WEIGHT4_2SIDE*(-1);

    weight += record[5][0][BLACK]*WEIGHT5;
    weight += record[5][0][WHITE]*WEIGHT5*(-1);
    
    weight += record[1][1][BLACK]*WEIGHT1_1SIDE;
    weight += record[1][1][BLACK]*WEIGHT1_1SIDE;
    weight += record[1][1][BLACK]*WEIGHT1_1SIDE;
    weight += record[1][1][BLACK]*WEIGHT1_1SIDE;
    weight += record[1][1][BLACK]*WEIGHT1_1SIDE;

    return weight;
}

double GenerateWeightAt(int a,int b, int color)
{
    if(board[a][b])
        BOOM("!!!!");
    board[a][b] = color;
    double result = GenerateWeight();
    board[a][b] = 0;
    return result;
}

#endif