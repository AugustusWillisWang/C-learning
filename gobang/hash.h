//hash.h
#ifndef _HASH_H
#define _HASH_H

#include <stdlib.h>
#define SEED 233
#ifdef RAND_MAX
#undef RAND_MAX
#endif
#define HASHSIZE 0x0FFFFFF
#define RAND_MAX HASHSIZE

int _ndefZobchain = 1;

struct zobhash
{
    double weight;
    unsigned long check;
    int level;
} hashtable[HASHSIZE];

unsigned long int zobrist_table[BOUNDRY][BOUNDRY][2];
// unsigned long int zobrist_table2[BOUNDRY][BOUNDRY][2];


int Setupzob()
{

    srand(SEED);
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            zobrist_table[a][b][0] = rand();
            zobrist_table[a][b][1] = rand();
            // zobrist_table2[a][b][0] = rand();
            // zobrist_table2[a][b][1] = rand();
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

double FindInHashTable(unsigned long zob,int level, double **_socket)
{
    if((!hashtable[zob].check)||level>hashtable[zob].level||(hashtable[zob].check!=Getzob2())){
        hashtable[zob].check = Getzob2();
        hashtable[zob].level = level;
        *_socket = &hashtable[zob].weight;
    }else{
            *_socket = 0;
        return hashtable[zob].weight;
        }
}


#endif