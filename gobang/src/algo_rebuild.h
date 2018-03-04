// Copyright (c) 2017-2018 Augustus Wang
// AlphaBeta剪枝和历史启发为基本框架, 其他部分通过头文件引入

//常量定义
#define ALGO_FINAL 3
#define EDGE 3
//程序设置
#define LEVEL 10 //最大搜索层数
#define NEABOR 2 //for GetAroundPosition(), 落子时只考虑已有棋子边NEABOR个点
//(6,2)is recommended;
#define THINKINGUPPERBOUND  //设置启发上界
#define DEEPLEVELUPPERBOUND //在层数较深时降低启发上界
#define DEEPLEVEL           //定义"较深的层数"
// #define WEIGHTHEURISTIC
#define ENABLEHASH //激活置换表
#define RANDFST    //首步随机落子
// #define DEFENDMODE //白棋前十步采取守势

#define ENABLEFBDMOVE   //禁手探测 (会极大拖慢速度)
#define TIMELIMIT 3000 //迭代加深时间限制

#include "zobrist.h"   //哈希
#include "support.h"   //全局变量, 共用函数
#include "heuristic.h" //启发式搜索框架
#include "weight.h"    //部分更新估值函数
// #include "change.h"    //部分更新估值函数
//原有估值存在严重bug!
#include "killfirst.h" //胜手深搜(未启用)
#include "rand_move.h" //随机落子
#include "greedy.h"    //贪婪启发(未启用)
#include "printboard.h"

//全局变量
int GetAroundPosition();          //查找周围的可用位置
int showweight[BOUNDRY][BOUNDRY]; //权重数组, 调试使用
time_t _starttime = 0;            //计时函数使用, 用于控制迭代加深搜索的时间
int best_weight_found;            //显示当前局面评分
int maxlevel = LEVEL;             // 搜索层数控制
int thinkingupperbound = 200;     //搜索宽度
int deeplevelupperbound = 200;    //深层搜索宽度
int deeplevel = 10;               //"深层"
int maxneabor = NEABOR;           //落子时只考虑已有棋子边NEABOR个点
int defendmode = 0;               //白棋特殊操作
//------------------------------------------
int ChangeMaxLevel() //按照当前手数对全局变量进行调整
{
    // return 0;
    static int cnt = 0; //子数统计
    cnt++;

#ifdef WEIGHTHEURISTIC
            thinkingupperbound = 10;
            deeplevelupperbound = 7;
            deeplevel = 4;
            maxlevel = 12;
            return 0;
#endif
            if (colornow == WHITE)
            {
                if (cnt == 1)
                {
                    maxlevel = 8;
                    // thinkingupperbound = 250;
                    // deeplevelupperbound = 250;
                    deeplevel = 9;
                    maxneabor = 1;
                }
                if (cnt == 2)
                {
                    maxlevel = 9;
                    // thinkingupperbound = 200;
                    // deeplevelupperbound = 200;
                    deeplevel = 10;
                    maxneabor = 1;
#ifdef DEFENDMODE
            defendmode = 1;
#endif
        }
        if (cnt == 4)
        {
            maxlevel = 9;
            // thinkingupperbound = 200;
            // deeplevelupperbound = 200;
            // deeplevel = 4;
            defendmode = 1;
        }
        if (cnt == 8)
        {
            maxlevel = 9;
            // thinkingupperbound = 200;
            // deeplevelupperbound = 200;
            // deeplevel = 6;
            maxneabor = 1;
        }
        if (cnt == 10)
        {
            maxlevel = 9;
            deeplevel = 4;
            maxneabor = 1;
            defendmode = 0;
        }
    }
    else
    {
        if (cnt == 1)
        {
            maxlevel = 9;
            // thinkingupperbound = 250;
            // deeplevelupperbound = 250;
            deeplevel = 9;
            maxneabor = 1;
            // defendmode = 1;
        }
        if (cnt == 2)
        {
            maxlevel = 9;
            // thinkingupperbound = 200;
            // deeplevelupperbound = 200;
            deeplevel = 6;
            maxneabor = 1;
            // #ifdef DEFENDMODE
            //             defendmode = 1;
            // #endif
        }
        if (cnt == 3)
        {
            maxlevel = 9;
            thinkingupperbound = 200;
            deeplevelupperbound = 200;
            deeplevel = 9;
        }
        if (cnt == 8)
        {
            maxlevel = 9;
            thinkingupperbound = 50;
            deeplevelupperbound = 30;
            deeplevel = 6;
            defendmode = 0;
            maxneabor = 1;
        }
        if (cnt == 10)
        {
            maxlevel = 9;
            deeplevel = 4;
            maxneabor = 1;
            defendmode = 0;
        }
    }
}

