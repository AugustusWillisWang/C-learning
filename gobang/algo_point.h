//对矩阵的各点进行查找

#define ALGO_POINT 2
#define EDGE 3

//这里的权值是随便赋的
#define WEIGHT_1_2SIDE 20.0
#define WEIGHT_2_2SIDE (500.0 / 2)
#define WEIGHT_3_2SIDE (100000.0 / 3)
#define WEIGHT_4_2SIDE (200000.0 / 4)

#define WEIGHT_1_1SIDE 10.0
#define WEIGHT_2_1SIDE (100.0 / 2)
#define WEIGHT_3_1SIDE (50000.0 / 3)
#define WEIGHT_4_1SIDE (150000.0 / 4)

#define WEIGHT_5_WIN 10000000000.0

//Let + be black weight, and - be white weight;
int ShowWeightArray_Algo2();
int Show_ValidArray_Algo2();

//对矩阵的整体查找
int GenValidPosition_Algo2();    //Calc only near the exist point.
double WeightContribute_Algo2(); //Gen weight for a single line in _Testline[9]
double PointGenWeightForShapeNow_Algo2();
double PointGenWeightAt_Algo2(int a, int b); //Get the weight change if making move at a,b.
int PointGenWeightMartix_Algo2();

int ClearWeightMartix();
//--------------------------------------------

int SimpleSituationCheck(); //Check 4-1 4-2 3-2 in order. If such situation exists, constrain avaliable position to such areas.

int GenNaiveConstrain_Algo2();
int PointTestNaiveSituationForShapeNow_Algo2();

int _algo2_havenot_clear_array = 1;

//------------------------------------------

int Inverse(int color)
{
    switch (color)
    {
    case WHITE:
        return BLACK;
    case BLACK:
        return WHITE;
    default:
        return 0;
    }
}

int _ValidPositionForPointAlgo[BOUNDRY][BOUNDRY];
int _TestedPositionForPointAlgo[BOUNDRY][BOUNDRY];
int _Testline[9]; //Get 9 elements out to check the weight.

double _weightnow;

//  int JudgeWinPlus();
//  int _LinearWeightCnter(int a, int b, int mode); //if mode==CLEAR, set cnt,max,color=0

int AlgoPoint(int *ap, int *bp) //Write the position choosed into int* ap,int* bp;
{
    if (fstmove && colornow == BLACK)
    {
        *ap = BOUNDRY / 2;
        *bp = BOUNDRY / 2;
        fstmove = 0;
        return 0;
    }

    PointGenWeightMartix_Algo2();
    // SHOWALL(weight, "double");

    int a_choosed = 0, b_choosed = 0;
    if (colornow == BLACK)
    {
        double max_weight_get = -100000000000000.0;
        for (int a = 0; a < BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                if (weight[a][b] > max_weight_get)
                {
                    max_weight_get = weight[a][b];
                    a_choosed = a;
                    b_choosed = b;
                }
            }
        }
    }
    else
    {
        double min_weight_get = 100000000000000.0;
        for (int a = 0; a < BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                if (weight[a][b] < min_weight_get)
                {
                    min_weight_get = weight[a][b];
                    a_choosed = a;
                    b_choosed = b;
                }
            }
        }
    }
    CK(a_choosed);
    CK(b_choosed);
    ShowWeightArray_Algo2();
    BP;
    *ap = a_choosed;
    *bp = b_choosed;

    ClearWeightMartix();

    return 0;
}
//colornow is known;

