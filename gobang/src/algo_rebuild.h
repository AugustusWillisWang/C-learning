// Copyright (c) 2017-2018 Augustus Wang

#define ALGO_FINAL 3
#define EDGE 3
#define LEVEL 8
#define NEABOR 1
//(6,2)is recommended;
// #define THINKINGUPPERBOUND 100
#define DEEPLEVELUPPERBOUND 60
// #define WEIGHTHEURISTIC
// #define ENABLEHASH

// #define ENABLEFBDMOVE

#include "zobrist.h"
#include "support.h"
#include "heuristic.h"
#include "weight.h"
#include "killfirst.h"

int GetAroundPosition();
int showweight[BOUNDRY][BOUNDRY];

//------------------------------------------

int GetAroundPosition(int (*_ValidPosition)[BOUNDRY],int depth,int color)
{
    int checked[BOUNDRY][BOUNDRY];
    memset(checked, 0, sizeof(checked));
    memset(_ValidPosition, 0, sizeof(int) * BOUNDRY * BOUNDRY);
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b])
            {
                for (int ia = -NEABOR; ia <= NEABOR; ia++)
                {
                    for (int ib = -NEABOR; ib <= NEABOR; ib++)
                    {
                            int _a = BoundLim(a + ia);
                            int _b = BoundLim(b + ib);
                        if (!board[_a][_b]&&!checked[a][b])
                        {
                            checked[a][b] = 1;
                            _ValidPosition[_a][_b] = 1;
#ifdef KILLSEARCH
                            if (depth <= (LEVEL - KILLSEARCH))
                                _ValidPosition[_a][_b] *= TestKillPoint( _a, _b);

#endif
#ifdef ENABLEFBDMOVE
                            _ValidPosition[_a][_b] *= !TestForbidMove(_a, _b, color);
#endif
                        }
                    }
                }
            }
        }
    }
}

#define OUTPUTWEIGHT                         \
    {                                        \
        if (color == BLACK && step == LEVEL) \
        {                                    \
            weight[a][b] = max;              \
        }                                    \
        if (color == WHITE && step == LEVEL) \
        {                                    \
            weight[a][b] = min;              \
        }                                    \
    }

#define MAXNODE 20
struct move bestmoverec = {-1, -1};

int AlphaBeta(int depth, int color, int alpha, int beta, unsigned long long zob, unsigned long long zob2)
{
    int result = _JudgeWin();
    if (result)
    {
        return (result == BLACK) ? INF : (-INF);
    }

    int score;
#ifdef ENABLEHASH
    struct findresult hashresult;
    hashresult = FindInHashTable(zob, zob2, depth, color);

    if (hashresult.find)
    {
        score = hashresult.weight;
        switch (hashresult.type)
        {
        case LOWER:
            if (score >= alpha)
            {
                return score;
            }
        case UPPER:

        case VALUE:
            return score;
        }
    }
#endif

    if (depth <= 0)
        return GenerateWeight();
    int valid_position[BOUNDRY][BOUNDRY];
    memset(valid_position, 0, sizeof(valid_position));
    GetAroundPosition(valid_position,depth,color);
    struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY];
    memset(heuristic_list, 0, sizeof(heuristic_list));
    int hcnt = 0; //hcnt-1 为最后一个节点的位置
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (valid_position[a][b])
            {
                AddTo_heuristic_list(heuristic_list, hcnt, a, b, depth, 10000 * FindIn_history_table(history_table, a, b, depth));
                hcnt++;
            }
        }
    }

#ifdef KILLSEARCH
    if (hcnt == 0)
    {
        return GenerateWeight();
    }
#endif

#ifdef WEIGHTHEURISTIC
    LinearGenWeightMartix_Algo1();

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (valid_position[a][b])
            {
                AddTo_heuristic_list(heuristic_list, hcnt, a, b, depth, Abs(weight[a][b]));
                hcnt++;
            }
        }
    }
    memset(weight, 0, sizeof(weight));
#endif

    Qsort_heuristic_element(heuristic_list, 0, hcnt - 1);

#ifdef THINKINGUPPERBOUND

    if (hcnt > THINKINGUPPERBOUND)
        hcnt = THINKINGUPPERBOUND;

#endif

#ifdef DEEPLEVELUPPERBOUND
    if (LEVEL > 4)
    {
        if (depth <= LEVEL - 4)
        {
            hcnt = DEEPLEVELUPPERBOUND;
        }
    }
