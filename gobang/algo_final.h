//对矩阵的各点进行查找

#define ALGO_FINAL 3

#ifndef EDGE
#define EDGE 3
#endif

//这里的权值是随便赋的
#define WEIGHT_1_LINK_2 20.0
#define WEIGHT_2_LINK_2 500.0
#define WEIGHT_3_LINK_2 100000.0
#define WEIGHT_4_LINK_2 200000.0

#define WEIGHT_1_LINK_1 1.0
#define WEIGHT_2_LINK_1 100.0
#define WEIGHT_3_LINK_1 50000.0
#define WEIGHT_4_LINK_1 150000.0

#define WEIGHT_1_SPACE_1 1.0 //useless
#define WEIGHT_2_SPACE_1 30.0
#define WEIGHT_3_SPACE_1 30000.0
#define WEIGHT_4_SPACE_1 130000.0

#define WEIGHT_1_SPACE_2 1.0 //useless
#define WEIGHT_2_SPACE_2 100.0
#define WEIGHT_3_SPACE_2 40000.0
#define WEIGHT_4_SPACE_2 140000.0

#define WEIGHT_5 10000000000.0

//Let + be black weight, and - be white weight;
int ShowWeightArray_Algo3();
int Show_ValidArray_Algo3();

//Main functions of the algo.
int GenValidPosition_Algo3(); //Calc only near the exist point.
int GenWeightMartix_Algo3();
//These functions are used to gen the weight.
double GenWeightAt_Algo3(int a, int b); //Get the weight (change?) if making move at a,b.
double GenWeightForShapeNow_Algo3();
int boardline[4][2 * BOUNDRY][BOUNDRY];
int Generate4Martixs();                                                           //Convert the board in to 4 different martixs.
double WeightContribute_Algo3(int *targetline);                                   //Calc a single line's contribute.
double GenWeightFromMarco(int incolor, int cnt, int space, int start0, int end0); //A pattern's contribute;

int Show4Martixs();
//-----------------------------------------

int ClearWeightMartix_Algo3();
//--------------------------------------------
//These functions are used to make sure the algo won't make stupid move in trival situations.
int SimpleSituationCheck_Algo3(); //Check 4-1 4-2 3-2 in order. If such situation exists, constrain avaliable position to such areas.

int GenNaiveConstrain_Algo3();
int TestNaiveSituationForShapeNow_Algo3();

int _algo3_havenot_clear_array = 1;

//-------------------------------------------

int Inverse_Algo3(int color)
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

double _weightnow = 0;

//  int JudgeWinPlus();
//  int _LinearWeightCnter(int a, int b, int mode); //if mode==CLEAR, set cnt,max,color=0

int AlgoFinal(int *ap, int *bp) //Write the position choosed into int* ap,int* bp;
{
    if (fstmove && colornow == BLACK)
    {
        *ap = BOUNDRY / 2;
        *bp = BOUNDRY / 2;
        fstmove = 0;
        return 0;
    }

    GenWeightMartix_Algo3();
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
    ShowWeightArray_Algo3();
    Show_ValidArray_Algo3();
    BP;
    *ap = a_choosed;
    *bp = b_choosed;

    ClearWeightMartix_Algo3();

    return 0;
}
//colornow is known;

