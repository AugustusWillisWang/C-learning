// Copyright (c) 2017-2018 Augustus Wang

#define ALGO_FINAL 3
#define EDGE 3
#define LEVEL 7
#define NEABOR 1
//(6,2)is recommended;
// #define THINKINGUPPERBOUND 100
// #define DEEPLEVELUPPERBOUND 60
// #define DEEPLEVEL 4
// #define WEIGHTHEURISTIC
#define ENABLEHASH

#define ENABLEFBDMOVE
#define TIMELIMIT 15000

#include "zobrist.h"
#include "support.h"
#include "heuristic.h"
#include "weight.h"
#include "killfirst.h"
#include "fuck_plagiarizer.h"

int GetAroundPosition();
int showweight[BOUNDRY][BOUNDRY];
time_t _starttime = 0;

//------------------------------------------

int GetAroundPosition(int (*_ValidPosition)[BOUNDRY], int depth, int color)
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
                        if ((!board[_a][_b]) && (!checked[_a][_b]))
                        {
                            checked[_a][_b] = 1;
                            _ValidPosition[_a][_b] = 1;
#ifdef KILLSEARCH
                            if (depth <= (toplevel - KILLSEARCH))
                                _ValidPosition[_a][_b] *= TestKillPoint(_a, _b);

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

int hashv = 0; //dbghash

#define MAXNODE 20
struct move bestmoverec = {-1, -1};

int AlphaBeta(int depth, int color, int alpha, int beta, unsigned long long zob, unsigned long long zob2, int toplevel)
{
#ifdef TIMELIMIT
    if ((clock() - _starttime) > TIMELIMIT)
        return 0;
#endif
    int result = _JudgeWin();
    if (result)
    {
        return (result == BLACK) ? INF : (-INF);
    }

    int score;
#ifdef ENABLEHASH
    struct findresult findresult;
    findresult = FindInHashTable(zob, zob2, depth, color);

    _tot++;
    if (findresult.find)
    {
        score = findresult.weight;
        if (CheckHashResult(findresult, alpha, beta) && (depth != toplevel))
        {
            _hit++;
            //dbghash
            hashv = score;
            // return score;
        }
    }
#endif

    if (depth <= 0)
    {
        int weight = GenerateWeight();

#ifdef ENABLEHASH
        SaveToZob(findresult, zob2, depth, VALUE, weight);
#endif
        return weight;
    }

    int type = 0;
    int valid_position[BOUNDRY][BOUNDRY];
    memset(valid_position, 0, sizeof(valid_position));
    GetAroundPosition(valid_position, depth, color);
    struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY];
    memset(heuristic_list, 0, sizeof(heuristic_list));
    int hcnt = 0; //hcnt-1 为最后一个节点的位置
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (valid_position[a][b])
            {
                AddTo_heuristic_list(heuristic_list, hcnt, a, b, depth, 1 * FindIn_history_table(history_table, a, b, depth));
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
    if (toplevel > DEEPLEVEL)
    {
        if (depth <= toplevel - DEEPLEVEL)
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
            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next, toplevel);
            if (depth == toplevel)
            {
                showweight[a][b] = score;
            }
            board[a][b] = 0;
            if (score < beta)
            {
                beta = score;
                if (depth == toplevel)
                {
                    showweight[a][b] = score;
                    bestmoverec.a = a;
                    bestmoverec.b = b;
                }
                bestmove = i;
                type = VALUE;
                if (alpha >= beta)
                {
                    AddTo_history_table(history_table, a, b, depth);
                    bestmove = i;

#ifdef ENABLEHASH
                    SaveToZob(findresult, zob2, depth, UPPER, score);
#endif

                    return alpha;
                }
            }
        }

        {
#ifdef ENABLEHASH

            if (type)
                SaveToZob(findresult, zob2, depth, VALUE, beta);

            else
                SaveToZob(findresult, zob2, depth, LOWER, beta);

#endif

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
            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next, toplevel);
            if (depth == toplevel)
            {
                showweight[a][b] = score;
            }
            board[a][b] = 0;
            if (score > alpha)
            {
                alpha = score;
                if (depth == toplevel)
                {
                    showweight[a][b] = score;
                    bestmoverec.a = a;
                    bestmoverec.b = b;
                }
                bestmove = i;
                type == VALUE;
                if (alpha >= beta)
                {
                    AddTo_history_table(history_table, a, b, depth);
                    bestmove = i;

#ifdef ENABLEHASH

                    SaveToZob(findresult, zob2, depth, LOWER, score);

#endif
                    // **_socket = beta;
                    // *_socket = 0;

                    return beta;
                }
            }
        }

        {
#ifdef ENABLEHASH

            if (type)
                SaveToZob(findresult, zob2, depth, VALUE, alpha);

            else
                SaveToZob(findresult, zob2, depth, UPPER, alpha);

#endif
            // **_socket = alpha;
            // *_socket = 0;

            // AddTo_history_table(history_table, heuristic_list[bestmove].a, heuristic_list[bestmove].b, depth);
            return alpha;
        }
    }
}

int IterativeDeepenAB()
{
    _starttime = clock();
    int levelnow = 1;
    int ltrec_a;
    int ltrec_b;
    while (levelnow <= LEVEL)
    {
        printf("Started level %d at %d\n", levelnow, clock() - _starttime);
        AlphaBeta(levelnow, colornow, -INF, INF, Getzob(), Getzob2(), levelnow);
        levelnow++;
        if ((clock() - _starttime) < TIMELIMIT)
        {
            ltrec_a = bestmoverec.a;
            ltrec_b = bestmoverec.b;
            CK(ltrec_a);
            CK(ltrec_b);
        }
    }
    CK(ltrec_a);
    CK(ltrec_b);
    bestmoverec.a = ltrec_a;
    bestmoverec.b = ltrec_b;
    return 0;
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
#ifdef FUCK_PLAGIARIZER
        RandomFirstMove(ap, bp); //首步随机落子函数, 防止对手使用不支持平移的开局库
#endif
        fstmove = 0;
        return 0;
    }

    // SHOWALL(weight, "int");
    memset(history_table, 0, sizeof(history_table));
    memset(showweight, 0, sizeof(showweight));

#ifndef TIMELIMIT
    AlphaBeta(LEVEL, colornow, -INF, INF, Getzob(), Getzob2(), LEVEL);
#else
    IterativeDeepenAB();
#endif

    // CK(bestmoverec.a);
    // CK(bestmoverec.b);
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
    // CK(timeend - timestart);
    printf("Used %dms in total.\n", timeend - timestart);
#ifdef ENABLEHASH
    CK(_hit);
    _hit = 0;
    CK(_tot);
    _tot = 0;
#endif
    return 0;
}
