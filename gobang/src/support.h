//Copyright (c) 2017-2018 Augustus Wang
//support.h
//Judgewin, and some basic parameters.
//棋盘定义, 数据结构定义, 基础情况判断以及其他共用部分, 写成头文件以方便单元测试
#ifndef _SUPPORT_H
#define _SUPPORT_H

#define BOUNDRY 15 //棋盘大小
#define BLACK 1 //黑方
#define WHITE 2 //白方
#define OUTOFBOARD 3 //棋盘边界, 超出棋盘范围的点用3表示

#define NORMAL 0 //旧的判断函数用的, 懒得改掉了
#define CLEAR 1 //旧的判断函数用的, 懒得改掉了

#include "lazy.h" //一些调试用的函数
#include "charlib.h" //处理用户输入输出的文本
#include <malloc.h> 

//global vars.
int colornow; //当前应走子的颜色
int fstmove = 1; //是否为第一步
int board[BOUNDRY][BOUNDRY];      //棋盘数据
int printboard[BOUNDRY][BOUNDRY]; //绘图板
int weight[BOUNDRY][BOUNDRY];     //权重变化,注意权重为double

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

struct movenode //历史启发搜索用排序节点
{
    int a;
    int b;
    int weight;
    int history_score;
};

int Board(int a, int b) //若坐标合法, 返回该位置的棋子颜色, 否则, 返回越界"3"
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

int ShowBoardArray(); //简单显示棋盘(调试用)

int ShowBoardArray()//简单显示棋盘(调试用)
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

int BoundLim(int a)//将一个输入数的取值规整到[0:BOUNDRY]
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

int EqualDouble(int a, int b)//浮点数相等判断
{
    if (a < b + 1 && a > b - 1)
        return 0;
    return 1;
}

int JudgeWin() //Haveoutput.version //快速胜负判断, 早期写法, 性能最优, 但是一点都不优雅233333
//不写注释了, 胜负判断使用weight.h里的函数来判断更加清楚
{
    // int weight_for_shape_now = 0.0;
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

int _JudgeWin() //Nooutput.version //快速胜负判断, 早期写法, 性能最优, 但是一点都不优雅233333
{
    // int weight_for_shape_now = 0.0;
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
            return incolor;
        }
        incolor = 0;
        continuecnt = 0;
    }
    // return weight_for_shape_now;
    return 0;
}

int Abs(int input)//绝对值
{
    if (input < 0)
    {
        input = -input;
    }
    return input;
}

int Inverse(int color)//颜色反转 黑->白, 白->黑
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

int ShowWeightArray(int weight[BOUNDRY][BOUNDRY])//调试用, 显示权重数组
{
    puts("ShowWeightArray:");
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%d\t", weight[a][b]);
        }
        puts("");
    }
    return 0;
}

int Abs_double(int input)//绝对值
{
    if (input < 0)
    {
        return -input;
    }
}

int MaxWeight(int (*weight)[BOUNDRY])
{
    int max = NINF;
    //    int min = 100000000000.0;
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

int MinWeight(int (*weight)[BOUNDRY])
{
    int min = INF;
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

int SetUp(int a, int b, int color) //设置当前棋盘某一位置(程序用)
{
    if (a >= 0 && a < BOUNDRY && b >= 0 && b < BOUNDRY && (color == 0 || color == BLACK || color == WHITE))
    {
        if (board[a][b] != 0)
        {
            puts("Wrong input, please input again!");
            setbuf(stdin, NULL);
            return -1;
        }
        board[a][b] = color;

        return 0;
    }
    puts("Wrong input, please input again!");
    setbuf(stdin, NULL);
    return -1;
}

#endif