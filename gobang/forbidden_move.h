#ifndef _FBD_MOVE
#define _FBD_MOVE

// int board[BOUNDRY][BOUNDRY];      //棋盘数据
// int BoundLim(int a)

int valid_position[BOUNDRY][BOUNDRY];
int forbid_move[BOUNDRY][BOUNDRY];
int _fbd_line[9];

int TestForbidMove(int a, int b, int colornow)
{
    //This function assumes that the position is legal, otherwise, other function should take care of this.
    if (a != BoundLim(a) || b != BoundLim(b))
        return 0; //Just return 0.

    //White has no forbidden move;
    if (colornow == WHITE)
        return 0;
    // int fbd_Testline();
    if (board[a][b])
    {
        BOOM("fbd20");
        return 0;
    }
    int huo3 = 0;
    int huo4 = 0;
    int huo5 = 0;
    int longlink5 = 0;
    int link = 1;
    int block = 0;

    board[a][b] = BLACK;
    for (int i = 0; i < 9; i++)
    {
        _fbd_line[i] = Board(a - 4 + i, b);
    }
    // fbd_Testline();
    {
        for (int p = 1; p <= 4; p++)
        {
            if (_fbd_line[4 - p] == BLACK)
                link++;
            else
            {
                if (_fbd_line[4 - p] == 0)
                    break;
                else
                {
                    block++;
                    break;
                }
            }
        }
        for (int p = 1; p <= 4; p++)
        {
            if (_fbd_line[4 + p] == BLACK)
                link++;
            else
            {
                if (_fbd_line[4 + p] == 0)
                    break;
                else
                {
                    block++;
                    break;
                }
            }
        }

        if (link >= 3 && (block == 0)) //33FORBID
        {
            huo3++;
        }
        if (link >= 4 && (block != 2)) //44FORBID
        {
            huo4++;
        }
        if (5==link) //5 edge enabled
        {
            huo5++;
        }
        if (link >= 5)
        { //long link forbid_move
            longlink5++;
        }

        link = 1;
        block = 0;
    }

    for (int i = 0; i < 9; i++)
    {
        _fbd_line[i] = Board(a, b - 4 + i);
    }
    // fbd_Testline();
    {
        for (int p = 1; p <= 4; p++)
        {
            if (_fbd_line[4 - p] == BLACK)
                link++;
            else
            {
                if (_fbd_line[4 - p] == 0)
                    break;
                else
                {
                    block++;
                    break;
                }
            }
        }
        for (int p = 1; p <= 4; p++)
        {
            if (_fbd_line[4 + p] == BLACK)
                link++;
            else
            {
                if (_fbd_line[4 + p] == 0)
                    break;
                else
                {
                    block++;
                    break;
                }
            }
        }

        if (link >= 3 && (block == 0)) //33FORBID
        {
            huo3++;
        }
        if (link >= 4 && (block != 2)) //44FORBID
        {
            huo4++;
        }
        if (5==link) //5 edge enabled
        {
            huo5++;
        }
        if (link >= 5)
        { //long link forbid_move
            longlink5++;
        }
        link = 1;
        block = 0;
    }

    for (int i = 0; i < 9; i++)
    {
        _fbd_line[i] = Board(a - 4 + i, b - 4 + i);
    }
    // fbd_Testline();
    {
        for (int p = 1; p <= 4; p++)
        {
            if (_fbd_line[4 - p] == BLACK)
                link++;
            else
            {
                if (_fbd_line[4 - p] == 0)
                    break;
                else
                {
                    block++;
                    break;
                }
            }
        }
        for (int p = 1; p <= 4; p++)
        {
            if (_fbd_line[4 + p] == BLACK)
                link++;
            else
            {
                if (_fbd_line[4 + p] == 0)
                    break;
                else
                {
                    block++;
                    break;
                }
            }
        }
        if (link >= 3 && (block == 0)) //33FORBID
        {
            huo3++;
        }
        if (link >= 4 && (block != 2)) //44FORBID
        {
            huo4++;
        }
        if (5==link) //5 edge enabled
        {
            huo5++;
        }
        if (link >= 5)
        { //long link forbid_move
            longlink5++;
        }

        link = 1;
        block = 0;
    }

    for (int i = 0; i < 9; i++)
    {
        _fbd_line[i] = Board(a - 4 + i, b + 4 - i);
    }
    // fbd_Testline();
    {
        for (int p = 1; p <= 4; p++)
        {
            if (_fbd_line[4 - p] == BLACK)
                link++;
            else
            {
                if (_fbd_line[4 - p] == 0)
                    break;
                else
                {
                    block++;
                    break;
                }
            }
        }
        for (int p = 1; p <= 4; p++)
        {
            if (_fbd_line[4 + p] == BLACK)
                link++;
            else
            {
                if (_fbd_line[4 + p] == 0)
                    break;
                else
                {
                    block++;
                    break;
                }
            }
        }

        if (link >= 3 && (block == 0)) //33FORBID
        {
            huo3++;
        }
        if (link >= 4 && (block != 2)) //44FORBID
        {
            huo4++;
        }
        if (5==link) //5 edge enabled
        {
            huo5++;
        }
        if (link >= 5)
        { //long link forbid_move
            longlink5++;
        }

        link = 1;
        block = 0;
    }

    //====================================
    board[a][b] = 0;
    if (huo5)
        return 0;
    if (longlink5)
        return 1;
    if (huo3 >= 2)
        return 1;
    if (huo4 >= 2)
        return 1;
    return 0;
    //-----------------------------------------------------------
}

int GenForbidMove(int (*valid_position)[BOUNDRY], int colornow)
{
    if (colornow == WHITE)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            for (int b = 0; b < BOUNDRY; b++)
            {
                forbid_move[a][b] = 0;
            }
        }

        return 0;
    }
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (valid_position[a][b])
            {
                valid_position[a][b] = TestForbidMove(a, b, colornow);
            }
        }
    }
    return 0;
}

int GenValidPosition(int (*valid_position)[BOUNDRY], int colornow)
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            for (int c = a - 2; c <= a + 2; c++)
            {
                for (int d = b - 2; d <= b + 2; b++)
                {
                    valid_position[BoundLim(c)][BoundLim(d)] = (board[BoundLim(c)][BoundLim(d)] == 0 ? 1 : 0);
                }
            }
        }
    }
}

int TestTipForbidMove(int a, int b, int colornow)
{
    if (TestForbidMove(a, b, colornow))
    {
        puts("Black takes forbidden move, reinput please!");
        return 1;
    }
    return 0;
}
#endif