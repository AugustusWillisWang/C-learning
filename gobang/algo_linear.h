//线性加权算法

#define ALGO_LINEAR 1

//Let + be black weight, and - be white weight;

static int LinearGenWeight();
// static int JudgeWinPlus();
static int _LinearWeightCnter(int a, int b, int mode); //if mode==CLEAR, set cnt,max,color=0

int AlgoLinear(int *ap, int *bp) //Write the position choosed into int* ap,int* bp;
{
    LinearGenWeight();
    int a_choosed=0,b_choosed=0;
    double max_weight_get = 0.0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY;b++){
            if(weight[a][b]>max_weight_get){
                max_weight_get = weight[a][b];
                a_choosed = a;
                b_choosed = b;
            }
        }
    }
    *ap = a_choosed;
    *bp = b_choosed;
    return 0;
}
    //colornow is known;
    


static int _LinearWeightCnter(int a, int b, int mode) //if mode==CLEAR, set cnt,max,color=0
{
    BLACK==1;
    WHITE == 2;
    static int cnt;
    static int max;
    static int color;
    if (mode == CLEAR)
    {
        cnt = 0;
        max = 0;
        color = 0;
    }
    switch (color) //Former color;
    {
    case 0:
        if (board[a][b] == WHITE)
        {
            color = WHITE;
            cnt++;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == BLACK)
        {
            color = BLACK;
            cnt++;
            if (cnt > max)
                max = cnt;
        }
        break;
    case BLACK:
        if (board[a][b] == WHITE)
        {
            color = WHITE;
            cnt = 1;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == BLACK)
        {
            color = BLACK;
            cnt++;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == 0)
        {
            color = 0;
            cnt = 0;
            if (cnt > max)
                max = cnt;
        }
        break;
    case WHITE:
        if (board[a][b] == WHITE)
        {
            color = WHITE;
            cnt++;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == BLACK)
        {
            color = BLACK;
            cnt = 1;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == 0)
        {
            color = 0;
            cnt = 0;
            if (cnt > max)
                max = cnt;
        }
        break;
    }
    if (max == 5)
    {
        if (color == WHITE)
        {
            printf("White wins!\n");
        }
        else if (color == BLACK)
        {
            printf("Black wins!\n");
        }
        return color;
    }
}

int LinearGenWeight()
{
    //判断胜利,应该是最高效的算法了
    //使用static简化了代码

    for (int a = 0; a < BOUNDRY; a++)
    {
        int mark = CLEAR;
        for (int b = 0; b < BOUNDRY; b++)
        {
            _LinearWeightCnter(a, b, mark);
            mark = NORMAL;
        }
    }
    for (int b = 0; b < BOUNDRY; b++)
    {
        int mark = CLEAR;
        for (int a = 0; a < BOUNDRY; a++)
        {
            _LinearWeightCnter(a, b, mark);
            mark = NORMAL;
        }
    }
    for (int aplusb = 0; aplusb < 2 * (BOUNDRY - 1); aplusb++)
    {
        int mark = CLEAR;

        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = aplusb - a;
            if (b >= 0 && b < BOUNDRY)
            {
                _LinearWeightCnter(a, b, mark);
                mark = NORMAL;
            }
        }
    }
    for (int aminusb = -(BOUNDRY - 1); aminusb < (BOUNDRY - 1); aminusb++)
    {
        int mark = CLEAR;

        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = a - aminusb;
            if (b >= 0 && b < BOUNDRY)
            {
                _LinearWeightCnter(a, b, mark);
                mark = NORMAL;
            }
        }
    }
}
