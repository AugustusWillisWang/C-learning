//测试用完全随机算法
//没用
#define ALGO_BASIC 0
#include "support.h"
// static int GenWeight();

int AlgoBasic(int *ap, int *bp) //Write the position choosed into int* ap,int* bp;
{
    // if(fstmove&&colornow==BLACK){
    //     *ap = BOUNDRY/2;
    //     *bp = BOUNDRY/2;
    //     fstmove = 0;
    //     return 0;
    // }
    *ap = BOUNDRY / 2;
    *bp = BOUNDRY / 2;
    while (board[*ap][*bp])
    {
        *ap = rand() % BOUNDRY;
        *bp = rand() % BOUNDRY;
    }

    return 0;
}

// static int GenWeight()
// {
//     return 0;
// }