double WeightContribute_Algo2()
//Deal with the 1-d 9 element array, return the weight generated.
//At the same time, mark the point tested.(Obsoleted)
{
    //  int _Testline[9];//Get 9 elements out to check the weight.
    int leftblocked = 0;
    int rightblocked = 0;
    int cnt = 0;
    int position = 4; //The middle of the 9 positions.
    //Get the weight of this position.
    if (_Testline[position] == 0)
        return 0;
    cnt++;
    int colorinmiddle = _Testline[position];
    while (_Testline[--position] == colorinmiddle) //Highlight!
    {
        cnt++;
        if (0 == position)
            break;
    }
    switch (_Testline[position])
    {

    case 0:
        leftblocked = 0;
        break;

    default:
        leftblocked = 1;
        break;
    }
    position = 4;
    while (_Testline[++position] == colorinmiddle) //Highlight!
    {
        cnt++;
        if (8 == position)
            break;
    }
    switch (_Testline[position])
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
    while (position >= 0 && _Testline[--position] != Inverse(colorinmiddle) && _Testline[position] != EDGE)
    {
        linkmax++;
    }
    position = 4;
    while (position < 9 && _Testline[++position] != Inverse(colorinmiddle) && _Testline[position] != EDGE)
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
            return (colornow == BLACK ? 1 : -1) * WEIGHT_1_2SIDE;
        case 1:
            return (colornow == BLACK ? 1 : -1) * WEIGHT_1_1SIDE;
        case 2:
            return (colornow == BLACK ? 1 : -1) * 0;
        }
    case 2:
        switch (leftblocked + rightblocked)
        {
        case 0:
            return (colornow == BLACK ? 1 : -1) * WEIGHT_2_2SIDE;
        case 1:
            return (colornow == BLACK ? 1 : -1) * WEIGHT_2_1SIDE;
        case 2:
            return (colornow == BLACK ? 1 : -1) * 0;
        }
    case 3:
        switch (leftblocked + rightblocked)
        {
        case 0:
            return (colornow == BLACK ? 1 : -1) * WEIGHT_3_2SIDE;
        case 1:
            return (colornow == BLACK ? 1 : -1) * WEIGHT_3_1SIDE;
        case 2:
            return (colornow == BLACK ? 1 : -1) * 0;
        }
    case 4:
        switch (leftblocked + rightblocked)
        {
        case 0:
            return (colornow == BLACK ? 1 : -1) * WEIGHT_4_2SIDE;
        case 1:
            return (colornow == BLACK ? 1 : -1) * WEIGHT_4_1SIDE;
        case 2:
            return (colornow == BLACK ? 1 : -1) * 0;
        }
    case 5:
        return (colornow == BLACK ? 1 : -1) * WEIGHT_5_WIN;
    }
    return 0;
}

double PointGenWeightForShapeNow_Algo2()
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
                    _Testline[i] = board[aget][bget];
                }
                else
                {
                    _Testline[i] = EDGE;
                }
            }

            weight_for_shape_now += WeightContribute_Algo2();
            for (int bget = b - 4, aget = a, i = 0; bget <= b + 4; bget++, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline[i] = board[aget][bget];
                }
                else
                {
                    _Testline[i] = EDGE;
                }
            }
            weight_for_shape_now += WeightContribute_Algo2();

            for (int aget = a - 4, bget = b - 4, i = 0; aget <= a + 4; aget++, bget++, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline[i] = board[aget][bget];
                }
                else
                {
                    _Testline[i] = EDGE;
                }
            }
            weight_for_shape_now += WeightContribute_Algo2();

            for (int aget = a - 4, bget = b + 4, i = 0; aget <= a + 4; aget++, bget--, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline[i] = board[aget][bget];
                }
                else
                {
                    _Testline[i] = EDGE;
                }
            }
            weight_for_shape_now += WeightContribute_Algo2();
        }
    }
    return weight_for_shape_now;
}

double PointGenWeightAt_Algo2(int a, int b)
{
    if (board[a][b]) //该位置无法落子
    {
        return 0;
    }
    board[a][b] = colornow;
    double change = PointGenWeightForShapeNow_Algo2();
    // printf("change:%lf\n", change);
    board[a][b] = 0;
    return change;
}

