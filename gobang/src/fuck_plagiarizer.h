//Copyright (c) 2017-2018 Augustus Wang
//fuck_plagiarizer.h
//没什么, 就是想吐槽一下......想象一下你在新手村练了一万年级, 结果发现对面冲了腾讯心悦会员落地98K......一首凉凉送给自己
//包括首步随机落子函数, 防止对手使用不支持平移的开局库

#ifndef FUCK_PLAGIARIZER
#define FUCK_PLAGIARIZER

#include "support.h"
#include "stdlib.h"

int RandomFirstMove(int *ap, int *bp) //首步随机落子函数, 防止对手使用不支持平移的开局库
{
    srand(clock());
    *ap = BOUNDRY / 2 + rand() % 5 - 2;
    *bp = BOUNDRY / 2 + rand() % 5 - 2;
}
#endif