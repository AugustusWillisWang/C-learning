//对矩阵的各点进行查找
//Based on algo_point.
//ALGO_MINMAX
#define ALGO_FINAL 3
#define EDGE 3
#define LEVEL 5

#include "zobrist.h"

//这里的权值是随便赋的
#define W1_2 2
#define W2_2 5
#define W3_2 10
#define W4_2 20

#define W1_1 1
#define W2_1 3
#define W3_1 5
#define W4_1 10

#define W5 10000000000.0

//Basic calc:

//Let + be black weight, and - be white weight;
// int ShowWeightArray_Algo3();
// int Show_ValidArray_Algo3();

//对矩阵的整体查找
// int GenValidPosition_Algo3();    //Calc only near the exist point.
double WeightContribute_Algo3(); //Gen weight for a single line in _Testline_[9]
double PointGenWeightForShapeNow_Algo3();
// double PointGenWeightAt_Algo3(int a, int b); //Get the weight change if making move at a,b.
// int PointGenWeightMartix_Algo3();

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

    int a_choosed = 0, b_choosed = 0;
    Minmax(colornow, LEVEL, NINF, INF);
    a_choosed = aget;
    b_choosed = bget;
    CK(a_choosed);
    CK(b_choosed);
    // ShowWeightArray_Algo3();
    // BP;
    *ap = a_choosed;
    *bp = b_choosed;

    // ClearWeightMartix_Algo3();

    return 0;
}
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

int ShowWeightArray_Algo3()
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%.0lf ", weight[a][b]);
        }
        puts("");
    }
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

#include"simpletest.h"

int ClearWeightMartix_Algo3()
{
    memset(weight, 0, sizeof(double) * BOUNDRY * BOUNDRY);
}

//Minmax:

// int _JudgeWin();

double MaxWeight(int *weight[])
{
    double max = -100000000000.0;
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
double MinWeight(int *weight[])
{
    // double max = -100000000000.0;
    double min = 100000000000.0;
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
                _ValidPosition[BoundLim(a + 1)][BoundLim(b + 1)] = 1;
                _ValidPosition[BoundLim(a + 1)][BoundLim(b)] = 1;
                _ValidPosition[BoundLim(a + 1)][BoundLim(b - 1)] = 1;
                _ValidPosition[BoundLim(a)][BoundLim(b + 1)] = 1;
                _ValidPosition[BoundLim(a)][BoundLim(b)] = 1;
                _ValidPosition[BoundLim(a)][BoundLim(b - 1)] = 1;
                _ValidPosition[BoundLim(a - 1)][BoundLim(b + 1)] = 1;
                _ValidPosition[BoundLim(a - 1)][BoundLim(b)] = 1;
                _ValidPosition[BoundLim(a - 1)][BoundLim(b - 1)] = 1;
            }
        }
    }
}

double MinmaxOrigin(int color, int step, double max, double min);
int NEqualDouble(double a, double b);

int _dbg_(double _weight, int level)
{
    static int cnt = 0;
    if (LEVEL == level)
    {
        printf("%lf ", _weight);
        cnt++;
        if (BOUNDRY == cnt)
        {
            cnt = 0;
            puts("");
        }
    }
}

