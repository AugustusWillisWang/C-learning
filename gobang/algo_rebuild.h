//对矩阵的各点进行查找
//Based on algo_point.
//ALGO_MINMAX
#define ALGO_FINAL 3
#define EDGE 3
#define LEVEL 3

#include "zobrist.h"
#include "support.h"
#include "heuristic.h"

//这里的权值是随便赋的
#define W1_2 0
#define W2_2 (4 / 2)
#define W3_2 (500 / 3)
#define W4_2 (20000 / 4)

#define W1_1 0
#define W2_1 (1 / 2)
#define W3_1 (10 / 3)
#define W4_1 (500 / 4)

#define W5 10000000.0

double WeightContribute_Algo3(); //Gen weight for a single line in _Testline_[9]
double PointGenWeightForShapeNow_Algo3();
int ClearWeightMartix_Algo3();
//--------------------------------------------

int SimpleSituationCheck_Algo3(); //Check 4-1 4-2 3-2 in order. If such situation exists, constrain avaliable position to such areas.
int GenNaiveConstrain_Algo3();
int PointTestNaiveSituationForShapeNow_Algo3();
int GetAroundPosition();

double Minmax();

int _algo3_havenot_clear_array = 1;

//------------------------------------------

int _ValidPositionForFinalAlgo[BOUNDRY][BOUNDRY];
// int _TestedPositionForFinalAlgo[BOUNDRY][BOUNDRY];
int _Testline_[9]; //Get 9 elements out to check the weight.

// double _weightnow_;

int aget;
int bget;

//  int JudgeWinPlus();
//  int _LinearWeightCnter(int a, int b, int mode); //if mode==CLEAR, set cnt,max,color=0

//colornow is known;

double WeightContribute_Algo3()
//Deal with the 1-d 9 element array, return the weight generated.
//At the same time, mark the point tested.(Obsoleted)
{
    //  int _Testline_[9];//Get 9 elements out to check the weight.
    int leftblocked = 0;
    int rightblocked = 0;
    int cnt = 0;
    int position = 4; //The middle of the 9 positions.
    //Get the weight of this position.
    if (_Testline_[position] == 0)
        return 0;
    cnt++;
    int colorinmiddle = _Testline_[position];
    while (_Testline_[--position] == colorinmiddle) //Highlight!
    {
        cnt++;
        if (0 == position)
            break;
    }
    switch (_Testline_[position])
    {

    case 0:
        leftblocked = 0;
        break;

    default:
        leftblocked = 1;
        break;
    }
    position = 4;
    while (_Testline_[++position] == colorinmiddle) //Highlight!
    {
        cnt++;
        if (8 == position)
            break;
    }
    switch (_Testline_[position])
    {
    case 0:
        rightblocked = 0;
        break;

    default:
        rightblocked = 1;
        break;
    }

    //If 5 link is impossible to achieve, then return 0;
    int linkmax = 1;
    position = 4;
    while (position >= 0 && _Testline_[--position] != Inverse(colorinmiddle) && _Testline_[position] != EDGE)
    {
        linkmax++;
    }
    position = 4;
    while (position < 9 && _Testline_[++position] != Inverse(colorinmiddle) && _Testline_[position] != EDGE)
    {
        linkmax++;
    }
    if (linkmax < 5)
        return 0;

    //Return weight according to cnt, l,r,blocked;

    switch (cnt)
    {
    case 1:
        switch (leftblocked + rightblocked)
        {
        case 0:
            return (colornow == BLACK ? 1 : -1) * W1_2;
        case 1:
            return (colornow == BLACK ? 1 : -1) * W1_1;
        case 2:
            return (colornow == BLACK ? 1 : -1) * 0;
        }
    case 2:
        switch (leftblocked + rightblocked)
        {
        case 0:
            return (colornow == BLACK ? 1 : -1) * W2_2;
        case 1:
            return (colornow == BLACK ? 1 : -1) * W2_1;
        case 2:
            return (colornow == BLACK ? 1 : -1) * 0;
        }
    case 3:
        switch (leftblocked + rightblocked)
        {
        case 0:
            return (colornow == BLACK ? 1 : -1) * W3_2;
        case 1:
            return (colornow == BLACK ? 1 : -1) * W3_1;
        case 2:
            return (colornow == BLACK ? 1 : -1) * 0;
        }
    case 4:
        switch (leftblocked + rightblocked)
        {
        case 0:
            return (colornow == BLACK ? 1 : -1) * W4_2;
        case 1:
            return (colornow == BLACK ? 1 : -1) * W4_1;
        case 2:
            return (colornow == BLACK ? 1 : -1) * 0;
        }
    case 5:
        return (colornow == BLACK ? 1 : -1) * W5;
    }
    return 0;
}

