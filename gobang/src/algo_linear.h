//线性加权算法
//对矩阵的整体进行查找, 缺点很明显
//没用

#define ALGO_LINEAR 1

//这里的权值是随便赋的
#define WEIGHT_1_LINK 1
#define WEIGHT_2_LINK 10
#define WEIGHT_3_LINK 100
#define WEIGHT_4_LINK 1000
#define WEIGHT_5_LINK 10000

//Let + be black weight, and - be white weight;
 int ShowWeightArray_Algo1();
 int Show_ValidArray_Algo1();

//对矩阵的整体查找
 int GenValidPosition_Algo1();
 int WeightContribute_Algo1(int incolor, int continuecnt);
 int LinearGenWeightForShapeNow_Algo1();
 int LinearGenweightAt_Algo1(int a, int b);
 int LinearGenWeightMartix_Algo1();

// //对每个点的附近进行查找
//  int PointGenWeightAt(int a, int b);

 int _ValidPositionForLinearAlgo[BOUNDRY][BOUNDRY];

 int _weightnow;

//  int JudgeWinPlus();
//  int _LinearWeightCnter(int a, int b, int mode); //if mode==CLEAR, set cnt,max,color=0

int AlgoLinear(int *ap, int *bp) //Write the position choosed into int* ap,int* bp;
{
    if (fstmove && colornow == BLACK)
    {
        *ap = BOUNDRY / 2;
        *bp = BOUNDRY / 2;
        fstmove = 0;
        return 0;
    }

    LinearGenWeightMartix_Algo1();
    // SHOWALL(weight, "int");
    int a_choosed = 0, b_choosed = 0;
    if (colornow == BLACK)
    {
        int max_weight_get = -100000.0;
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
        int min_weight_get = 100000.0;
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
    *ap = a_choosed;
    *bp = b_choosed;

    return 0;
}
//colornow is known;

 int WeightContribute_Algo1(int incolor, int continuecnt)
{
    int result = 0.0;
    switch (continuecnt)
    {
    case 0:
        result = 0.0;
        break;
    case 1:
        result = WEIGHT_1_LINK;
        break;
    case 2:
        result = WEIGHT_2_LINK;
        break;
    case 3:
        result = WEIGHT_3_LINK;
        break;
    case 4:
        result = WEIGHT_4_LINK;
        break;
    case 5:
        result = WEIGHT_5_LINK;
        break;
    default:
        //more than 5
        result = WEIGHT_5_LINK;
    }

    switch (incolor)
    {
    case 0:
        return 0.0;
    case BLACK:
        return result;
    case WHITE:
        return -result;
    }
}

 int LinearGenWeightForShapeNow_Algo1()
{
    int weight_for_shape_now = 0.0;
    //line
    int incolor = 0;
    int continuecnt = 0;
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
                weight_for_shape_now += WeightContribute_Algo1(incolor, continuecnt);
                continuecnt = 1;
                incolor = board[a][b];
            }
        }
        weight_for_shape_now += WeightContribute_Algo1(incolor, continuecnt);
        incolor = 0;
        continuecnt = 0;
    }

    //col
    incolor = 0;
    continuecnt = 0;
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
                weight_for_shape_now += WeightContribute_Algo1(incolor, continuecnt);
                continuecnt = 1;
                incolor = board[a][b];
            }
        }
        weight_for_shape_now += WeightContribute_Algo1(incolor, continuecnt);
        incolor = 0;
        continuecnt = 0;
    }

    //dig2
    incolor = 0;
    continuecnt = 0;
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
                    weight_for_shape_now += WeightContribute_Algo1(incolor, continuecnt);
                    continuecnt = 1;
                    incolor = board[a][b];
                }
            }
        }
        weight_for_shape_now += WeightContribute_Algo1(incolor, continuecnt);
        incolor = 0;
        continuecnt = 0;
    }

    //dig1
    incolor = 0;
    continuecnt = 0;
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
                    weight_for_shape_now += WeightContribute_Algo1(incolor, continuecnt);
                    continuecnt = 1;
                    incolor = board[a][b];
                }
            }
        }
        weight_for_shape_now += WeightContribute_Algo1(incolor, continuecnt);
        incolor = 0;
        continuecnt = 0;
    }
    return weight_for_shape_now;
}

 int LinearGenweightAt_Algo1(int a, int b)
{
    if (board[a][b]) //该位置无法落子
    {
        return 0;
    }
    board[a][b] = colornow;
    int change = LinearGenWeightForShapeNow_Algo1() - _weightnow;
    board[a][b] = 0;
    return change;
}

 int LinearGenWeightMartix_Algo1()
{
    //4连情况

    //3连情况

    //在上一个条件不满足时执行:
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
    memset(_ValidPositionForLinearAlgo, 0, sizeof(int) * BOUNDRY * BOUNDRY);
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b])
            {
                _ValidPositionForLinearAlgo[BoundLim(a + 1)][BoundLim(b + 1)] = 1;
                _ValidPositionForLinearAlgo[BoundLim(a + 1)][BoundLim(b)] = 1;
                _ValidPositionForLinearAlgo[BoundLim(a + 1)][BoundLim(b - 1)] = 1;
                _ValidPositionForLinearAlgo[BoundLim(a)][BoundLim(b + 1)] = 1;
                _ValidPositionForLinearAlgo[BoundLim(a)][BoundLim(b)] = 1;
                _ValidPositionForLinearAlgo[BoundLim(a)][BoundLim(b - 1)] = 1;
                _ValidPositionForLinearAlgo[BoundLim(a - 1)][BoundLim(b + 1)] = 1;
                _ValidPositionForLinearAlgo[BoundLim(a - 1)][BoundLim(b)] = 1;
                _ValidPositionForLinearAlgo[BoundLim(a - 1)][BoundLim(b - 1)] = 1;
                
            }
        }
    }

// makemovenow:

    //在可行的位置产生权重
    _weightnow = LinearGenWeightForShapeNow_Algo1();

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (_ValidPositionForLinearAlgo[a][b])
                weight[a][b] = LinearGenweightAt_Algo1(a, b);
        }
    }
}

 int ShowWeightArray_Algo1()
{
     for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%d ", weight[a][b]);
        }
        puts("");
    }
}

 int Show_ValidArray_Algo1()
{
     for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%d ", _ValidPositionForLinearAlgo[a][b]);
        }
        puts("");
    }
}