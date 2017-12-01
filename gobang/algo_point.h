//对矩阵的各点进行查找

#define ALGO_POINT 2
#define EDGE 3

//这里的权值是随便赋的
#define WEIGHT_1_2SIDE 2
#define WEIGHT_2_2SIDE 20
#define WEIGHT_3_2SIDE 200
#define WEIGHT_4_2SIDE 2000
#define WEIGHT_5_2SIDE 20000

#define WEIGHT_1_1SIDE 1
#define WEIGHT_2_1SIDE 10
#define WEIGHT_3_1SIDE 100
#define WEIGHT_4_1SIDE 1000
#define WEIGHT_5_1SIDE 10000

//Let + be black weight, and - be white weight;
static int ShowWeightArray_Algo2();
static int Show_ValidArray_Algo2();

//对矩阵的整体查找
static int GenValidPosition_Algo2();    //Calc only near the exist point.
static double WeightContribute_Algo2(); //Gen weight for a single line in _Testline[9]
static double PointGenWeightForShapeNow_Algo2();
static double PointGenweightAt_Algo2(int a, int b); //Get the weight change if making move at a,b.
static int PointGenWeightMartix_Algo2();

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

static int _ValidPositionForPointAlgo[BOUNDRY][BOUNDRY];
static int _TestedPositionForPointAlgo[BOUNDRY][BOUNDRY];
static int _Testline[9]; //Get 9 elements out to check the weight.

static double _weightnow;

// static int JudgeWinPlus();
// static int _LinearWeightCnter(int a, int b, int mode); //if mode==CLEAR, set cnt,max,color=0

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
        double max_weight_get = -100000.0;
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
        double min_weight_get = 100000.0;
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

static double WeightContribute_Algo2()
//Deal with the 1-d 9 element array, return the weight generated.
//At the same time, mark the point tested.(Obsoleted)
{
    // static int _Testline[9];//Get 9 elements out to check the weight.
    int leftblocked = 0;
    int rightblocked = 0;
    int cnt = 0;
    int position = 5; //The middle of the 9 positions.

    //Get the weight of this position.
    if (_Testline[position] == 0)
        return 0;

    int colorinmiddle = _Testline[position];
    while (position >= 0 && _Testline[--position] == colorinmiddle) //Highlight!
        cnt++;
    switch (_Testline[position])
    {

    case 0:
        leftblocked = 0;
        break;

    default:
        leftblocked = 1;
        break;
    }
    position = 5;
    while (position < 9 && _Testline[--position] == colorinmiddle) //Highlight!
        cnt++;
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
    position = 5;
    while(position>=0&&_Testline[--position]!=Inverse(colorinmiddle)&&_Testline[position]!=EDGE){
        linkmax++;
    }
    position = 5;
    while(position<9&&_Testline[++position]!=Inverse(colorinmiddle)&&_Testline[position]!=EDGE){
        linkmax++;
    }
    if(linkmax<5)return 0;

    //Return weight according to cnt, l,r,blocked;
}

static double PointGenWeightForShapeNow_Algo2()
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
                    _Testline[i] = EDGE;
                }
                else
                {
                    _Testline[i] = board[aget][bget];
                }
            }
            weight_for_shape_now += WeightContribute_Algo2();
            for (int bget = b - 4, aget = a, i = 0; bget <= b + 4; bget++, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline[i] = EDGE;
                }
                else
                {
                    _Testline[i] = board[aget][bget];
                }
            }
            weight_for_shape_now += WeightContribute_Algo2();

            for (int aget = a - 4, bget = b - 4, i = 0; aget <= a + 4; aget++, bget++, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline[i] = EDGE;
                }
                else
                {
                    _Testline[i] = board[aget][bget];
                }
            }
            weight_for_shape_now += WeightContribute_Algo2();

            for (int aget = a - 4, bget = b + 4, i = 0; aget <= a + 4; aget++, bget--, i++)
            {
                if (aget < BOUNDRY && aget >= 0 && bget >= 0 && bget < BOUNDRY)
                {
                    _Testline[i] = EDGE;
                }
                else
                {
                    _Testline[i] = board[aget][bget];
                }
            }
            weight_for_shape_now += WeightContribute_Algo2();
        }
    }
    return weight_for_shape_now;
}

static double PointGenweightAt_Algo2(int a, int b)
{
    if (board[a][b]) //该位置无法落子
    {
        return 0;
    }
    board[a][b] = colornow;
    double change = PointGenWeightForShapeNow_Algo2() - _weightnow;
    board[a][b] = 0;
    return change;
}

static int PointGenWeightMartix_Algo2()
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

    //在可行的位置产生权重
    _weightnow = PointGenWeightForShapeNow_Algo2();

    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (_ValidPositionForPointAlgo[a][b])
                weight[a][b] = PointGenweightAt_Algo2(a, b);
        }
    }
}

static int ShowWeightArray_Algo2()
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%lf ", weight[a][b]);
        }
        puts("");
    }
}

static int Show_ValidArray_Algo2()
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