int GetAroundPosition(int (*_ValidPosition)[BOUNDRY], int depth, int color, int toplevel) //查找可落子点位置, 支持在这里进行禁手判断和其他操作 (旧版)
//新版的函数保存了一个全局数组, 每次更新时只处理新落子周围的部分. 新函数在weight.h中
{
    int checked[BOUNDRY][BOUNDRY]; //记录已经检查过的点, 防止重复检查
    memset(checked, 0, sizeof(checked));
    memset(_ValidPosition, 0, sizeof(int) * BOUNDRY * BOUNDRY);

    // if (depth == toplevel)
    // {
    //     if (haveonekill)
    //     {
    //         memcpy(_ValidPosition, onekillmove, sizeof(onekillmove));
    //         return 1;
    //     }
    // }
    StartTimer(4);

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++) //遍历棋盘
        {
            if (board[a][b])
            {
                if (defendmode) //白棋采取守势, 特殊走法
                {
                    if (board[a][b] == WHITE)
                        continue;
                }
                for (int ia = -maxneabor; ia <= maxneabor; ia++)
                {
                    for (int ib = -maxneabor; ib <= maxneabor; ib++)
                    {
                        int _a = BoundLim(a + ia); //BoundLim的作用是将点坐标转化为合法的坐标, 将超出边界的值转移到边界上
                        int _b = BoundLim(b + ib);
                        if ((!board[_a][_b]) && (!checked[_a][_b]))
                        {
                            checked[_a][_b] = 1;
                            _ValidPosition[_a][_b] = 1;
#ifdef KILLSEARCH //胜手深搜 \
    //经过考虑后决定不开启此功能, 如果开启, 建议使用多线程与主搜索函数同步进行
                            if (depth <= (toplevel - KILLSEARCH))
                                _ValidPosition[_a][_b] *= TestKillPoint(_a, _b);
#endif

                            //此功能被整合到权值判断中以加速
                            // #ifdef ENABLEFBDMOVE //禁手判断, 如果是禁手则标为禁止落子点
                            //                             _ValidPosition[_a][_b] *= !ForbidMove(_a, _b, color);
                            // #endif
                            if ((defendmode && (depth == toplevel)))
                                _ValidPosition[_a][_b] *= threat_martix[_a][_b];
                        }
                    }
                }
            }
        }
    }
    EndTimer(4);
}

// #define OUTPUTWEIGHT                         \
//     {                                        \
//         if (color == BLACK && step == LEVEL) \
//         {                                    \
//             weight[a][b] = max;              \
//         }                                    \
//         if (color == WHITE && step == LEVEL) \
//         {                                    \
//             weight[a][b] = min;              \
//         }                                    \
//     }

int hashv = 0; //DBG_hash

struct move bestmoverec = {-1, -1}; //记录结果

int AlphaBeta(int depth, int color, int alpha, int beta, unsigned long long zob, unsigned long long zob2, int toplevel, int original_weight) //搜索主函数
{

//AlphaBeta值可以理解成根据之前的结果所估计出的有效评分的界, 超出界限的直接剪枝以提高速度

#ifdef TIMELIMIT //迭代加深时间控制, 如此层没有完成使用上一层的结果(见IDAB函数)
    if ((clock() - _starttime) > TIMELIMIT)
        return 0;
#endif

    // if(original_weight!=GenerateWeight()){
    //     CK(depth);
    //     CK(original_weight);
    //     CK(GenerateWeight());
    // }
    if (original_weight > BIG_WEIGHT || original_weight < (-BIG_WEIGHT)) //一方胜利直接返回
    {
        return original_weight;
    }

    int score;
#ifdef ENABLEHASH //检查哈希表中是否已经存在可用值
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
            // hashv = score;
            // return score;
        }
    }
