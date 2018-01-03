
int SimpleSituationCheck_Algo3(int (*_ValidPosition)[BOUNDRY]) //Check 4-1 4-2 3-2 in order. If such situation exists, constrain avaliable position to such areas.
{
    // Show_ValidArray_Algo3();
    // BP;

    // PointTestNaiveSituationForShapeNow_Algo3(3, 2, _ValidPosition);
    // Show_ValidArray_Algo3();
    // BP;

    PointTestNaiveSituationForShapeNow_Algo3(4, 2, _ValidPosition);
    // Show_ValidArray_Algo3();
    // BP;

    PointTestNaiveSituationForShapeNow_Algo3(4, 1, _ValidPosition);
    // Show_ValidArray_Algo3();
    // BP;
}

int PointTestNaiveSituationForShapeNow_Algo3(int cntneeded, int spaceneeded, int (*_ValidPosition)[BOUNDRY])
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
                GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor, _ValidPosition);
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
        GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor, _ValidPosition);

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
                GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor, _ValidPosition);
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
        GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor, _ValidPosition);

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
                    GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor, _ValidPosition);
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
        GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor, _ValidPosition);

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
                    GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor, _ValidPosition);
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
        GenNaiveConstrain_Algo3(cntneeded, spaceneeded, start, end, continuecnt, &startposition, &endposition, incolor, _ValidPosition);

        incolor = 0;
        continuecnt = 0;
    }
    return 0;
}

int GenNaiveConstrain_Algo3(int cntneeded, int spaceneeded, int start, int end, int continuecnt, int *startposition, int *endposition, int incolor, int (*_ValidPosition)[BOUNDRY])
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
            memset(_ValidPosition, 0, sizeof(int) * BOUNDRY * BOUNDRY);
        }
        if (startposition[0] != -1 && startposition[1] != -1)
            _ValidPosition[startposition[0]][startposition[1]] = 1;
        if (endposition[0] != -1 && endposition[1] != -1)
            _ValidPosition[endposition[0]][endposition[1]] = 1;
        // BP;
    }
}