double PointGenWeightForShapeNow_Algo3()
{
    double weight_for_shape_now = 0.0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            for (int aget = a - 4, i = 0, bget = b; aget <= a + 4; aget++, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline_[i] = board[aget][bget];
                }
                else
                {
                    _Testline_[i] = EDGE;
                }
            }

            weight_for_shape_now += WeightContribute_Algo3();
            for (int bget = b - 4, aget = a, i = 0; bget <= b + 4; bget++, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline_[i] = board[aget][bget];
                }
                else
                {
                    _Testline_[i] = EDGE;
                }
            }
            weight_for_shape_now += WeightContribute_Algo3();

            for (int aget = a - 4, bget = b - 4, i = 0; aget <= a + 4; aget++, bget++, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline_[i] = board[aget][bget];
                }
                else
                {
                    _Testline_[i] = EDGE;
                }
            }
            weight_for_shape_now += WeightContribute_Algo3();

            for (int aget = a - 4, bget = b + 4, i = 0; aget <= a + 4; aget++, bget--, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline_[i] = board[aget][bget];
                }
                else
                {
                    _Testline_[i] = EDGE;
                }
            }
            weight_for_shape_now += WeightContribute_Algo3();
        }
    }
    return weight_for_shape_now;
}

    // int Show_ValidArray_Algo3()
    // {
    //     for (int a = 0; a < BOUNDRY; a++)
    //     {
    //         for (int b = 0; b < BOUNDRY; b++)
    //         {
    //             printf("%d ", _ValidPosition[a][b]);
    //         }
    //         puts("");
    //     }
    // }

#include "simpletest.h"

//Minmax:

// int _JudgeWin();

double MaxWeight(int (*weight)[BOUNDRY])
{
    double max = NINF;
    //    double min = 100000000000.0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (weight[a][b] > max)
                max = weight[a][b];
        }
    }
    return max;
}

double MinWeight(int (*weight)[BOUNDRY])
{
    double min = INF;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (weight[a][b] < min)
                min = weight[a][b];
        }
    }
    return min;
}

