//zobrist.h
#ifndef _ZOBRIST_H
#define _ZOBRIST_h

#include <stdlib.h>
#define SEED 233
#define HASHSIZE 0x0FFFFFF
#include "support.h"
#include "MersenneTwisterRand.h"
//使用梅森旋转法生成随机数, 而非C99自带的实现
//注记: hash分成两部分, 短的数组索引和长的校验用数.

int _ndefZobchain = 1;

struct zobhash
{
    double weight;
    unsigned long long check;
    int level;
} hashtable[HASHSIZE];

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
    return result;
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
    return result;
}

unsigned long int NextHash(unsigned long int hash, int a, int b, int colornow)
{
    return zobrist_table[a][b][colornow] + hash;
}

unsigned long int LastHash(unsigned long int hash, int a, int b, int colornow)
{
    return -zobrist_table[a][b][colornow] + hash;
}
unsigned long int NextHash2(unsigned long int hash, int a, int b, int colornow)
{
    return zobrist_check_table[a][b][colornow] + hash;
}

unsigned long int LastHash2(unsigned long int hash, int a, int b, int colornow)
{
    return -zobrist_check_table[a][b][colornow] + hash;
}

double FindInHashTable(unsigned long zob,unsigned long zob2, int level, double **_socket)
{
    //**_socket 为权值的值
    //*_socket 为权值在hash表中的保存位置
    if ((level > hashtable[zob%HASHSIZE].level) || hashtable[zob%HASHSIZE].check!=zob2)
        { //!hashtable[zob].check)|| todo
            hashtable[zob%HASHSIZE].check = zob2;
            hashtable[zob%HASHSIZE].level = level;
            *_socket = &hashtable[zob%HASHSIZE].weight;
        }
    else
    {
        *_socket = 0;
        return hashtable[zob%HASHSIZE].weight;
    }
}

#endif