#endif

    if (depth <= 0) //叶子节点返回估值
    {
        int weight = original_weight;

#ifdef ENABLEHASH
        SaveToZob(findresult, zob2, depth, VALUE, weight); //保存到哈希表
#endif
        return weight;
    }
    StartTimer(5);

    int type = 0;                         //若要使用哈希表, 需要保存节点类型
    int valid_position[BOUNDRY][BOUNDRY]; //可用位置
    int weight_reg[BOUNDRY][BOUNDRY];     //保存计算出的权值
    memset(valid_position, 0, sizeof(valid_position));
    GetAroundPosition(valid_position, depth, color, toplevel);  //查找可用位置, 判断禁手, etc
    struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY]; //准备启发式搜索
    memset(heuristic_list, 0, sizeof(heuristic_list));
    int hcnt = 0; //hcnt-1 为最后一个节点的位置

    struct fbd_weight result;

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (valid_position[a][b])
            {
                //收集元素, 准备排序.
                board[a][b] = color;
                result = UpdateFBDWeight(a, b, original_weight);
                board[a][b] = 0;

                if (!result.fbd) //若非禁手
                {
                    weight_reg[a][b] = result.weight;
#ifdef WEIGHTHEURISTIC
                    AddTo_heuristic_list(heuristic_list, hcnt, a, b, depth, Abs(weight_reg[a][b]) + 100 * FindIn_history_table(history_table, a, b, depth));
#else
                    AddTo_heuristic_list(heuristic_list, hcnt, a, b, depth, FindIn_history_table(history_table, a, b, depth));
#endif
                    hcnt++;
                }
            }
        }
    }

#ifdef KILLSEARCH
    if (hcnt == 0)
    {
        //若无法再进行胜手深搜
        return original_weight;
    }
#endif

    Qsort_heuristic_element(heuristic_list, 0, hcnt - 1); //对启发节点排序

#ifdef THINKINGUPPERBOUND //若设置了搜索宽度, 只搜索最靠前的节点

    if (hcnt > thinkingupperbound)
        hcnt = thinkingupperbound;

#endif

#ifdef DEEPLEVELUPPERBOUND //深层搜索宽度控制
    if (toplevel > deeplevel)
    {
        if (depth <= toplevel - deeplevel)
        {
            hcnt = deeplevelupperbound;
        }
    }
#endif
    EndTimer(5);

    int bestmove = -1; //bestmove存贮找到的最好走法在第几个节点

    if (color == WHITE) //这一节点会去选取
    {
        for (int i = 0; i < hcnt; i++) //按先后顺序探测各个节点
        {
            //读取坐标
            int a = heuristic_list[i].a;
            int b = heuristic_list[i].b;
            //在原有基础上计算新的Hash
            unsigned long long hashnext = NextHash(zob, a, b, color);
            unsigned long long hash2next = NextHash2(zob2, a, b, color);

            //走子
            board[a][b] = color;

#ifdef ENABLEFBDMOVE

            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next, toplevel, weight_reg[a][b]); //搜索, 传入计算好的hash值和估值
#else
            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next, toplevel, weight_reg[a][b]); //搜索, 传入计算好的hash值和估值