int GetAroundPosition(int (*_ValidPosition)[BOUNDRY])
{
    memset(_ValidPosition, 0, sizeof(int) * BOUNDRY * BOUNDRY);
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b])
            {
                for (int ia = -2; ia <= 2; ia++)
                {
                    for (int ib = -2; ib <= 2; ib++)
                    {
                        if (!board[BoundLim(a + ia)][BoundLim(b + ib)])
                            _ValidPosition[BoundLim(a + ia)][BoundLim(b + ib)] = 1;
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

double Search(int color, double alpha, double beta, int depth, unsigned long long zob, unsigned long long zob2)
{
    int win = _JudgeWin();
    if (win)
    {
        if (win == BLACK)
            return INF;
        if (win == WHITE)
            return INF;
        BOOM("this should not happen");
    }

    double score;
    double *__soc = 0;
    double **_socket = &__soc;

    score = FindInHashTable(zob, zob2, depth, _socket);
    //If in hash table
    if (0 == *_socket)
        return score;

    //If not in hash table;
    //If depth==0;
    if (depth <= 0)
    {
        score = (color == BLACK ? 1 : -1) * PointGenWeightForShapeNow_Algo3(); //Return evaluate
        **_socket = score;
        *_socket = 0;

        return score;
    }

    //depth!=0;
    int valid_position[BOUNDRY][BOUNDRY];
    memset(valid_position, 0, sizeof(valid_position));
    GetAroundPosition(valid_position);
    struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY];
    int hcnt = 0; //hcnt-1 为最后一个节点的位置
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (valid_position[a][b])
            {
                AddTo_heuristic_list(heuristic_list, hcnt, a, b, depth, FindIn_history_table(history_table, a, b, depth));
                hcnt++;
            }
        }
    }
    Qsort_heuristic_element(heuristic_list, 0, hcnt - 1);

    int bestmove = -1;

    for (int i = 0; i < hcnt; i++)
    {
        int a = heuristic_list[i].a;
        int b = heuristic_list[i].b;
        unsigned long long hashnext = NextHash(zob, a, b, colornow);
        unsigned long long hash2next = NextHash2(zob2, a, b, colornow);

        board[a][b] = color;
        color = Inverse(color);
        score = -Search(color, -beta, -alpha, depth - 1, hashnext, hash2next);
        color = Inverse(color);
        board[a][b] = 0;

        //debug
        // if (depth == LEVEL)
        // {
        //     ShowWeightArray(weight);
        //     memset(weight, 0, sizeof(weight));
        // }
        // if (depth == LEVEL - 1)
        //     weight[a][b] = score;
        if (score > alpha)
        {
            alpha = score;

            if (depth == LEVEL)
            {
                bestmoverec.a = a;
                bestmoverec.b = b;
            }
            bestmove = i;
        }
        if (alpha >= beta)
        {
            AddTo_history_table(history_table, a, b, depth);
            bestmove = i;
            return beta;
            break;
        }
    }
    if (bestmove != (-1))
    {
        **_socket = beta;
        *_socket = 0;

        AddTo_history_table(history_table, heuristic_list[bestmove].a, heuristic_list[bestmove].b, depth);
        return alpha;
    }
}

int AlphaBeta(int depth, int color, double alpha, double beta)
{
    int result = _JudgeWin();
    if (result)
    {
        return (result == BLACK) ? INF : (-INF);
    }
    if (depth <= 0)
        return PointGenWeightForShapeNow_Algo3();
    int valid_position[BOUNDRY][BOUNDRY];
    memset(valid_position, 0, sizeof(valid_position));
    GetAroundPosition(valid_position);

    double score;
    if (color == WHITE)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                if (valid_position[a][b])
                {
                    board[a][b] = color;
                    score = AlphaBeta(depth - 1, Inverse(color), alpha, beta);
                    board[a][b] = 0;
                    if (score < beta)
                    {
                        beta = score;
                        if (depth == LEVEL)
                        {
                            weight[a][b] = score;
                            bestmoverec.a = a;
                            bestmoverec.b = b;
                        }
                        if (alpha >= beta)
                        {
                            return alpha;
                        }
                    }
                }
            }
        }
        return beta;
    }
    else
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                if (valid_position[a][b])
                {
                    board[a][b] = color;
                    score = AlphaBeta(depth - 1, Inverse(color), alpha, beta);
                    board[a][b] = 0;
                    if (score > alpha)
                    {
                        alpha = score;
                        if (depth == LEVEL)
                        {
                            weight[a][b] = score;
                            bestmoverec.a = a;
                            bestmoverec.b = b;
                        }
                        if (alpha >= beta)
                        {
                            return beta;
                        }
                    }
                }
            }
        }
        return alpha;
    }
}

// struct move bestmoverec = {-1, -1};
// double Search(int color, double alpha, double beta, int depth, unsigned long long zob, unsigned long long zob2)
int AlgoFinal(int *ap, int *bp) //Write the position choosed into int* ap,int* bp;
{
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

    // SHOWALL(weight, "double");
    memset(history_table, 0, sizeof(history_table));
    memset(weight, 0, sizeof(weight));
    // Search(colornow, -INF, INF, LEVEL, Getzob(), Getzob2());
    AlphaBeta(LEVEL, colornow, -INF, INF);
    CK(bestmoverec.a);
    CK(bestmoverec.b);
    // ShowWeightArray_Algo3();
    // BP;
    *ap = bestmoverec.a;
    *bp = bestmoverec.b;
    if (board[*ap][*bp])
    {
        scanf("%d", *ap);
        BOOM("wrong position!");
    }
    ShowWeightArray(weight);

    // ClearWeightMartix_Algo3();

    return 0;
}