int PointGenWeightMartix_Algo2()
{

    //落子在有棋子的区域附近, 以提高效果并加快速度
    int BoundLim(int a)
    {
        if (a < 0)
        {
            return 0;
        }
        else if (a >= BOUNDRY)
        {
            return BOUNDRY;
        }
        else
        {
            return a;
        }
    }
    memset(_ValidPositionForPointAlgo, 0, sizeof(int) * BOUNDRY * BOUNDRY);
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b])
            {
                _ValidPositionForPointAlgo[BoundLim(a + 1)][BoundLim(b + 1)] = 1;
                _ValidPositionForPointAlgo[BoundLim(a + 1)][BoundLim(b)] = 1;
                _ValidPositionForPointAlgo[BoundLim(a + 1)][BoundLim(b - 1)] = 1;
                _ValidPositionForPointAlgo[BoundLim(a)][BoundLim(b + 1)] = 1;
                _ValidPositionForPointAlgo[BoundLim(a)][BoundLim(b)] = 1;
                _ValidPositionForPointAlgo[BoundLim(a)][BoundLim(b - 1)] = 1;
                _ValidPositionForPointAlgo[BoundLim(a - 1)][BoundLim(b + 1)] = 1;
                _ValidPositionForPointAlgo[BoundLim(a - 1)][BoundLim(b)] = 1;
                _ValidPositionForPointAlgo[BoundLim(a - 1)][BoundLim(b - 1)] = 1;
            }
        }
    }

    // makemovenow:

    SimpleSituationCheck();
    //在可行的位置产生权重
    // _weightnow = PointGenWeightForShapeNow_Algo2();

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (_ValidPositionForPointAlgo[a][b])
                weight[a][b] = PointGenWeightAt_Algo2(a, b);
            // CK(weight[a][b]);
        }
    }
}

int ShowWeightArray_Algo2()
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

int Show_ValidArray_Algo2()
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%d ", _ValidPositionForPointAlgo[a][b]);
        }
        puts("");
    }
}

int SimpleSituationCheck() //Check 4-1 4-2 3-2 in order. If such situation exists, constrain avaliable position to such areas.
{
    // Show_ValidArray_Algo2();
    // BP;

    PointTestNaiveSituationForShapeNow_Algo2(3, 2);
    // Show_ValidArray_Algo2();
    // BP;

    PointTestNaiveSituationForShapeNow_Algo2(4, 2);
    // Show_ValidArray_Algo2();
    // BP;

    PointTestNaiveSituationForShapeNow_Algo2(4, 1);
    // Show_ValidArray_Algo2();
    // BP;
}