double WeightContribute_Algo3(int *targetline)
//Deal with a_choosed single line in the 4 martix gened.
{
    double weightinline = 0;
    int linewithedge[BOUNDRY + 2];
    linewithedge[0] = EDGE;
    linewithedge[BOUNDRY + 1] = EDGE;
    memcpy(linewithedge + 1, targetline, sizeof(int) * BOUNDRY);

    int incolor = 0;
    int space = 0;
    int start = 0;
    int end = 0;
    int cnt = 0;
    for (int position = 1; position < BOUNDRY + 1; position++)
    {
        if (!incolor)
        {
            if (linewithedge[position] == BLACK || linewithedge[position] == WHITE)
            {
                incolor = linewithedge[position];
                cnt++;
                start = linewithedge[position - 1];
            }
            continue;
        }
        if (incolor)
        {
            if (linewithedge[position] == 0)
            {
                space++;
                if (space == 2)
                {
                    if(linewithedge[position-1]==0){
                        // end = 0;
                        space = 0;
                    }
                    end = 0;
                }else{
                    continue;
                }
            }
            if (linewithedge[position] == EDGE)
            {
                end = EDGE;
            }
            if (linewithedge[position] == Inverse(incolor))
            {
                end = Inverse(incolor);
            }
            if (linewithedge[position] == incolor)
            {
                cnt++;
                continue;
            }
            weightinline += GenWeightFromMarco(incolor, cnt, space, start == 0, end == 0);
            if(cnt==2){
                CK(incolor), CK(cnt), CK(space), CK(start), CK(end);
                puts("----------");
            }
            incolor = 0;
            space = 0;
            start = 0;
            end = 0;
            cnt = 0;
        }
    }
    weightinline += GenWeightFromMarco(incolor, cnt, space, start == 0, end == 0);
    if(cnt==2){
                CK(incolor), CK(cnt), CK(space), CK(start), CK(end);
                puts("------------");
    }
    // incolor = 0;
    // space = 0;
    // start = 0;
    // end = 0;
    // cnt = 0;
    // CK((int)weightinline);
    return weightinline;
}

double GenWeightForShapeNow_Algo3()
{
    double _weight = 0.0;
    Generate4Martixs();
    // int boardline[4][2 * BOUNDRY][BOUNDRY];

    for (int a = 0; a < 4; a++)
    {
        for (int b = 0; b < 2 * BOUNDRY; b++)
        {
            _weight += WeightContribute_Algo3(boardline[a][b]);
        }
    }
    return _weight;
}

double GenWeightAt_Algo3(int a, int b)
{
    if (board[a][b]) //该位置无法落子
    {
        return 0;
    }
    board[a][b] = colornow;
    double change = GenWeightForShapeNow_Algo3();
    // printf("change:%lf\n", change);
    board[a][b] = 0;
    return change;
}

int GenWeightMartix_Algo3()
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
            return BOUNDRY-1;
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
                for (int tempa = a - 2; tempa <= a + 2; tempa++)
                {
                    for (int tempb = b - 2; tempb <= b + 2; tempb++)
                    {
                        _ValidPositionForPointAlgo[BoundLim(tempa)][BoundLim(tempb)] = 1;
                    }
                }
            }
        }
    }

    // makemovenow:

    SimpleSituationCheck_Algo3();
    //在可行的位置产生权重
    // _weightnow = GenWeightForShapeNow_Algo3();

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (_ValidPositionForPointAlgo[a][b])
                weight[a][b] = GenWeightAt_Algo3(a, b);
            // CK(weight[a][b]);
        }
    }
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

int Show_ValidArray_Algo3()
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

int SimpleSituationCheck_Algo3() //Check 4-1 4-2 3-2 in order. If such situation exists, constrain avaliable position to such areas.
{
    // Show_ValidArray_Algo3();
    // BP;

    TestNaiveSituationForShapeNow_Algo3(3, 2);
    // Show_ValidArray_Algo3();
    // BP;

    TestNaiveSituationForShapeNow_Algo3(4, 2);
    // Show_ValidArray_Algo3();
    // BP;

    TestNaiveSituationForShapeNow_Algo3(4, 1);
    // Show_ValidArray_Algo3();
    // BP;
}

int TestNaiveSituationForShapeNow_Algo3(int cntneeded, int spaceneeded)
{
    _algo3_havenot_clear_array = 1;

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
                GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);
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
        GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);

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
                GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);
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
        GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);

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
                    GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);
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
        GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);

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
                    GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);
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
        GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor);

        incolor = 0;
        continuecnt = 0;
    }
    return 0;
}

int GenNaiveConstrain_Algo3(int cntneeded, int spaceneeded, int start, int end, int continuecnt, int *startposition, int *endposition, int incolor)
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
        if (_algo3_havenot_clear_array)
        {
            _algo3_havenot_clear_array = 0;
            memset(_ValidPositionForPointAlgo, 0, sizeof(int) * BOUNDRY * BOUNDRY);
        }
        if (startposition[0] != -1 && startposition[1] != -1)
            _ValidPositionForPointAlgo[startposition[0]][startposition[1]] = 1;
        if (endposition[0] != -1 && endposition[1] != -1)
            _ValidPositionForPointAlgo[endposition[0]][endposition[1]] = 1;
        BP;
    }
}

