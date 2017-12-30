//zobrist.h
#include <stdlib.h>
#define SEED 233
// #ifdef RAND_MAX
// #undef RAND_MAX
// #endif
#define HASHSIZE 0x0FFFFFF
// #define RAND_MAX HASHSIZE
#include "MersenneTwisterRand.h"

int _ndefZobchain = 1;

struct zobhash
{
    double weight;
    unsigned long check;
    int level;
} hashtable[HASHSIZE];

unsigned long int zobrist_table[BOUNDRY][BOUNDRY][2];
unsigned long int zobrist_table2[BOUNDRY][BOUNDRY][2];

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
            zobrist_table2[a][b][0] = ExtractMTRandom32();
            zobrist_table2[a][b][1] = ExtractMTRandom32();
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
    return 1;
    unsigned long int result = 0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b] == BLACK)
            {
                result += zobrist_table2[a][b][0];
            }
            if (board[a][b] == WHITE)
            {
                result += zobrist_table2[a][b][1];
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

double FindInHashTable(unsigned long zob, int level, double **_socket)
{
    if ((level > hashtable[zob%HASHSIZE].level) || !hashtable[zob%HASHSIZE].check)
        { //!hashtable[zob].check)|| todo
            hashtable[zob%HASHSIZE].check = Getzob2();
            hashtable[zob%HASHSIZE].level = level;
            *_socket = &hashtable[zob%HASHSIZE].weight;
        }
    else
    {
        *_socket = 0;
        return hashtable[zob%HASHSIZE].weight;
    }
}