int PointTestNaiveSituationForShapeNow_Algo2(int cntneeded, int spaceneeded)
{
    _algo2_havenot_clear_array = 1;

    //line
    int incolor = 0;
    int continuecnt = 0;
    int start = -1;
    int end = -1;

    int startposition[2];
    int endposition[2];

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b] == incolor)
            {
                continuecnt++;
            }
            else
            {
                //deal
                end = board[a][b];
                endposition[0] = a;
                endposition[1] = b;
                GenNaiveConstrain_Algo2(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);
                incolor = board[a][b];
                continuecnt = 1;
                if ((a) >= 0 && (a) < BOUNDRY && (b - 1) >= 0 && (b - 1) < BOUNDRY)
                {
                    start = board[a][b - 1];
                    startposition[0] = a;
                    startposition[1] = b - 1;
                }
                else
                {
                    start = EDGE;
                    startposition[0] = -1;
                    startposition[1] = -1;
                }
            }
        }
        end = EDGE;
        //deal;
        GenNaiveConstrain_Algo2(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);

        incolor = 0;
        continuecnt = 0;
    }

    //col
    incolor = 0;
    continuecnt = 0;
    start = -1;
    end = -1;
    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            if (board[a][b] == incolor)
            {
                continuecnt++;
            }
            else
            {

                //deal

                end = board[a][b];
                endposition[0] = a;
                endposition[1] = b;
                GenNaiveConstrain_Algo2(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);
                continuecnt = 1;
                incolor = board[a][b];
                if ((a - 1) >= 0 && (a - 1) < BOUNDRY && (b) >= 0 && (b) < BOUNDRY)
                {
                    start = board[a - 1][b];
                    startposition[0] = a - 1;
                    startposition[1] = b;
                }
                else
                {
                    start = EDGE;
                    startposition[0] = -1;
                    startposition[1] = -1;
                }
            }
        }
        end = EDGE;
        //deal;
        GenNaiveConstrain_Algo2(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);

        incolor = 0;
        continuecnt = 0;
    }

    //dig2
    incolor = 0;
    continuecnt = 0;
    start = -1;
    end = -1;
    for (int aplusb = 0; aplusb < 2 * (BOUNDRY - 1); aplusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = aplusb - a;
            if (b >= 0 && b < BOUNDRY)
            {
                if (board[a][b] == incolor)
                {
                    continuecnt++;
                }
                else
                {
                    //deal

                    end = board[a][b];
                    endposition[0] = a;
                    endposition[1] = b;
                    GenNaiveConstrain_Algo2(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);
                    continuecnt = 1;
                    incolor = board[a][b];
                    if ((a - 1) >= 0 && (a - 1) < BOUNDRY && (b + 1) >= 0 && (b + 1) < BOUNDRY)
                    {
                        start = board[a - 1][b + 1];
                        startposition[0] = a - 1;
                        startposition[1] = b + 1;
                    }
                    else
                    {
                        start = EDGE;
                        startposition[0] = -1;
                        startposition[1] = -1;
                    }
                }
            }
        }
            end = EDGE;
            //deal;
            GenNaiveConstrain_Algo2(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);

            incolor = 0;
            continuecnt = 0;
    }

    //dig1
    incolor = 0;
    continuecnt = 0;
    start = -1;
    end = -1;
    for (int aminusb = -(BOUNDRY - 1); aminusb < (BOUNDRY - 1); aminusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = a - aminusb;
            if (b >= 0 && b < BOUNDRY)
            {
                if (board[a][b] == incolor)
                {
                    continuecnt++;
                }
                else
                {
                    //deal
                    end = board[a][b];
                    endposition[0] = a;
                    endposition[1] = b;
                    GenNaiveConstrain_Algo2(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);
                    continuecnt = 1;
                    incolor = board[a][b];
                    if ((a - 1) >= 0 && (a - 1) < BOUNDRY && (b - 1) >= 0 && (b - 1) < BOUNDRY)
                    {
                        start = board[a - 1][b - 1];
                        startposition[0] = a - 1;
                        startposition[1] = b - 1;
                    }
                    else
                    {
                        start = EDGE;
                        startposition[0] = -1;
                        startposition[1] = -1;
                    }
                }
            }
        }
            end = EDGE;
            //deal;
            GenNaiveConstrain_Algo2(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);

            incolor = 0;
            continuecnt = 0;
    }
    return 0;
}

int GenNaiveConstrain_Algo2(int cntneeded, int spaceneeded, int start, int end, int continuecnt, int *startposition, int *endposition, int incolor)
{
    if (incolor == 0)
        return 0;
    // startposition[0]
    // {
    //     CK(start), CK(end), CK(continuecnt), CK(incolor), CK(startposition[0]);
    //     CK(startposition[1]);
    //     CK(endposition[0]);
    //     CK(endposition[1]);
    //     printf("\n");
    //     puts("---");
    // }
    int space = (start == 0) + (end == 0);
    if (continuecnt == cntneeded && space == spaceneeded)
    {
        if (_algo2_havenot_clear_array)
        {
            _algo2_havenot_clear_array = 0;
            memset(_ValidPositionForPointAlgo, 0, sizeof(int) * BOUNDRY * BOUNDRY);
        }
        if (startposition[0] != -1 && startposition[1] != -1)
            _ValidPositionForPointAlgo[startposition[0]][startposition[1]] = 1;
        if (endposition[0] != -1 && endposition[1] != -1)
            _ValidPositionForPointAlgo[endposition[0]][endposition[1]] = 1;
        BP;
    }
}

int ClearWeightMartix()
{
    memset(weight, 0, sizeof(double) * BOUNDRY * BOUNDRY);
}