double Minmax(int color, int step, double max, double min)
{
    int temp;
    int _aget, _bget;
    if (temp = _JudgeWin())
    {
        if (temp == BLACK)
            return W5;
        else
            return W5 * (-1);
    }
    if (step == 0)
    {
        // int _weight[BOUNDRY][BOUNDRY];

        return PointGenWeightForShapeNow_Algo3();
        // PointGenWeightMartix_Algo3(_weight);
        // if (color == BLACK)
        // return MaxWeight(_weight);
        // if (color == WHITE)
        // return MinWeight(_weight);
    }
    else
    {
        // int _weight[BOUNDRY][BOUNDRY];
        double _weight;
        int _ValidPosition[BOUNDRY][BOUNDRY];
        memset(_ValidPosition, 0, sizeof(int) * BOUNDRY * BOUNDRY);
        // memset(_weight, 0, sizeof(int) * BOUNDRY * BOUNDRY);

        GetAroundPosition(_ValidPosition);
        if (_usesimpletest)
            SimpleSituationCheck_Algo3(_ValidPosition);
        // double maxget = max;
        // double minget = min;
        for (int a = 0; a < BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                if (_ValidPosition[a][b] && board[a][b] == 0)
                {
                    // double *_zobnewweight = 0;
                    // double **_zobnewweightp = &_zobnewweight;
                    // double ___soc = 0;
                    double *__soc = 0;
                    double **_socket = &__soc;
                    if (color == BLACK)
                    {
                        board[a][b] = color;
                        _weight = FindInHashTable(Getzob(), step, _socket);
                        if (*_socket != 0)
                        {

                            // _weight = newweight()
                            _weight = Minmax(Inverse(color), step - 1, max, min);
                            // _zobnewweight = 0;
                            **_socket = _weight;
                            *_socket = 0;
                        }
                        board[a][b] = 0;
                        // _dbg_(_weight, step);
                        // printf("%lf ;\n", _weight);

                        if (_weight > max)
                        {
                            max = _weight;
                            _aget = a;
                            _bget = b;
                        }
                        if (max >= min)
                            goto cut;
                    }

                    if (color == WHITE)
                    {
                        board[a][b] = color;
                        _weight = FindInHashTable(Getzob(), step, _socket);
                        if (*_socket != 0)
                        {

                            // _weight = newweight()
                            _weight = Minmax(Inverse(color), step - 1, max, min);
                            // _zobnewweight = 0;
                            **_socket = _weight;
                            *_socket = 0;
                        }

                        board[a][b] = 0;
                        // _dbg_(_weight, step);

                        if (_weight < min)
                        {
                            min = _weight;
                            _aget = a;
                            _bget = b;
                            if (max >= min)
                                goto cut;
                        }
                    }
                }
            }
        }
    }

    aget = _aget;
    bget = _bget;
    if (color == BLACK)
        return max;
    // return MaxWeight(_weight);
    if (color == WHITE)
        return min;
cut:
    aget = _aget;
    bget = _bget;
    if (color == BLACK)
        return min;
    // return MaxWeight(_weight);
    if (color == WHITE)
        return max;
    // return MinWeight(_weight);
}

double MinmaxOrigin(int color, int step, double max, double min)
{
    int temp;
    int _aget, _bget;
    if (temp = _JudgeWin())
    {
        if (temp == BLACK)
            return W5;
        else
            return W5 * (-1);
    }
    if (step == 0)
    {
        // int _weight[BOUNDRY][BOUNDRY];

        return PointGenWeightForShapeNow_Algo3();
        // PointGenWeightMartix_Algo3(_weight);
        // if (color == BLACK)
        // return MaxWeight(_weight);
        // if (color == WHITE)
        // return MinWeight(_weight);
    }
    else
    {
        // int _weight[BOUNDRY][BOUNDRY];
        double _weight;
        int _ValidPosition[BOUNDRY][BOUNDRY];
        memset(_ValidPosition, 0, sizeof(int) * BOUNDRY * BOUNDRY);
        // memset(_weight, 0, sizeof(int) * BOUNDRY * BOUNDRY);

        GetAroundPosition(_ValidPosition);
        SimpleSituationCheck_Algo3(_ValidPosition);
        // double maxget = max;
        // double minget = min;
        for (int a = 0; a < BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                if (_ValidPosition[a][b] && board[a][b] == 0)
                {
                    if (color == BLACK)
                    {
                        board[a][b] = color;
                        _weight = Minmax(Inverse(color), step - 1, max, min);
                        board[a][b] = 0;
                        if (_weight > min)
                        {
                            min = _weight;
                            _aget = a;
                            _bget = b;
                        }
                        if (min > max)
                            goto cut;
                    }

                    if (color == WHITE)
                    {
                        board[a][b] = color;
                        _weight = Minmax(Inverse(color), step - 1, max, min);
                        board[a][b] = 0;
                        if (_weight < max)
                        {
                            max = _weight;
                            _aget = a;
                            _bget = b;
                            if (max < min)
                                goto cut;
                        }
                    }
                }
            }
        }
    }
cut:
    aget = _aget;
    bget = _bget;
    if (color == BLACK)
        return min;
    // return MaxWeight(_weight);
    if (color == WHITE)
        return max;
    // return MinWeight(_weight);
}

int NEqualDouble(double a, double b)
{
    if (a < b + 1 && a > b - 1)
        return 0;
    return 1;
}