#endif

    int bestmove = -1;

    if (color == WHITE)
    {
        for (int i = 0; i < hcnt; i++)
        {
            int a = heuristic_list[i].a;
            int b = heuristic_list[i].b;
            unsigned long long hashnext = NextHash(zob, a, b, colornow);
            unsigned long long hash2next = NextHash2(zob2, a, b, colornow);

            board[a][b] = color;
            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next);
            if (depth == LEVEL)
            {
                showweight[a][b] = score;
            }
            board[a][b] = 0;
            if (score < beta)
            {
                beta = score;
                if (depth == LEVEL)
                {
                    showweight[a][b] = score;
                    bestmoverec.a = a;
                    bestmoverec.b = b;
                }
                bestmove = i;
                if (alpha >= beta)
                {
                    AddTo_history_table(history_table, a, b, depth);
                    bestmove = i;
#ifdef ENABLEHASH
                    {
                        // struct findresult result;
                        hashresult.point->weight = alpha;
                        hashresult.point->check = zob2;
                        hashresult.point->level = depth;
                        hashresult.point->type = ALPHA;
                    }
#endif
                    // **_socket = alpha;
                    // *_socket = 0;

                    return alpha;
                }
            }
        }

        {
#ifdef ENABLEHASH

            {
                // struct findresult result;
                hashresult.point->weight = beta;
                hashresult.point->check = zob2;
                hashresult.point->level = depth;
                hashresult.point->type = BETA;
            }
#endif
            // **_socket = beta;
            // *_socket = 0;

            if (bestmove != -1)
                AddTo_history_table(history_table, heuristic_list[bestmove].a, heuristic_list[bestmove].b, depth);
            return beta;
        }
    }
    else
    {

        for (int i = 0; i < hcnt; i++)
        {
            int a = heuristic_list[i].a;
            int b = heuristic_list[i].b;
            unsigned long long hashnext = NextHash(zob, a, b, colornow);
            unsigned long long hash2next = NextHash2(zob2, a, b, colornow);

            board[a][b] = color;
            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next);
            if (depth == LEVEL)
            {
                showweight[a][b] = score;
            }
            board[a][b] = 0;
            if (score > alpha)
            {
                alpha = score;
                if (depth == LEVEL)
                {
                    showweight[a][b] = score;
                    bestmoverec.a = a;
                    bestmoverec.b = b;
                }
                bestmove = i;
                if (alpha >= beta)
                {
                    AddTo_history_table(history_table, a, b, depth);
                    bestmove = i;

#ifdef ENABLEHASH
                    {
                        // struct findresult result;
                        hashresult.point->weight = beta;
                        hashresult.point->check = zob2;
                        hashresult.point->level = depth;
                        hashresult.point->type = BETA;
                    }
#endif
                    // **_socket = beta;
                    // *_socket = 0;

                    return beta;
                }
            }
        }

        {
#ifdef ENABLEHASH
            {

                // struct findresult result;
                hashresult.point->weight = alpha;
                hashresult.point->check = zob2;
                hashresult.point->level = depth;
                hashresult.point->type = ALPHA;
            }
#endif
            // **_socket = alpha;
            // *_socket = 0;

            // AddTo_history_table(history_table, heuristic_list[bestmove].a, heuristic_list[bestmove].b, depth);
            return alpha;
        }
    }
}

// struct move bestmoverec = {-1, -1};
// int Search(int color, int alpha, int beta, int depth, unsigned long long zob, unsigned long long zob2)
int AlgoFinal(int *ap, int *bp) //Write the position choosed into int* ap,int* bp;
{
    time_t timestart = clock();
    if (_ndefZobchain)
    {
        Setupzob();
        _ndefZobchain = 0;
    }

    if (fstmove && colornow == BLACK)
    {
        *ap = BOUNDRY / 2;
        *bp = BOUNDRY / 2;
        fstmove = 0;
        return 0;
    }

    // SHOWALL(weight, "int");
    memset(history_table, 0, sizeof(history_table));
    memset(showweight, 0, sizeof(showweight));
    AlphaBeta(LEVEL, colornow, -INF, INF, Getzob(), Getzob2());
    CK(bestmoverec.a);
    CK(bestmoverec.b);
    *ap = bestmoverec.a;
    *bp = bestmoverec.b;
    ShowWeightArray(showweight);
    if (board[*ap][*bp])
    {
        puts("I give up, TT......");
        AlgoPoint(ap, bp); //Just x** move;
    }

    // ClearWeightMartix_Algo3();
    time_t timeend = clock();
    CK(timeend - timestart);
    return 0;
}