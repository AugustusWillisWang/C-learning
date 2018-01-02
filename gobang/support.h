//support.h
//Judgewin, and some basic parameters.
#ifndef _SUPPORT_H
#define _SUPPORT_H

#define BOUNDRY 15 //19
#define BLACK 1
#define WHITE 2
#define OUTOFBOARD 3

#define NORMAL 0
#define CLEAR 1

#include "lazy.h"
#include "charlib.h"
#include "malloc.h"

//global vars.
int colornow;
int fstmove = 1;
int board[BOUNDRY][BOUNDRY];      //棋盘数据
int printboard[BOUNDRY][BOUNDRY]; //绘图板
double weight[BOUNDRY][BOUNDRY];  //权重变化,注意权重为double

//settings
int _usesimpletest = 0;
int set_savelog = 0;

#define INF 10000000
#define NINF -1000000

struct move
{
    int a;
    int b;
};

struct movenode
{
    int a;
    int b;
    double weight;
    int history_score;
};

int Board(int a, int b)
{
    if (a >= 0 && a < BOUNDRY && b >= 0 && b < BOUNDRY)
    {
        return board[a][b];
    }
    else
    {
        return OUTOFBOARD;
    }
}

int ShowBoardArray(); //简单显示棋盘

int ShowBoardArray()
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%d ", board[a][b]);
        }
        printf("\n");
    }
    printf("\n");
    // CP;
    // printf("-----------------------------------------------------\n");
    return 0;
}

int BoundLim(int a)
{
    if (a < 0)
    {
        return 0;
    }
    else if (a >= BOUNDRY)
    {
        return BOUNDRY - 1;
    }
    else
    {
        return a;
    }
}

int EqualDouble(double a, double b)
{
    if (a < b + 1 && a > b - 1)
        return 0;
    return 1;
}

int JudgeWin() //Haveoutput.version
{
    // double weight_for_shape_now = 0.0;
    //line
    int incolor = 0;
    int continuecnt = 0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b] == incolor)
            {
                continuecnt++;
            }
            else
            {
                if (incolor && (continuecnt >= 5))
                {

                    if (incolor == WHITE)
                    {
                        printf("White wins!\n");
                    }
                    else if (incolor == BLACK)
                    {
                        printf("Black wins!\n");
                    }
                    return incolor;
                }
                // weight_for_shape_now += WeightContribute(incolor, continuecnt);
                continuecnt = 1;
                incolor = board[a][b];
            }
        }
        // weight_for_shape_now += WeightContribute(incolor, continuecnt);
        if (incolor && (continuecnt >= 5))
        {

            if (incolor == WHITE)
            {
                printf("White wins!\n");
            }
            else if (incolor == BLACK)
            {
                printf("Black wins!\n");
            }
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }

    //col
    incolor = 0;
    continuecnt = 0;
    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            if (board[a][b] == incolor)
            {
                continuecnt++;
            }
            else
            {
                if (incolor && (continuecnt >= 5))
                {

                    if (incolor == WHITE)
                    {
                        printf("White wins!\n");
                    }
                    else if (incolor == BLACK)
                    {
                        printf("Black wins!\n");
                    }
                    return incolor;
                }
                // weight_for_shape_now += WeightContribute(incolor, continuecnt);
                continuecnt = 1;
                incolor = board[a][b];
            }
        }
        // weight_for_shape_now += WeightContribute(incolor, continuecnt);
        if (incolor && (continuecnt >= 5))
        {

            if (incolor == WHITE)
            {
                printf("White wins!\n");
            }
            else if (incolor == BLACK)
            {
                printf("Black wins!\n");
            }
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }

    //dig2
    incolor = 0;
    continuecnt = 0;
    for (int aplusb = 0; aplusb < 2 * (BOUNDRY - 1); aplusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = aplusb - a;
            if (b >= 0 && b < BOUNDRY)
            {
                if (board[a][b] == incolor)
                {
                    continuecnt++;
                }
                else
                {
                    if (incolor && (continuecnt >= 5))
                    {

                        if (incolor == WHITE)
                        {
                            printf("White wins!\n");
                        }
                        else if (incolor == BLACK)
                        {
                            printf("Black wins!\n");
                        }
                        return incolor;
                    }
                    // weight_for_shape_now += WeightContribute(incolor, continuecnt);
                    continuecnt = 1;
                    incolor = board[a][b];
                }
            }
        }
        // weight_for_shape_now += WeightContribute(incolor, continuecnt);
        if (incolor && (continuecnt >= 5))
        {

            if (incolor == WHITE)
            {
                printf("White wins!\n");
            }
            else if (incolor == BLACK)
            {
                printf("Black wins!\n");
            }
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }

    //dig1
    incolor = 0;
    continuecnt = 0;
    for (int aminusb = -(BOUNDRY - 1); aminusb < (BOUNDRY - 1); aminusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = a - aminusb;
            if (b >= 0 && b < BOUNDRY)
            {
                if (board[a][b] == incolor)
                {
                    continuecnt++;
                }
                else
                {
                    if (incolor && (continuecnt >= 5))
                    {

                        if (incolor == WHITE)
                        {
                            printf("White wins!\n");
                        }
                        else if (incolor == BLACK)
                        {
                            printf("Black wins!\n");
                        }
                        return incolor;
                    }
                    // weight_for_shape_now += WeightContribute(incolor, continuecnt);
                    continuecnt = 1;
                    incolor = board[a][b];
                }
            }
        }
        // weight_for_shape_now += WeightContribute(incolor, continuecnt);
        if (incolor && (continuecnt >= 5))
        {

            if (incolor == WHITE)
            {
                printf("White wins!\n");
            }
            else if (incolor == BLACK)
            {
                printf("Black wins!\n");
            }
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }
    // return weight_for_shape_now;
    return 0;
}

