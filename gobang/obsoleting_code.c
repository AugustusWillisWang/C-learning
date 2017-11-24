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
