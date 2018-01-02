// #include "lazy.h"
#define LEVEL 3
#include "support.h"
#include "heuristic.h"
int main()
{
    memset(history_table, 0, sizeof(history_table));
    AddTo_history_table(history_table, 1, 2, 0);
    AddTo_history_table(history_table, 2, 3, 1);
    AddTo_history_table(history_table, 3, 4, 2);
    AddTo_history_table(history_table, 4, 5, 2);
    AddTo_history_table(history_table, 5, 6, 3);
    printf("%d\n", FindIn_history_table(history_table, 2, 3, 2));
    printf("%d\n", FindIn_history_table(history_table, 2, 3, 1));
    struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY];
    memset(heuristic_list, 0, sizeof(heuristic_list));
    AddTo_heuristic_list(heuristic_list, 0, 1, 2, 0, FindIn_history_table(history_table, 1, 2, 1));
    AddTo_heuristic_list(heuristic_list, 1, 2, 3, 1, FindIn_history_table(history_table, 2, 3, 1));
    AddTo_heuristic_list(heuristic_list, 2, 3, 4, 2, FindIn_history_table(history_table, 3, 4, 2));
    AddTo_heuristic_list(heuristic_list, 3, 4, 5, 2, FindIn_history_table(history_table, 4, 5, 2));
    AddTo_heuristic_list(heuristic_list, 4, 5, 6, 3, FindIn_history_table(history_table, 5, 6, 3));
    Qsort_heuristic_element(heuristic_list, 0, 4);

    return 0;
}

int AlphaBeta(int depth, int color, double alpha, double beta, unsigned long long zob, unsigned long long zob2)
{
    int result = _JudgeWin();
    if (result)
    {
        return (result == BLACK) ? INF : (-INF);
    }

    double score;
    // double *__soc = 0;
    // double **_socket = &__soc;
    // score = FindInHashTable(zob, zob2, depth, _socket);
    // if (0 == *_socket)
        // return score;

    if (depth <= 0)
        return PointGenWeightForShapeNow_Algo3();
    int valid_position[BOUNDRY][BOUNDRY];
    memset(valid_position, 0, sizeof(valid_position));
    GetAroundPosition(valid_position);
    struct heuristic_element heuristic_list[BOUNDRY * BOUNDRY];
    memset(heuristic_list, 0, sizeof(heuristic_list));
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
                bestmove = i;
                if (alpha >= beta)
                {
                    AddTo_history_table(history_table, a, b, depth);
                    bestmove = i;
                    return alpha;
                }
            }
        }
        if (bestmove != (-1))
        {
            // **_socket = beta;
            // *_socket = 0;

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
                bestmove = i;
                if (alpha >= beta)
                {
                    AddTo_history_table(history_table, a, b, depth);
                    bestmove = i;

                    return beta;
                }
            }
        }
        if (bestmove != (-1))
        {
            // **_socket = alpha;
            // *_socket = 0;

            AddTo_history_table(history_table, heuristic_list[bestmove].a, heuristic_list[bestmove].b, depth);
            return alpha;
        }
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
    AlphaBeta(LEVEL, colornow, -INF, INF,Getzob(),Getzob2());
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