int _JudgeWin() //Nooutput.version
{
    // double weight_for_shape_now = 0.0;
    //line
    int incolor = 0;
    int continuecnt = 0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b] == incolor)
            {
                continuecnt++;
            }
            else
            {
                if (incolor && (continuecnt >= 5))
                {

                    if (incolor == WHITE)
                    {
                        return WHITE;
                    }
                    else if (incolor == BLACK)
                    {
                        return BLACK;
                    }
                    return incolor;
                }
                // weight_for_shape_now += WeightContribute(incolor, continuecnt);
                continuecnt = 1;
                incolor = board[a][b];
            }
        }
        // weight_for_shape_now += WeightContribute(incolor, continuecnt);
        if (incolor && (continuecnt >= 5))
        {

            if (incolor == WHITE)
            {
                printf("White wins!\n");
            }
            else if (incolor == BLACK)
            {
                printf("Black wins!\n");
            }
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }

    //col
    incolor = 0;
    continuecnt = 0;
    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            if (board[a][b] == incolor)
            {
                continuecnt++;
            }
            else
            {
                if (incolor && (continuecnt >= 5))
                {

                    if (incolor == WHITE)
                    {
                        return WHITE;
                    }
                    else if (incolor == BLACK)
                    {
                        return BLACK;
                    }
                    return incolor;
                }
                // weight_for_shape_now += WeightContribute(incolor, continuecnt);
                continuecnt = 1;
                incolor = board[a][b];
            }
        }
        // weight_for_shape_now += WeightContribute(incolor, continuecnt);
        if (incolor && (continuecnt >= 5))
        {

            if (incolor == WHITE)
            {
                printf("White wins!\n");
            }
            else if (incolor == BLACK)
            {
                printf("Black wins!\n");
            }
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }

    //dig2
    incolor = 0;
    continuecnt = 0;
    for (int aplusb = 0; aplusb < 2 * (BOUNDRY - 1); aplusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = aplusb - a;
            if (b >= 0 && b < BOUNDRY)
            {
                if (board[a][b] == incolor)
                {
                    continuecnt++;
                }
                else
                {
                    if (incolor && (continuecnt >= 5))

                    {
                        if (incolor == WHITE)

                        {
                            return WHITE;
                        }
                        else if (incolor == BLACK)
                        {
                            return BLACK;
                        }
                    }
                    // weight_for_shape_now += WeightContribute(incolor, continuecnt);
                    continuecnt = 1;
                    incolor = board[a][b];
                }
            }
        }
        // weight_for_shape_now += WeightContribute(incolor, continuecnt);
        if (incolor && (continuecnt >= 5))
        {

            if (incolor == WHITE)
            {
                printf("White wins!\n");
            }
            else if (incolor == BLACK)
            {
                printf("Black wins!\n");
            }
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }

    //dig1
    incolor = 0;
    continuecnt = 0;
    for (int aminusb = -(BOUNDRY - 1); aminusb < (BOUNDRY - 1); aminusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = a - aminusb;
            if (b >= 0 && b < BOUNDRY)
            {
                if (board[a][b] == incolor)
                {
                    continuecnt++;
                }
                else
                {
                    if (incolor && (continuecnt >= 5))
                    {
                        if (incolor == WHITE)
                        {
                            return WHITE;
                        }
                        else if (incolor == BLACK)
                        {
                            return BLACK;
                        }
                        return incolor;
                    }
                    // weight_for_shape_now += WeightContribute(incolor, continuecnt);
                    continuecnt = 1;
                    incolor = board[a][b];
                }
            }
        }
        // weight_for_shape_now += WeightContribute(incolor, continuecnt);
        if (incolor && (continuecnt >= 5))
        {

            if (incolor == WHITE)
            {
                printf("White wins!\n");
            }
            else if (incolor == BLACK)
            {
                printf("Black wins!\n");
            }
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }
    // return weight_for_shape_now;
    return 0;
}

int Abs(int input)
{
    if (input < 0)
    {
        input = -input;
    }
    return input;
}

int Inverse(int color)
{
    switch (color)
    {
    case WHITE:
        return BLACK;
    case BLACK:
        return WHITE;
    default:
        return 0;
    }
}

int ShowWeightArray(double weight[BOUNDRY][BOUNDRY])
{
    puts("ShowWeightArray:");
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%.1lf\t", weight[a][b]);
        }
        puts("");
    }
    return 0;
}
double Abs_double(double input)
{
    if (input < 0)
    {
        return -input;
    }
}


double MaxWeight(int (*weight)[BOUNDRY])
{
    double max = NINF;
    //    double min = 100000000000.0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (weight[a][b] > max)
                max = weight[a][b];
        }
    }
    return max;
}

double MinWeight(int (*weight)[BOUNDRY])
{
    double min = INF;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (weight[a][b] < min)
                min = weight[a][b];
        }
    }
    return min;
}


#endif