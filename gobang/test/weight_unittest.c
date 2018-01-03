// Copyright (c) 2017-2018 Augustus Wang

#include "weight.h"
#include "printboard.h"
int main()
{
    // board[1][1] = 1;
    board[2][2] = 1;
    board[1][1] = 1;
    board[3][1] = 1;
    board[3][2] = 1;
    board[3][3] = 1;
    board[3][4] = 2;
    board[3][2] = 1;
    // board[3][3] = 1;
    // board[3][4] = 2;
    FlushScanMartix();
    _ShowScanMartix();
    GenerateWeight();
    scanf("%ddd", board);
}

    // int record[BOUNDRY + 2][3][3]; //record[link][side][color]

    // printf("%d ",record[1][0][1]);
    // printf("%d ",record[1][1][1]);
    // printf("%d ",record[1][2][1]);
    // printf("%d ",record[2][0][1]);
    // printf("%d ",record[2][1][1]);
    // printf("%d ",record[2][2][1]);
    // CK(record[3][0][1]);
    // CK(record[3][1][1]);
    // CK(record[3][2][1]);
    // CK(record[4][0][1]);
    // CK(record[4][1][1]);
    // CK(record[4][2][1]);
    
    // printf("%d ",record[1][0][2]);
    // printf("%d ",record[1][1][2]);
    // printf("%d ",record[1][2][2]);
    // printf("%d ",record[2][0][2]);
    // printf("%d ",record[2][1][2]);
    // printf("%d ",record[2][2][2]);
    // CK(record[3][0][2]);
    // CK(record[3][1][2]);
    // CK(record[3][2][2]);
    // CK(record[4][0][2]);
    // CK(record[4][1][2]);
    // CK(record[4][2][2]);