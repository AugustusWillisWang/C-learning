//测试用完全随机算法

#define ALGO_BASIC 0

static int GenWeight();

int AlgoBasic(int* ap,int* bp) //Write the position choosed into int* ap,int* bp;
{
    *ap = rand()%19;
    *bp = rand()%19;
    return 0;
}

static int GenWeight()
{
    return 0;
}