// int GenNaiveConstrain_Algo2(int a,int b,int lima,int lim b,)
// //Deal with the 1-d 9 element array, return the weight generated.
// //At the same time, mark the point tested.(Obsoleted)
// {
//     //  int _Testline[9];//Get 9 elements out to check the weight.
//     int leftblocked = 0;
//     int rightblocked = 0;
//     int cnt = 0;
//     int position = 4; //The middle of the 9 positions.
//     //Get the weight of this position.
//     if (_Testline[position] == 0)
//         return 0;
//     cnt++;
//     int colorinmiddle = _Testline[position];
//     while (_Testline[--position] == colorinmiddle) //Highlight!
//     {
//         cnt++;
//         if (0 == position)
//             break;
//     }
//     switch (_Testline[position])
//     {

//     case 0:
//         leftblocked = 0;
//         break;

//     default:
//         leftblocked = 1;
//         break;
//     }
//     position = 4;
//     while ( _Testline[++position] == colorinmiddle) //Highlight!
//         {cnt++;
//         if(8==position)
//             break;
//         }
//     switch (_Testline[position])
//     {
//     case 0:
//         rightblocked = 0;
//         break;

//     default:
//         rightblocked = 1;
//         break;
//     }

//     //If 5 link is impossible to achieve, then return 0;
//     int linkmax = 1;
//     position = 4;
//     while (position >= 0 && _Testline[--position] != Inverse(colorinmiddle) && _Testline[position] != EDGE)
//     {
//         linkmax++;
//     }
//     position = 4;
//     while (position < 9 && _Testline[++position] != Inverse(colorinmiddle) && _Testline[position] != EDGE)
//     {
//         linkmax++;
//     }
//     if (linkmax < 5)
//         return 0;

//     //Gen constrain area.

//     if(cnt==a&&(2-leftblocked-rightblocked)==b)
//     {
//         if(_algo2_havenot_clear_array)
//         {
//             _algo2_havenot_clear_array = 0;
//             memset(_ValidPositionForPointAlgo, 0, sizeof(int) * BOUNDRY * BOUNDRY);
//         }

//     }
// return 0;
// }

// int PointTestNaiveSituationForShapeNow_Algo2(int a,int b)
// {
//     int _algo2_havenot_clear_array = 1;
//     // double weight_for_shape_now = 0.0;
//     for (int a = 0; a < BOUNDRY; a++)
//     {
//         for (int b = 0; b < BOUNDRY; b++)
//         {
//             for (int aget = a - 4, i = 0, bget = b; aget <= a + 4; aget++, i++)
//             {
//                 if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
//                 {
//                     _Testline[i] = board[aget][bget];

//                 }
//                 else
//                 {
//                     _Testline[i] = EDGE;

//                 }
//             }

//         GenNaiveConstrain_Algo2(a,b);
//             for (int bget = b - 4, aget = a, i = 0; bget <= b + 4; bget++, i++)
//             {
//                 if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
//                 {
//                     _Testline[i] = board[aget][bget];

//                 }
//                 else
//                 {
//                     _Testline[i] = EDGE;

//                 }
//             }
// GenNaiveConstrain_Algo2(a,b);

//             for (int aget = a - 4, bget = b - 4, i = 0; aget <= a + 4; aget++, bget++, i++)
//             {
//                 if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
//                 {
//                     _Testline[i] = board[aget][bget];

//                 }
//                 else
//                 {
//                     _Testline[i] = EDGE;

//                 }
//             }
// GenNaiveConstrain_Algo2(a,b);

//             for (int aget = a - 4, bget = b + 4, i = 0; aget <= a + 4; aget++, bget--, i++)
//             {
//                 if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
//                 {
//                     _Testline[i] = board[aget][bget];

//                 }
//                 else
//                 {
//                     _Testline[i] = EDGE;

//                 }
//             }
// GenNaiveConstrain_Algo2(a,b);
//         }
//     }
//     return 0;
// }
