// Copyright (c) 2017-2018 Augustus Wang
// zobrist.h
// zobrist hash 实现及空间分配
#ifndef _ZOBRIST_H
#define _ZOBRIST_H

#include <stdlib.h>
#define SEED 233
#define HASHSIZE 0x02FFFFFF
#include "support.h"
#include "MersenneTwisterRand.h"
//使用梅森旋转法生成随机数, 而非C99自带的实现
//注记: hash分成两部分, 短的数组索引和长的校验用数.

// #define ENABLEHASH

int _ndefZobchain = 1;

struct zobhash
{
    int weight;
    unsigned long long check;
    int level;
    int type; //todo
} hashtable[HASHSIZE + 1];

unsigned long int zobrist_table[BOUNDRY][BOUNDRY][2];
unsigned long int zobrist_check_table[BOUNDRY][BOUNDRY][2];

int Setupzob()
{
    InitializeMTRandom(SEED);
    ExtractMTRandom32();

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            zobrist_table[a][b][0] = ExtractMTRandom32();
            zobrist_table[a][b][1] = ExtractMTRandom32();
            zobrist_check_table[a][b][0] = ExtractMTRandom32();
            zobrist_check_table[a][b][1] = ExtractMTRandom32();
        }
        // printf("%lu ", zobrist_table + i);
    }

    // _ZobChain.hash = 0;
    // _ZobChain.weight = 0;
    // _ZobChain.next = 0;
}

unsigned long int Getzob()
{
    unsigned long int result = 0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b] == BLACK)
            {
                result += zobrist_table[a][b][0];
            }
            if (board[a][b] == WHITE)
            {
                result += zobrist_table[a][b][1];
            }
        }
    }
    return result & HASHSIZE;
}

unsigned long int Getzob2()
{
    unsigned long int result = 0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b] == BLACK)
            {
                result += zobrist_check_table[a][b][0];
            }
            if (board[a][b] == WHITE)
            {
                result += zobrist_check_table[a][b][1];
            }
        }
    }
    return result & HASHSIZE;
}

unsigned long int NextHash(unsigned long int hash, int a, int b, int colornow)
{
#ifndef ENABLEHASH
    return 0;
#endif
    return (zobrist_table[a][b][colornow] + hash) & HASHSIZE;
}

unsigned long int LastHash(unsigned long int hash, int a, int b, int colornow)
{
#ifndef ENABLEHASH
    return 0;
#endif
    return (-zobrist_table[a][b][colornow] + hash) & HASHSIZE;
}
unsigned long int NextHash2(unsigned long int hash, int a, int b, int colornow)
{
#ifndef ENABLEHASH
    return 0;
#endif
    return (zobrist_check_table[a][b][colornow] + hash) & HASHSIZE;
}

unsigned long int LastHash2(unsigned long int hash, int a, int b, int colornow)
{
#ifndef ENABLEHASH
    return 0;
#endif
    return (-zobrist_check_table[a][b][colornow] + hash) & HASHSIZE;
}

struct findresult
{
    int find;
    struct zobhash *point;
    int weight;
    int type;
};

#define LOWER 1
#define UPPER 2
#define VALUE 3

struct findresult FindInHashTable(unsigned long zob, unsigned long zob2, int level, int type) //type:color
{
    unsigned long int hashvalue = zob;
    if ((level > hashtable[hashvalue].level) || hashtable[hashvalue].check != zob2 || hashtable[hashvalue].type != type)
    { //!hashtable[zob].check)|| todo
        hashtable[hashvalue].check = zob2;
        hashtable[hashvalue].level = level;
        struct findresult result =
            {
                0, &hashtable[hashvalue], hashtable[hashvalue].weight, hashtable[hashvalue].type};
        return result;
    }
    else
    {
        struct findresult result =
            {
                1, &hashtable[hashvalue], hashtable[hashvalue].weight, hashtable[hashvalue].type};
        return result;
    }
}

int CheckHashResult(struct findresult result, int alpha, int beta)
{
    if (!result.find)
        return 0;
    if (result.type == VALUE)
        return 1;
    if (result.type == LOWER)
    {
        if (result.weight >= beta)
            return 1;
    }
    if (result.type == UPPER)
    {
        if (result.weight <= alpha)
            return 1;
    }
    return 0;
}

// struct zobhash
// {
//     int weight;
//     unsigned long long check;
//     int level;
//     int type; //todo
// } hashtable[HASHSIZE];

int SaveToZob(struct findresult result, unsigned long zob2, int level, int type, int weight)
{
    result.point->weight = weight;
    result.point->check = zob2;
    result.point->level = level;
    result.point->type = type;
    return 0;
}

int _hit = 0;
int _tot = 0;

#endif