#endif
            //撤销
            board[a][b] = 0;

            if (depth == maxlevel) //根节点
            {
                showweight[a][b] = score;
                //输出推断出的最好情况估分
                {
                    if (colornow == BLACK)
                    {
                        if (score > best_weight_found)
                        {
                            best_weight_found = score;
                        }
                    }
                    else if (score < best_weight_found)
                    {
                        best_weight_found = score;
                    }
                }
            }

            if (score < beta) //对于白节点, 要找到最小的有效估值, 它取最小的有效值, 在发现新的有效值之后降低上界
            {
                beta = score;
                if (depth == toplevel) //根节点
                {
                    // showweight[a][b] = score;
                    bestmoverec.a = a;
                    bestmoverec.b = b;
                    //这是目前找到的最好点
                }
                bestmove = i;
                type = VALUE;
                if (alpha >= beta) //可行窗口为0, 不会出现此种情况, 直接剪枝
                {
                    AddTo_history_table(history_table, a, b, depth); //更新历史记录
                    bestmove = i;

#ifdef ENABLEHASH
                    SaveToZob(findresult, zob2, depth, UPPER, score); //保存到哈希表
#endif
                    //剪枝
                    return alpha;
                }
            }
        }

        {
#ifdef ENABLEHASH

            if (type)
                SaveToZob(findresult, zob2, depth, VALUE, beta); //保存到哈希表

            else
                SaveToZob(findresult, zob2, depth, LOWER, beta); //保存到哈希表

#endif

            if (bestmove != -1)
                AddTo_history_table(history_table, heuristic_list[bestmove].a, heuristic_list[bestmove].b, depth); //更新历史记录
            return beta;
        }
    }
    else //黑色节点, 注释同上
    {

        for (int i = 0; i < hcnt; i++)
        {
            int a = heuristic_list[i].a;
            int b = heuristic_list[i].b;
            unsigned long long hashnext = NextHash(zob, a, b, color);
            unsigned long long hash2next = NextHash2(zob2, a, b, color);

            board[a][b] = color;
#ifdef ENABLEFBDMOVE
            // if(GenerateFBDWeight()!=UpdateFBDWeight(a, b, original_weight))printf("bommmmmmm%d %d\n",GenerateFBDWeight(),UpdateFBDWeight(a, b, original_weight));

            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next, toplevel, weight_reg[a][b]); //搜索, 传入计算好的hash值和估值
#else
            score = AlphaBeta(depth - 1, Inverse(color), alpha, beta, hashnext, hash2next, toplevel, weight_reg[a][b]); //搜索, 传入计算好的hash值和估值
#endif
            board[a][b] = 0;
            if (depth == maxlevel)
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

int IterativeDeepenAB() //迭代深化
{
    _starttime = clock();
    int levelnow = 4; //从一层开始不断加深
    int ltrec_a;      //找到的最好点记录
    int ltrec_b;      //找到的最好点记录

#ifdef ENABLEFBDMOVE
    int original_weight = GenerateFBDWeight(); //产生初始局面估值
#else
    int original_weight = GenerateWeight();                                                                             //产生初始局面估值
#endif
    StartTimer(6);

    ChangeMaxLevel(); //按手数调整参数

    while (levelnow <= maxlevel)
    {
        printf("Started level %d at %d\n", levelnow, clock() - _starttime);
        AlphaBeta(levelnow, colornow, -INF, INF, Getzob(), Getzob2(), levelnow, original_weight);
        levelnow += 1;
#ifdef TIMELIMIT
        if ((clock() - _starttime) < TIMELIMIT) //采纳在时间不超限的情况下最后一个结果
        {
            ltrec_a = bestmoverec.a;
            ltrec_b = bestmoverec.b;
            ShowMove(ltrec_a, ltrec_b, colornow); //顺便显示当前走子位置
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
int AlgoFinal(int *ap, int *bp) //Write the position choosed into int* ap,int* bp; //AI主函数, 会将计算结果写到两个int* 所指的地址上
{
    time_t timestart = clock();
    if (_ndefZobchain) //初始化hash表
    {
        Setupzob();
        _ndefZobchain = 0;
    }

    //初始化最佳分数
    if (colornow == BLACK)
    {
        best_weight_found = -INF;
    }
    else
    {
        best_weight_found = INF;
    }

    //首步落子
    if (fstmove && colornow == BLACK)
    {
        *ap = BOUNDRY / 2;
        *bp = BOUNDRY / 2;
#ifdef RANDFST
        RandomFirstMove(ap, bp); //首步随机落子函数, 防止对手使用不支持平移的开局库
#endif
        fstmove = 0;
        return 0;
    }

    // SHOWALL(weight, "int");
    memset(history_table, 0, sizeof(history_table)); //每次重置历史启发所用的历史记录表
    memset(showweight, 0, sizeof(showweight));

    TestOneStepKill(colornow);//确定当前是否有必胜点

#ifndef TIMELIMIT
#ifdef ENABLEFBDMOVE
    int original_weight = GenerateFBDWeight(); //产生当前局面估分
#else
    int original_weight = GenerateWeight(); //产生当前局面估分
#endif
    AlphaBeta(maxlevel, colornow, -INF, INF, Getzob(), Getzob2(), maxlevel, original_weight);
#else
    IterativeDeepenAB();
#endif

    // CK(bestmoverec.a);
    // CK(bestmoverec.b);
    *ap = bestmoverec.a;
    *bp = bestmoverec.b;
    ShowWeightArray(showweight);
    if (board[*ap][*bp]) //错误检查
    {
        puts("I give up, TT......"); //如果发现错误, 就随机落子(大雾)
        AlgoPoint(ap, bp);           //Just x** move;
    }

    // ClearWeightMartix_Algo3();
    time_t timeend = clock();
    // CK(timeend - timestart);
    printf("Used %dms in total.\n", timeend - timestart);
#ifdef ENABLEHASH //统计hash的hit数
    CK(_hit);
    _hit = 0;
    CK(_tot);
    _tot = 0;
#endif
    // CK(best_weight_found); //显示当前局面评分
    return 0;
}