int ClearWeightMartix_Algo3()
{
    memset(weight, 0, sizeof(double) * BOUNDRY * BOUNDRY);
}

int Generate4Martixs()
{
    //Let the whole martix be 3.
    for (int i = 0; i < 4; i++)
    {
        for (int a = 0; a < 2 * BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                boardline[i][a][b] = 3;
            }
        }
    }

    // boardline[4][2 * BOUNDRY][BOUNDRY]
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            boardline[0][a][b] = board[a][b];
        }
    }

    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            boardline[1][b][a] = board[a][b];
        }
    }

    for (int aplusb = 0; aplusb < 2 * (BOUNDRY - 1); aplusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = aplusb - a;
            if (b >= 0 && b < BOUNDRY)
            {
                boardline[2][aplusb][b] = board[a][b];
            }
        }
    }

    for (int aminusb = -(BOUNDRY - 1); aminusb < (BOUNDRY - 1); aminusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = a - aminusb;
            if (b >= 0 && b < BOUNDRY)
            {
                boardline[3][aminusb + BOUNDRY - 1][b] = board[a][b];
            }
        }
    }
    // Show4Martixs();
}

int Show4Martixs()
{
    // boardline[4][2 * BOUNDRY][BOUNDRY];
    for (int i = 0; i < 4; i++)
    {
        for (int a = 0; a < 2 * BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                printf("%d ", boardline[i][a][b]);
            }
            puts("");
        }
        puts("");
    }
}

double GenWeightFromMarco(int incolor, int cnt, int space, int start0, int end0) //A pattern's contribute;
{
    double result = (incolor == BLACK ? 1 : -1);
    int edge = start0 + end0;
    switch (edge)
    {
    case 0:
        switch (space)
        {
        case 0:
            switch (cnt)
            {
            case 0:
            case 1:
                return 0;
            case 2:
                return 0;

            case 3:
                return 0;

            case 4:
                return 0;

            case 5:
                return WEIGHT_5 * result;

            case 6:
                return WEIGHT_5 * result;

            case 7:
                return WEIGHT_5 * result;

            case 8:
                return WEIGHT_5 * result;
            default:
                return 0;
            }
        case 1:
            switch (cnt)
            {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                return 0;
            default:
                return 0;
            }
        }
    case 1:
        switch (space)
        {
        case 0:
            switch (cnt)
            {
            case 0:
                return 0;
            case 1:
                return WEIGHT_1_LINK_1 * result;
            case 2:
                return WEIGHT_2_LINK_1 * result;

            case 3:
                return WEIGHT_3_LINK_1 * result;

            case 4:
                return WEIGHT_4_LINK_1 * result;

            case 5:
            case 6:
            case 7:
            case 8:
                return WEIGHT_5;
            default:
                return 0;
            }
        case 1:
            switch (cnt)
            {
            case 0:
                return 0;
            case 1:
                return WEIGHT_1_SPACE_1 * result;

            case 2:
                return WEIGHT_2_SPACE_1 * result;

            case 3:
                return WEIGHT_3_SPACE_1 * result;

            case 4:
                return WEIGHT_4_SPACE_1 * result;

            case 5:
            case 6:
            case 7:
            case 8:
                return WEIGHT_5 * result;
            default:
                return 0;
            }
        }
    case 2:
        switch (space)
        {
        case 0:
            switch (cnt)
            {
            case 0:
                return 0;
            case 1:
                return WEIGHT_1_LINK_2 * result;
            case 2:
                return WEIGHT_2_LINK_2 * result;

            case 3:
                return WEIGHT_3_LINK_2 * result;

            case 4:
                return WEIGHT_4_LINK_2 * result;

            case 5:
            case 6:
            case 7:
            case 8:
                return WEIGHT_5 * result;
            default:
                return 0;
            }
        case 1:
            switch (cnt)
            {
            case 0:
                return 0;
            case 1:
                return WEIGHT_1_SPACE_2 * result;

            case 2:
                return WEIGHT_2_SPACE_2 * result;

            case 3:
                return WEIGHT_3_SPACE_2 * result;

            case 4:
                return WEIGHT_4_SPACE_2 * result;

            case 5:
            case 6:
            case 7:
            case 8:
                return WEIGHT_5 * result;
            default:
                return 0;
            }
        }
    }
}