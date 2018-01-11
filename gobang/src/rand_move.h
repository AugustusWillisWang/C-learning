//Copyright (c) 2017-2018 Augustus Wang
//包括首步随机落子函数, 防止对手使用不支持平移的开局库

#ifndef _RAND_MOVE_H
#define _RAND_MOVE_H

#include "support.h"
#include "stdlib.h"

int RandomFirstMove(int *ap, int *bp) //首步随机落子函数, 防止对手使用不支持平移的开局库
{
    srand(clock());
    *ap = BOUNDRY / 2 + rand() % 5 - 2;
    *bp = BOUNDRY / 2 + rand() % 5 - 2;
}
#endif