//线性加权算法

#define ALGO_LINEAR 1
#define WEIGHT_1_LINK 1
#define WEIGHT_2_LINK 10
#define WEIGHT_3_LINK 100
#define WEIGHT_4_LINK 1000
#define WEIGHT_5_LINK 10000

//Let + be black weight, and - be white weight;

static double WeightContribute(int incolor, int continuecnt);
static double LinearGenWeightForShapeNow();
static double LinearGenweightAt(int a, int b);
static int LinearGenWeightMartix();

static double _weightnow;


// static int JudgeWinPlus();
// static int _LinearWeightCnter(int a, int b, int mode); //if mode==CLEAR, set cnt,max,color=0

int AlgoLinear(int *ap, int *bp) //Write the position choosed into int* ap,int* bp;
{
    if(fstmove&&colornow==BLACK){
    *ap = BOUNDRY/2;
    *bp = BOUNDRY/2;
    fstmove = 0;
    return 0;
    }

    LinearGenWeightMartix();
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

static double WeightContribute(int incolor, int continuecnt)
{
    double result = 0.0;
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

static double LinearGenWeightForShapeNow()
{
    double weight_for_shape_now = 0.0;
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
                weight_for_shape_now += WeightContribute(incolor, continuecnt);
                continuecnt = 1;
                incolor = board[a][b];
            }
        }
        weight_for_shape_now += WeightContribute(incolor, continuecnt);
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
                weight_for_shape_now += WeightContribute(incolor, continuecnt);
                continuecnt = 1;
                incolor = board[a][b];
            }
        }
        weight_for_shape_now += WeightContribute(incolor, continuecnt);
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
                    weight_for_shape_now += WeightContribute(incolor, continuecnt);
                    continuecnt = 1;
                    incolor = board[a][b];
                }
            }
        }
        weight_for_shape_now += WeightContribute(incolor, continuecnt);
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
                    weight_for_shape_now += WeightContribute(incolor, continuecnt);
                    continuecnt = 1;
                    incolor = board[a][b];
                }
            }
        }
        weight_for_shape_now += WeightContribute(incolor, continuecnt);
        incolor = 0;
        continuecnt = 0;
    }
    return weight_for_shape_now;
}

static double LinearGenweightAt(int a, int b)
{
    if (board[a][b]) //该位置无法落子
    {
        return 0;
    }
    board[a][b] = colornow;
    double change = LinearGenWeightForShapeNow() - _weightnow;
    board[a][b] = 0;
    return change;
}

static int LinearGenWeightMartix()
{
    _weightnow = LinearGenWeightForShapeNow();
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            weight[a][b] = LinearGenweightAt(a, b);
        }
    }
}
