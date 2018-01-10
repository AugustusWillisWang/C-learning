// Copyright (c) 2017-2018 Augustus Wang
// AlphaBeta剪枝和历史启发为基本框架, 其他部分通过头文件引入

//常量定义
#define ALGO_FINAL 3
#define EDGE 3

//程序设置
#define LEVEL 6
#define NEABOR 2 //for GetAroundPosition()
//(6,2)is recommended;
#define THINKINGUPPERBOUND 100
#define DEEPLEVELUPPERBOUND 60
#define DEEPLEVEL 4
// #define WEIGHTHEURISTIC
// #define ENABLEHASH
#define FUCK_PLAGIARIZER

#define ENABLEFBDMOVE
#define TIMELIMIT 15000

#include "zobrist.h"
#include "support.h"
#include "heuristic.h"
#include "weight.h"
#include "killfirst.h"
#include "fuck_plagiarizer.h"
#include "greedy.h"

//全局变量
int GetAroundPosition();
int showweight[BOUNDRY][BOUNDRY];
int WMartix[BOUNDRY][BOUNDRY];
time_t _starttime = 0;
int best_weight_found;
int maxlevel = LEVEL;
int thinkingupperbound = 200;
int deeplevelupperbound = 200;
int deeplevel = 4;
int maxneabor = 2;
//------------------------------------------
int ChangeMaxLevel()
{
    static int cnt = 0;
    cnt++;
    if (cnt == 1)
    {
        maxlevel = 12;
        thinkingupperbound = 15;
        deeplevelupperbound = 10;
        deeplevel = 6;
        maxneabor = 1;
        maxneabor = 2;
    }
    if (cnt == 2)
    {
        maxlevel = 8;
        thinkingupperbound = 250;
        deeplevelupperbound = 250;
        deeplevel = 9;
        // maxneabor = 1;
    }
    if (cnt == 4)
    {
        maxlevel = 8;
        thinkingupperbound = 120;
        deeplevelupperbound = 45;
        deeplevel = 4;
    }
    if (cnt == 8)
    {
        maxlevel = 8;
        thinkingupperbound = 80;
        deeplevelupperbound = 40;
        deeplevel = 4;
    }
    if (cnt == 10)
        maxlevel = 8;
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

int AlphaBeta(int depth, int color, int alpha, int beta, unsigned long long zob, unsigned long long zob2, int toplevel, int original_weight, int martix[BOUNDRY][BOUNDRY])
{
#ifdef TIMELIMIT
    if ((clock() - _starttime) > TIMELIMIT)
        return 0;
#endif

    if (original_weight > BIG_WEIGHT || original_weight < (-BIG_WEIGHT))
    {
        return original_weight;
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
        int weight = original_weight;

#ifdef ENABLEHASH
        SaveToZob(findresult, zob2, depth, VALUE, weight);
#endif
        return weight;
    }
    StartTimer(5);

    int type = 0;
    int valid_position[BOUNDRY][BOUNDRY];
    struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY];
    memset(heuristic_list, 0, sizeof(heuristic_list));
    int hcnt = 0; //hcnt-1 为最后一个节点的位置
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (martix[a][b])
            {
                AddTo_heuristic_list(heuristic_list, hcnt, a, b, depth, (martix[a][b]) + 100 * FindIn_history_table(history_table, a, b, depth));
                hcnt++;
            }
        }
    }

#ifdef KILLSEARCH
    if (hcnt == 0)
    {
        return original_weight;
    }
#endif

    Qsort_heuristic_element(heuristic_list, 0, hcnt - 1);

#ifdef THINKINGUPPERBOUND

    if (hcnt > thinkingupperbound)
        hcnt = thinkingupperbound;

#endif

#ifdef DEEPLEVELUPPERBOUND
    if (toplevel > deeplevel)
    {
        if (depth <= toplevel - deeplevel)
        {
            hcnt = deeplevelupperbound;
        }
    }
#endif
    EndTimer(5);

    int bestmove = -1;

    if (color == WHITE)
    {
        for (int i = 0; i < hcnt; i++)
        {
            int a = heuristic_list[i].a;
            int b = heuristic_list[i].b;
            unsigned long long hashnext = NextHash(zob, a, b, color);
            unsigned long long hash2next = NextHash2(zob2, a, b, color);

            board[a][b] = color;

            int(*t)[BOUNDRY];
            t = SavePWMartix(martix);
            UpdatePositionWeight(a, b, color, martix);
            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next, toplevel, UpdateWeight(a, b, original_weight),martix);
            board[a][b] = 0;
            RecoveryPWMartix(martix, t);
            if (depth == toplevel)
            {
                showweight[a][b] = score;
                //输出推断出的最好情况估分
                {
                    if (colornow == BLACK)
                    {
                        if (original_weight > best_weight_found)
                        {
                            best_weight_found = original_weight;
                        }
                    }
                    else if (original_weight < best_weight_found)
                    {
                        best_weight_found = original_weight;
                    }
                }
            }
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
            unsigned long long hashnext = NextHash(zob, a, b, color);
            unsigned long long hash2next = NextHash2(zob2, a, b, color);

            board[a][b] = color;
            int(*t)[BOUNDRY];
            t = SavePWMartix(martix);
            UpdatePositionWeight(a, b, color, martix);
            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next, toplevel, UpdateWeight(a, b, original_weight),martix);
            board[a][b] = 0;
            RecoveryPWMartix(martix, t);
            
            if (depth == toplevel)
            {
                showweight[a][b] = score;
                //输出推断出的最好情况估分
                {
                    if (colornow == BLACK)
                    {
                        if (original_weight > best_weight_found)
                        {
                            best_weight_found = original_weight;
                        }
                    }
                    else if (original_weight < best_weight_found)
                    {
                        best_weight_found = original_weight;
                    }
                }
            }
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
    int original_weight = GenerateWeight();
    StartTimer(6);

    ChangeMaxLevel();

    while (levelnow <= maxlevel)
    {
        printf("Started level %d at %d\n", levelnow, clock() - _starttime);
        AlphaBeta(levelnow, colornow, -INF, INF, Getzob(), Getzob2(), levelnow, original_weight,WMartix);
        levelnow++;
#ifdef TIMELIMIT
        if ((clock() - _starttime) < TIMELIMIT)
        {
            ltrec_a = bestmoverec.a;
            ltrec_b = bestmoverec.b;
            CK(ltrec_a);
            CK(ltrec_b);
        }
#endif
    }
    CK(ltrec_a);
    CK(ltrec_b);
    CK(historyhitcnt);
    bestmoverec.a = ltrec_a;
    bestmoverec.b = ltrec_b;
    EndTimer(6);
    ShowTimer();
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

    if (colornow == BLACK)
    {
        best_weight_found = -INF;
    }
    else
    {
        best_weight_found = INF;
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

    int original_weight = GenerateWeight();

#ifndef TIMELIMIT
    AlphaBeta(maxlevel, colornow, -INF, INF, Getzob(), Getzob2(), maxlevel, original_weight);
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
    CK(best_weight_found);
    return 0;
}
