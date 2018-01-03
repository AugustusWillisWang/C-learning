//判断胜利,若有一方胜利返回对应的color,否则返回0

int JudgeWinOriginal()
{
    //判断胜利,应该是最高效的算法了
    //这是第一次写的有点zz.......
    int color = 0;
    int cnt = 0;
    int max = 0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            switch (color)
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
        max = 0;
        cnt = 0;
        color = 0;
    }
    //row
    color = 0;
    cnt = 0;
    max = 0;
    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            switch (color)
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
        max = 0;
        cnt = 0;
        color = 0;
    }
    //dig2
    color = 0;
    cnt = 0;
    max = 0;
    for (int aplusb = 0; aplusb < 2 * (BOUNDRY - 1); aplusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = aplusb - a;
            if (b >= 0 && b < BOUNDRY)
            {
                switch (color)
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
        }
        max = 0;
        cnt = 0;
        color = 0;
    }

    //dig1
    color = 0;
    cnt = 0;
    max = 0;
    for (int aminusb = -(BOUNDRY - 1); aminusb < (BOUNDRY - 1); aminusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = a - aminusb;
            if (b >= 0 && b < BOUNDRY)
            {
                switch (color)
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
        }
        max = 0;
        cnt = 0;
        color = 0;
    }
}

//此函数被放到具体算法中用static 函数实现
// int GenWeight()
// {
//     //产生权重
// }



int _Tester(int a, int b, int mode) //if mode==CLEAR, set cnt,max,color=0
{
    static int cnt;
    static int max;
    static int color;
    if (mode == CLEAR)
    {
        cnt = 0;
        max = 0;
        color = 0;
    }
    switch (color)
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

int JudgeWinPlus()
{
    //判断胜利,应该是最高效的算法了
    //使用static简化了代码

    for (int a = 0; a < BOUNDRY; a++)
    {
        int mark = CLEAR;
        for (int b = 0; b < BOUNDRY; b++)
        {
            _Tester(a, b, mark);
            mark = NORMAL;
        }
    }
    for (int b = 0; b < BOUNDRY; b++)
    {
        int mark = CLEAR;
        for (int a = 0; a < BOUNDRY; a++)
        {
            _Tester(a, b, mark);
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
                _Tester(a, b, mark);
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
                _Tester(a, b, mark);
                mark = NORMAL;
            }
        }
    }
}


// int _ndefZobchain = 1;

// struct _ZobChain
// {
//     int (*boardrecord)[BOUNDRY];
//     double weight;
//     struct _ZobChain *next;
// };
// int (*BoardRec())[BOUNDRY]
// //malloc memory to save the board now, meanwhile, return the point foe saved board.
// {
//     int(*result)[BOUNDRY] = (int(*)[BOUNDRY])malloc(sizeof(int) * BOUNDRY * BOUNDRY);
//     // memcpy(result, board, BOUNDRY * BOUNDRY * sizeof(int));
//     for (int a = 0; a < BOUNDRY; a++)
//     {
//         for (int b = 0; b < BOUNDRY; b++)
//         {
//             result[a][b] = board[a][b];
//         }
//     }
//     return result;
// }

// int BoardCmp(int (*boarda)[BOUNDRY], int (*boardb)[BOUNDRY])
// {
//     for (int a = 0; a < BOUNDRY; a++)
//     {
//         for (int b = 0; b < BOUNDRY; b++)
//         {
//             if (boarda[a][b] < boardb[a][b])
//                 return -1;
//             if (boarda[a][b] > boardb[a][b])
//                 return 1;
//         }
//     }
//     return 0;
// }

// double FindinZobChain(unsigned long int zob, double **_socket)
// //Remark: the status of this function is defined at double *_zobnewweight = 0;
// // _weight= FindinZobChain();
// // if (_zobnewweight == 0) {_weight = newweight();*_zobnewweight=_weight;}
// // else goon;
// {

//     struct _ZobChain *_lastpoint = hashtable[zob];
//     struct _ZobChain *current;

//     //emptylist

//     if (hashtable[zob] == 0)
//     {
//         hashtable[zob] = (struct _ZobChain *)malloc(sizeof(struct _ZobChain));
//         current = hashtable[zob];
//         // current->boardrecord = 0;
//         // puts("new line!");
//         current->next = 0;
//         current->boardrecord = BoardRec();
//         *_socket = &(current->weight);
//         return 0;
//     }
//     else
//     {
//         current = hashtable[zob];
//     }
//     //nonemptylist
//     do
//     {
//         if (BoardCmp(current->boardrecord, board) == 1)
//         {
//             _lastpoint = current;
//             if (current->next == 0)
//             {
//                 //add here
//                 // puts("new end!");

//                 current->next = (struct _ZobChain *)malloc(sizeof(struct _ZobChain));
//                 current->next->next = 0;
//                 current->next->boardrecord = BoardRec();
//                 *_socket = &(current->next->weight);
//                 return 0;
//             }
//             current = current->next;
//             // printf("%p\n", current);
//             continue;
//         }
//         if (BoardCmp(current->boardrecord, board) == 0)
//         {
//             // puts("read!");
//             *_socket = 0;
//             return current->weight;
//         }
//         if (BoardCmp(current->boardrecord, board) == -1)
//         {
//             //add here;
//             // puts("new in!");
//             _lastpoint = (struct _ZobChain *)malloc(sizeof(struct _ZobChain));
//             _lastpoint->next = current;
//             _lastpoint->boardrecord = BoardRec();
//             *_socket = &(_lastpoint->weight);
//             return 0;
//         }

//         BOOM("Undefed sit!");
//     } while (1);
// }

// double FindInHashTable(double **_socket)
// {
//     unsigned long int zob = Getzob();
//     return FindinZobChain(zob, _socket);
// }

int PrintBoard_Obsoleted()
{
    // ┠ ┨┯ ┷┏┓┗ ┛┳⊥﹃﹄┌ ┐└ ┘∟
    // http://lulinbest.blog.sohu.com/88118628.html
    int LINE = 103;
    int VLINE = 104;
    int CROSS = 105;

    static int display_array[30][30];
    for (int i = 2; i < 2 + BOUNDRY; i++)
    {
        display_array[0][i] = i - 2;
    }

    for (int i = 2; i < 2 + BOUNDRY; i++)
    {
        display_array[i][0] = i - 2;
    }
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            display_array[2 + a][2 + b] = board[a][b];
        }
    }

    for (int a = 0; a < 30; a++)
    {
        for (int b = 0; b < 30; b++)
        {
            switch (display_array[a][b])
            {

            case BLACK + 100:
                printf("1");
                break;
            case WHITE + 100:
                printf("2");
                break;
            case 0:
                if (a == 0 || b == 0)
                {
                    printf(" 0");
                    break;
                }
                printf(" ");
                break;
            default:
                printf("%d", display_array[a][b]);
            }
        }
        puts("");
    }

    return 0;
}
